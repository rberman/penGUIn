//
//  Sphere.hpp
//  
//
//  Created by Bret Jackson on 2/3/17.
//
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <stdio.h>
#include "Model.h"
#include "GLSLProgram.h"
#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_access.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

class Sphere{
public:
    
    /*!
     * Creates a sphere centered at position with the specified radius and color
     */
    Sphere(glm::vec3 &position, float radius, glm::vec4 &color);
    virtual ~Sphere();
    
    virtual void draw(GLSLProgram &shader, glm::mat4 &modelMatrix);
    
protected:
    std::unique_ptr<Model> _model;
    glm::vec3 _position;
    float _radius;
    glm::vec4 _color;
};

#endif /* Sphere_hpp */
