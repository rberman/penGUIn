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

		setBody();

		bodyPartInfo.emplace("head", std::make_tuple("head", mat4(1.0)));
		bodyPartInfo.emplace("body", std::make_tuple("root", mat4(1.0)));
		bodyPartInfo.emplace("leftFoot", std::make_tuple("lfemur", mat4(1.0)));
		bodyPartInfo.emplace("rightFoot", std::make_tuple("rfemur", mat4(1.0)));
		bodyPartInfo.emplace("leftWing", std::make_tuple("lhumerus", mat4(1.0)));
		bodyPartInfo.emplace("rightWing", std::make_tuple("rhumerus", mat4(1.0)));
	}

	void AnimatedCharacter::setBody() {
		//set body
		float bodyHeight = calculateLengthFromRoot("lowerneck") + calculateLengthFromRoot("lfemur");
		_body.reset(new Body(bodyHeight/2, vec3(0, 0, 0)));
		//set head
		float headRadius = calculateLengthFromRoot("head") - calculateLengthFromRoot("lowerneck");
		_head.reset(new Head(headRadius, vec3(0, 0, 0)));
		//set feet
		float footHeight = calculateLengthFromRoot("lfoot") - calculateLengthFromRoot("lfemur");
		_leftFoot.reset(new Foot(footHeight, vec3(0, 0.3, 0)));
		_rightFoot.reset(new Foot(footHeight, vec3(0, 0.3, 0)));
		//set wings
		float wingSize = calculateLengthFromRoot("lfingers") - calculateLengthFromRoot("lclavicle");
		_leftWing.reset(new Wing(wingSize/2, vec3(0.05, -0.3, -.3))); //TODO: calculate based on asf
		_rightWing.reset(new Wing(wingSize/2, vec3(-0.05, -0.3, -.3)));

	}

	float AnimatedCharacter::calculateLengthFromRoot(std::string key) {
		std::shared_ptr<Bone> target = boneTable[key];
		std::shared_ptr<Bone> current = target;
		glm::vec3 compositeBoneVector = vec3(0, 0, 0);
		while (current != boneTable["root"]) {
			compositeBoneVector += current->getBoneVector();
			current = current->_parent;
		}

		return glm::length(compositeBoneVector);
	}

	glm::mat4 AnimatedCharacter::getCurrentCoordinateFrame()
	{
		glm::mat4 rotation = glm::eulerAngleYXZ(deg2rad(orientation.y), deg2rad(orientation.x), deg2rad(orientation.z));
		rotation[3] = vec4(position, 1);
		return rotation;
	}

	glm::mat4 AnimatedCharacter::rotateMatrixAtOrigin(mat4 baseMatrix, mat4 rotationMatrix) {
		vec3 translationVec = baseMatrix[3];
		mat4 translationToCenter = mat4(1.0);
		translationToCenter[3] = vec4(-translationVec, 1.0);
		mat4 translationBack = mat4(1.0);
		translationBack[3] = vec4(translationVec, 1.0);
		
		return (translationBack * rotationMatrix * translationToCenter * baseMatrix);
	}

	void AnimatedCharacter::calculateModelMatrices()
	{
		for (std::unordered_map<std::string, std::tuple<std::string, glm::mat4>>::iterator iter = bodyPartInfo.begin(); iter != bodyPartInfo.end(); ++iter) {
			std::string key = iter->first;
			std::tuple<std::string, glm::mat4> partTuple = bodyPartInfo[key];
			std::get<1>(bodyPartInfo[key]) = calculateModelMatrixForBone(std::get<0>(partTuple));
		}
	}

	glm::mat4 AnimatedCharacter::calculateModelMatrixForBone(std::string key)
	{
		std::shared_ptr<Bone> target = boneTable[key];
		std::shared_ptr<Bone> current = target;
		std::vector<mat4> modelMatrices;
		std::unordered_map<std::string, std::shared_ptr<Bone>> test = boneTable;
		while (current != boneTable["root"]) {
            mat4 currentLocalTranslation = translate(mat4(1.0), current->getBoneVector());
            modelMatrices.push_back(currentLocalTranslation);
			modelMatrices.push_back(current->getCurrentLocalRotation());
			current = current->_parent;
		}

		glm::mat4 totalModel = mat4(1.0);
        for(int i = modelMatrices.size() - 1; i >= 0; i--)
		{
			totalModel = modelMatrices[i] * totalModel;
		}
		//mat4 coordinateFrame = getCurrentCoordinateFrame();
		//totalModel = getCurrentCoordinateFrame() * totalModel;

		return totalModel;
	}

	void AnimatedCharacter::draw(GLSLProgram &shader, const glm::mat4 &modelMatrix)
	{
		glm::mat4 headMat = modelMatrix * std::get<1>(bodyPartInfo["head"]);
		_head->draw(shader, headMat);

		glm::mat4 bodyMat = modelMatrix * std::get<1>(bodyPartInfo["body"]);
		_body->draw(shader, bodyMat);

		
		mat4 leftWingRotation = glm::toMat4(glm::angleAxis(glm::radians(-50.f), vec3(0, 0, 1)));
		glm::mat4 leftWingMat = modelMatrix * rotateMatrixAtOrigin(std::get<1>(bodyPartInfo["leftWing"]), leftWingRotation);
		_leftWing->draw(shader, leftWingMat);

		mat4 rightWingRotation = glm::toMat4(glm::angleAxis(glm::radians(50.f), vec3(0, 0, 1)));
		glm::mat4 rightWingMat = modelMatrix * rotateMatrixAtOrigin(std::get<1>(bodyPartInfo["rightWing"]), rightWingRotation);
		_rightWing->draw(shader, rightWingMat);

		mat4 leftFootRotation = glm::toMat4(glm::angleAxis(glm::radians(25.f),vec3(0,0,1)));
		glm::mat4 leftFootMat = modelMatrix * rotateMatrixAtOrigin(std::get<1>(bodyPartInfo["leftFoot"]), leftFootRotation);//leftFootRotation * std::get<1>(bodyPartInfo["leftFoot"]);
		_leftFoot->draw(shader, leftFootMat);

		mat4 rightFootRotation = glm::toMat4(glm::angleAxis(glm::radians(-25.f), vec3(0, 0, 1)));
		glm::mat4 rightFootMat = modelMatrix * rotateMatrixAtOrigin(std::get<1>(bodyPartInfo["rightFoot"]), rightFootRotation);
		_rightFoot->draw(shader, rightFootMat);
	}


	/***  Below this line, all routines are for loading skeleton and animation data from files ***/

	float AnimatedCharacter::deg2rad(float d) {
		if (!deg)
			return d;
		else
			return d * glm::pi<float>() / 180;
	}

	void AnimatedCharacter::loadSkeleton(std::string asfFilename)
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
					boneTable[child]->setParent(boneTable[parent]);
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



