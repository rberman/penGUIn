//
//  Head.h
//  Basic_Graphics
//
//  Created by Ruthie Berman on 4/24/17.
//
//

#ifndef Head_h
#define Head_h

#include "GLSLProgram.h"
#include "config.h"
#include "Texture.h"
#include "Mesh.h"
#include "Eye.h"
#include "Cone.h"
#include "Sphere.h"
#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/constants.hpp>
#include <glm/glm/gtx/quaternion.hpp>


namespace basicgraphics {
    class Head {
    public:
        Head(float radius, vec3 translation);
        ~Head(){};
        
        // Calculate and set up buffers to render to screen
        void createHead(float radius);
        void createEye(float radius);
        
        // Draw Penguin head to screen
        void draw(GLSLProgram &shader, const glm::mat4 &modelMatrix);
        
    protected:
        std::vector< std::shared_ptr<Texture> > textures;
        std::unique_ptr<Mesh> _mesh;
        std::unique_ptr<Cone> _beak;
        std::unique_ptr<Eye> _leftEye;
        std::unique_ptr<Eye> _rightEye;
        glm::mat4 _localMat;
    };
}


#endif /* Head_h */
