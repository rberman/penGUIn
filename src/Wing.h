//
//  Wing.h
//  Basic_Graphics
//
//  Created by Ruthie Berman on 4/26/17.
//
//

#ifndef Wing_h
#define Wing_h

#include "GLSLProgram.h"
#include "config.h"
#include "Texture.h"
#include "Mesh.h"
#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/constants.hpp>

namespace basicgraphics {
    class Wing {
    public:
        Wing();
        ~Wing(){};
        
        // Calculate and set up buffers to render to screen
        void createWing(float radius);
        
        // Draw Penguin wing to screen
        void draw(GLSLProgram &shader, const glm::mat4 &modelMatrix);
        
    protected:
        std::vector< std::shared_ptr<Texture> > textures;
        std::unique_ptr<Mesh> _mesh;
        glm::mat4 _localMat;
    };
}


#endif /* Wing_h */
