//
//  Eye.h
//  Basic_Graphics
//
//  Created by Ruthie Berman on 5/3/17.
//
//

#ifndef Eye_h
#define Eye_h

#include "GLSLProgram.h"
#include "config.h"
#include "Texture.h"
#include "Mesh.h"
#include "Cone.h"
#include "Sphere.h"
#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/constants.hpp>
#include <glm/glm/gtx/quaternion.hpp>


namespace basicgraphics {
    class Eye {
    public:
        Eye(float radius, vec3 position);
        ~Eye(){};
        
        // Calculate and set up buffers to render to screen
        void createEye(float radius, vec3 position);
        void createPupil(float radius, vec3 position, float zCoord);
        
        // Draw Penguin head to screen
        void draw(GLSLProgram &shader, const glm::mat4 &modelMatrix);
        
    protected:
        std::vector< std::shared_ptr<Texture> > textures;
        std::unique_ptr<Sphere> _eye;
        std::unique_ptr<Mesh> _pupil;
    };
}


#endif /* Eye_h */
