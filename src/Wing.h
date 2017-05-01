#pragma once

// Wing header file for penGUIn project
//
// Created by Connor Valenti on 4/20/2017

#ifndef Wing_h
#define Wing_h

#include <stdio.h>

#include "Mesh.h"
#include "GLSLProgram.h"
#include "Texture.h"
#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_access.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtx/quaternion.hpp>

namespace basicgraphics {
	class Wing {
	public:
		Wing(float radius, vec3 translation);
		~Wing() {};
		void createWing(float radius);
		void draw(GLSLProgram &shader, const glm::mat4 &modelMatrix);

	protected:
		std::unique_ptr<Mesh> _mesh;
		std::vector<std::shared_ptr<Texture>> textures;
		glm::mat4 _localMat;
	};
}

#endif
