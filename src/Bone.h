#ifndef Bone_h
#define Bone_h

#include <iostream>
#include "RotationBounds.h"
#include "Inreader.h"
#include "amcutil.h"
#include <cstdlib>
#include "GLSLProgram.h"
#include <glm/glm/glm.hpp>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm/gtc/matrix_access.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtx/euler_angles.hpp>
#include <Vector>




/** This class holds the data for a single articulated joint and bone of an animated character.  It also
    stores a list of 0 or more child bones.  So, it can be used to create a scenegraph for an animated
    character. */
namespace basicgraphics {
    class Bone  {
    public:

        // This constructor is setup to read data from the CMU motion capture database files
        Bone(Inreader &inr, bool dg);

        // Bones are named based on parts of the body
        std::string getName();
  
        // Returns the rotation of this joint in the body.
        glm::mat4 getCurrentLocalRotation();

        // Returns a vector that is scaled to the length of the bone and points in the direction of the bone.
        // In the bone's local coordinate frame, you can think of the bone as beginning at (0,0,0) and ending
        // at the postion (0,0,0) + getBoneVector().
        glm::vec3 getBoneVector() { return length * direction; }

        // An array of pointers to the other bones that are children of this one in the scenegraph.  All children
        // attach to the end of the bone.
        std::vector< std::shared_ptr<Bone> > children;


        // This is the key routine that you need to fill in
        void draw();

        
          /* You should not need to use anything below this line.  These routines are used for reading the
     bone data from files */

        void addChild(std::shared_ptr<Bone> child);

        void readPose(Inreader &inr);

    protected:

        void constructFromFile(Inreader &inr, bool dg);

        float deg2rad(float d);

        std::string name;
        float length;
        glm::vec3 direction;
        RotationBounds rotationBounds;
        glm::vec3 axis;
        glm::mat4 initialRotation;
        glm::mat4 currentRotation;
        int id;
        bool deg;
    };
}
    

#endif
