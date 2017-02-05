//
//  Cylinder.cpp
//  
//
//  Created by Bret Jackson on 2/3/17.
//
//

#include "Cylinder.h"

namespace basicgraphics {

	Cylinder::Cylinder(glm::vec3 &point1, glm::vec3 &point2, float radius, glm::vec4 &color) : _point1(point1), _point2(point2), _radius(radius), _color(color)
	{
		_model.reset(new Model("cylinder.nff", 1.0, _color));


		glm::vec3 direction = point2 - point1;
		float length = glm::length(direction);
		glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(radius, length, radius));

		glm::vec3 axis = glm::cross(glm::vec3(0, 1, 0), glm::normalize(direction));
		float angle = glm::acos(glm::dot(glm::vec3(0, 1, 0), glm::normalize(direction)));
		glm::mat4 rotate = glm::toMat4(glm::angleAxis(angle, axis));

		glm::vec4 endpt = (rotate * scale * glm::vec4(0, -0.5, 0, 1));
		glm::mat4 trans = glm::translate(glm::mat4(1.0), point1 - glm::vec3(endpt));

		_localMat = trans * rotate * scale;


	}

	Cylinder::~Cylinder() {

	}

	void Cylinder::draw(GLSLProgram &shader, glm::mat4 &modelMatrix) {

		glm::mat4 model = modelMatrix * _localMat;
		shader.setUniform("model_mat", model);
		_model->draw(shader);
	}

}