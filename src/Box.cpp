//
//  Box.cpp
//  
//
//  Created by Bret Jackson on 2/3/17.
//
//

#include "Box.h"

namespace basicgraphics {

	Box::Box(glm::vec3 &min, glm::vec3 &max, glm::vec4 &color) : _min(min), _max(max), _color(color)
	{
		_model.reset(new Model("cube.nff", 1.0, _color));

		glm::vec3 extents = (max - min) / 2.0f;
		glm::vec3 center = min + extents;
		glm::mat4 scale = glm::scale(glm::mat4(1.0), extents);

		glm::mat4 trans = glm::translate(glm::mat4(1.0), center);

		_localMat = trans * scale;


	}

	Box::~Box() {

	}

	void Box::draw(GLSLProgram &shader, glm::mat4 &modelMatrix) {

		glm::mat4 model = modelMatrix * _localMat;
		shader.setUniform("model_mat", model);
		_model->draw(shader);
	}

}