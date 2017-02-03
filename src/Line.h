//
//  Line.hpp
//  
//
//  Created by Bret Jackson on 2/3/17.
//
//

#ifndef Line_hpp
#define Line_hpp

#include <stdio.h>

#include "Mesh.h"
#include "GLSLProgram.h"
#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_access.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtx/quaternion.hpp>

class Line{
public:
    
    /*!
     * Create a line (i.e. a flat ribbon) from start to end. The ribbon surface will face the normal direction and have width of 2*radius
     */
    Line(glm::vec3 &start, glm::vec3 &end, glm::vec3 &normal, float radius, glm::vec4 &color);
    virtual ~Line();
    
    virtual void draw(GLSLProgram &shader, glm::mat4 &modelMatrix);
    
protected:
    std::unique_ptr<Mesh> _mesh;
    glm::vec3 _start;
    glm::vec3 _end;
    glm::vec3 _normal;
    float _radius;
    glm::vec4 _color;
};

#endif /* Line_hpp */
