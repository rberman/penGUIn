//
//  Body.h
//  Basic_Graphics
//
//
//

#ifndef Body_h
#define Body_h

#include "GLSLProgram.h"
#include "config.h"
#include "Texture.h"
#include "Mesh.h"
#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/constants.hpp>

namespace basicgraphics {
    class Body {
    public:
        Body(float radius, vec3 translation);
        ~Body(){};
        
        // Calculate and set up buffers to render to screen
        void createBody(float radius);
        
        // Draw Penguin body to screen
        void draw(GLSLProgram &shader, const glm::mat4 &modelMatrix);
        
    protected:
        std::vector< std::shared_ptr<Texture> > textures;
        std::unique_ptr<Mesh> _mesh;
        glm::mat4 _localMat;
    };
}


#endif /* Body_h */
