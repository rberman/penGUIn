//
//  Foot.h
//  Basic_Graphics
//
//  Created by Ruthie Berman on 4/26/17.
//
//

#ifndef Foot_h
#define Foot_h


#include <stdio.h>
#include "GLSLProgram.h"
#include "Texture.h"
#include "Mesh.h"
#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/constants.hpp>
#include "glm/glm/gtx/orthonormalize.hpp"
#include "glm/glm/gtx/quaternion.hpp"
#include <glm/glm/gtx/vector_angle.hpp>
#include <cmath>

namespace basicgraphics {
    
    class Foot {
    public:
        Foot(const float length, const glm::vec3 legTop);
        ~Foot() {};
        
        void draw(GLSLProgram &shader, const glm::mat4 &modelMatrix); // might need to add model matrix
        
    protected:
        void setupGeometry(const float length);
        std::vector< std::shared_ptr<Texture> > textures;
        std::unique_ptr<Mesh> _mesh;
        glm::mat4 _localMat;
        
    };
}

#endif /* Foot_h */
