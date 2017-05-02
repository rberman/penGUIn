#ifndef AnimatedCharacter_h
#define AnimatedCharacter_h

#include <string>
#include "Bone.h"
#include "Inreader.h"
#include "Head.h"
#include "Foot.h"
#include "Wing.h"
#include "Body.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtx/euler_angles.hpp>
#include <vector>
#include "GLSLProgram.h"
#include <memory>
#include <unordered_map>
#include <tuple>
/** This is the root class for the animated character.  You can also think of this as a root node in
    a scene graph.  The class takes care of loading the skeleton file and also animation file(s) needed
    to draw the skeleton.  The key routine that you need to code is the draw(..) routine.  In it, you
    will want to draw all of the character's bones in the correct positions and orientations based on
    the current animation data. */

namespace basicgraphics {
	class AnimatedCharacter/** : public ReferenceCountedObject**/ {
	public:

		AnimatedCharacter(std::string asfFilename, std::string amcFilename);

		// This should be called once per frame to advance through the animation
		void nextFrame();

		// This returns the current coordinate frame of the ROOT NODE of the character, typicaly this is
		// the character's pelvis -- all of the root node bones should be drawn relative to this coordinate
		// frame.  This coordinate frame will change every frame of the animation.
		glm::mat4 getCurrentCoordinateFrame();

		// This is an array of pointers to bones.  It will contain one or more bones that are attached to the
		// root node of the character, each of these bones will, in turn, have 0 or more child bones.
		std::vector< std::shared_ptr<Bone> > rootNodeBones;


		// TODO: Implement this routine to draw all the character's bones in the correct pose based on the
		// current animation data
		void draw(GLSLProgram &shader, const glm::mat4 &modelMatrix);

		// Calculates absolute model matrices for each body part
		void calculateModelMatrices();

	protected:

		/** Everything below this line is for loading skeleton and animation files **/
		void loadAnimation(std::string amcFilename);

		void loadSkeleton(std::string asfFilename);

		void resetFile();

		float deg2rad(float d);

		void parseUnits(Inreader &inr);
		void parseRoot(Inreader &inr);
		void parseBonedata(Inreader &inr);
		void parseHierarchy(Inreader &inr);

		//The input key should correspond to the keys of the boneTable, which are bone names
		glm::mat4 calculateModelMatrixForBone(std::string key);

		std::unordered_map<std::string, std::tuple<std::string, glm::mat4>> bodyPartInfo; //map of string to tuple
		std::unique_ptr<Foot> _leftFoot;
		glm::mat4 leftFootModel;

		std::unique_ptr<Foot> _rightFoot;
		glm::mat4 rightFootModel;

		std::unique_ptr<Body> _body;
		glm::mat4 bodyModel;

		std::unique_ptr<Head> _head;
		glm::mat4 headModel;

		std::unique_ptr<Wing> _leftWing;
		glm::mat4 leftWingModel;

		std::unique_ptr<Wing> _rightWing;
		glm::mat4 rightWingModel;


		bool deg;
		glm::vec3 position;
		glm::vec3 orientation;
		std::unordered_map< std::string, std::shared_ptr<Bone> > boneTable;
		std::ifstream *anim;
	};
}
#endif
