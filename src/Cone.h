//
//  Cone.hpp
//  
//
//  Created by Bret Jackson on 2/3/17.
//
//

#ifndef Cone_hpp
#define Cone_hpp

#include <stdio.h>
#include "Model.h"
#include "GLSLProgram.h"
#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_access.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtx/quaternion.hpp>

class Cone{
public:
    /*!
     * Creates a cone with the base at point1 and the point at point2.
     */
    Cone(glm::vec3 &point1, glm::vec3 &point2, float radius, glm::vec4 &color);
    virtual ~Cone();
    
    virtual void draw(GLSLProgram &shader, glm::mat4 &modelMatrix);
    
protected:
    std::unique_ptr<Model> _model;
    glm::vec3 _point1;
    glm::vec3 _point2;
    glm::mat4 _localMat;
    float _radius;
    glm::vec4 _color;
};

#endif /* Cone_hpp */
