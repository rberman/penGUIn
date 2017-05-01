#include "AnimatedCharacter.h"
#include "amcutil.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>



namespace basicgraphics {
	AnimatedCharacter::AnimatedCharacter(std::string asfFilename, std::string amcFilename)
	{
		anim = NULL;
		loadSkeleton(asfFilename);
		loadAnimation(amcFilename);
		_head.reset(new Head(0.5, vec3(0, 1, 0)));
		_body.reset(new Body(0.5, vec3(0,0,0)));
		_leftFoot.reset(new Foot(0.5, vec3(0.15, -0.5, 0)));
		_rightFoot.reset(new Foot(0.5, vec3(-0.15, -0.5, 0)));
		_leftWing.reset(new Wing(0.1, vec3(-0.5, 0, 0)));
		_rightWing.reset(new Wing(0.1, vec3(0.5, 0, 0)));
	}

	glm::mat4 AnimatedCharacter::getCurrentCoordinateFrame()
	{
		glm::mat4 rotation = glm::eulerAngleYXZ(deg2rad(orientation.y), deg2rad(orientation.x), deg2rad(orientation.z));
		rotation[3] = vec4(position, 1);
		return rotation;
	}

	void AnimatedCharacter::draw(GLSLProgram &shader, const glm::mat4 &modelMatrix)
	{
		_head->draw(shader, modelMatrix);
		_body->draw(shader, modelMatrix);
		_leftWing->draw(shader, modelMatrix);
		_rightWing->draw(shader, modelMatrix);
		_leftFoot->draw(shader, modelMatrix);
		_rightFoot->draw(shader, modelMatrix);
	}


	/***  Below this line, all routines are for loading skeleton and animation data from files ***/

	float AnimatedCharacter::deg2rad(float d) {
		if (!deg)
			return d;
		else
			return d * glm::pi<float>() / 180;
	}

	void
		AnimatedCharacter::loadSkeleton(std::string asfFilename)
	{
		std::ifstream in(asfFilename.c_str());
		Inreader inr(&in);

		while (inr.good()) {
			if (inr.expect("#")) {
				std::cerr << "Ignoring comment line" << std::endl;
				inr.swallowLine();
			}

			else if (inr.expect(":version")) {
				inr.swallowLine();
			}

			else if (inr.expect(":name")) {
				std::cerr << "Swallowing name" << std::endl;
				inr.swallowLine();
			}

			else if (inr.expect(":units")) {
				std::cerr << "Reading units" << std::endl;
				parseUnits(inr);
			}

			else if (inr.expect(":documentation")) {
				std::cerr << "Reading documentation" << std::endl;
				while (inr.good() && !inr.peek(":")) {
					inr.swallowLine();
				}
			}

			else if (inr.expect(":root")) {
				std::cerr << "Reading root" << std::endl;
				parseRoot(inr);
			}

			else if (inr.expect(":bonedata")) {
				std::cerr << "Reading bonedata" << std::endl;
				parseBonedata(inr);
			}

			else if (inr.expect(":hierarchy")) {
				std::cerr << "Reading hierarchy" << std::endl;
				parseHierarchy(inr);
			}

			else if (inr.expect("")) {
				break;
			}
			else {

				std::string tok;
				inr.readToken(tok);
				if (!inr.good()) {
					break;
				}
				std::cerr << "Encountered unknown token" << std::endl;
				std::cerr << "'" << tok << "'" << std::endl;
				std::abort();
			}
		} // end while (looping over file) 
	}

	void AnimatedCharacter::parseUnits(Inreader &inr) {
		bool cont;
		do {
			cont = false;

			if (inr.expect("mass")) {
				float trash;
				inr.readFloat(trash);
				cont = true;
			}

			if (inr.expect("length")) {
				float trash;
				inr.readFloat(trash);
				cont = true;
			}

			if (inr.expect("angle")) {
				std::string token;
				inr.readToken(token);
				if (token == "deg") {
					deg = true;
				}
			}

		} while (cont);
	}

	void AnimatedCharacter::parseRoot(Inreader &inr) {
		bool cont;
		do {
			cont = false;

			if (inr.expect("order")) {
				cont = true;
				if (!inr.expect("TX TY TZ RX RY RZ")) {
					std::cerr << "'order' not in order expected" << std::endl;
					std::abort();
				}
			}

			if (inr.expect("axis")) {
				cont = true;
				if (!inr.expect("XYZ")) {
					std::cerr << "'axis' not in order expected" << std::endl;
					std::abort();
				}
			}

			if (inr.expect("position")) {
				cont = true;
				inr.readFloat(position.x);
				inr.readFloat(position.y);
				inr.readFloat(position.z);
				position = amc2meter(position);
			}

			if (inr.expect("orientation")) {
				cont = true;
				inr.readFloat(orientation.x);
				inr.readFloat(orientation.y);
				inr.readFloat(orientation.z);
			}

		} while (cont);
	}

	void AnimatedCharacter::parseBonedata(Inreader &inr) {
		while (inr.expect("begin")) {
			std::shared_ptr<Bone> bone(new Bone(inr, deg));
			boneTable.emplace(bone->getName(), bone);
		}
	}

	void AnimatedCharacter::parseHierarchy(Inreader &inr) {
		if (!inr.expect("begin")) {
			std::cerr << "Reading hierarchy, expected 'begin', not found" << std::endl;
			std::abort();
		}
		while (!inr.expect("end")) {
			std::string line;
			std::string parent;
			inr.readToken(parent);
			inr.readLine(line);

			std::stringstream ss(line);
			std::string child;
			ss >> child;
			while (ss) {
				if (parent == "root") {
					rootNodeBones.push_back(boneTable[child]);
				}
				else {
					boneTable[parent]->addChild(boneTable[child]);
				}
				ss >> child;
			}
		}
	}

	void AnimatedCharacter::loadAnimation(std::string amcFilename) {
		if (anim)
			delete anim;
		anim = new std::ifstream(amcFilename.c_str());
		resetFile();
	}

	void AnimatedCharacter::nextFrame() {
		Inreader inr(anim);
		int frame;
		inr.readInt(frame);
		if (!inr.good()) {
			resetFile();
			return;
		}
		while (!inr.upcomingInt()) {
			std::string bone;
			inr.readToken(bone);
			if (!inr.good()) {
				resetFile();
				return;
			}
			if (bone == "root") {
				inr.readFloat(position.x);
				inr.readFloat(position.y);
				inr.readFloat(position.z);
				position = amc2meter(position);
				inr.readFloat(orientation.x);
				inr.readFloat(orientation.y);
				inr.readFloat(orientation.z);
			}
			else {
				boneTable[bone]->readPose(inr);
			}
		}
	}

	void AnimatedCharacter::resetFile() {
		if (!anim) {
			return;
		}
		anim->clear();
		anim->seekg(0);
		Inreader inr(anim);
		inr.swallowLine();
		inr.swallowLine();
		inr.swallowLine();
	}
}



