//
//  Line.cpp
//  
//
//  Created by Bret Jackson on 2/3/17.
//
//

#include "Line.h"

namespace basicgraphics {

	Line::Line(glm::vec3 &start, glm::vec3 &end, glm::vec3 &normal, float radius, glm::vec4 &color) : _start(start), _end(end), _radius(radius), _color(color)
	{
		_normal = glm::normalize(normal);
		glm::vec3 direction = _end - _start;
		glm::vec3 right = glm::normalize(glm::cross(normal, direction));

		std::vector<Mesh::Vertex> cpuVertexArray;
		std::vector<int>			 cpuIndexArray;
		std::vector<std::shared_ptr<Texture>> textures;

		Mesh::Vertex vert;
		vert.position = _start + radius * right;
		vert.normal = _normal;
		vert.texCoord0 = glm::vec2(0, 0);
		cpuVertexArray.push_back(vert);
		cpuIndexArray.push_back(0);

		vert.position = _start - radius * right;
		vert.normal = _normal;
		vert.texCoord0 = glm::vec2(0, 1);
		cpuVertexArray.push_back(vert);
		cpuIndexArray.push_back(1);

		vert.position = _end + radius * right;
		vert.normal = _normal;
		vert.texCoord0 = glm::vec2(1, 0);
		cpuVertexArray.push_back(vert);
		cpuIndexArray.push_back(2);

		vert.position = _end - radius * right;
		vert.normal = _normal;
		vert.texCoord0 = glm::vec2(1, 1);
		cpuVertexArray.push_back(vert);
		cpuIndexArray.push_back(3);

		const int numVertices = cpuVertexArray.size();
		const int cpuVertexByteSize = sizeof(Mesh::Vertex) * numVertices;
		const int cpuIndexByteSize = sizeof(int) * cpuIndexArray.size();
		_mesh.reset(new Mesh(textures, GL_TRIANGLE_STRIP, GL_STATIC_DRAW, cpuVertexByteSize, cpuIndexByteSize, 0, cpuVertexArray, cpuIndexArray.size(), cpuIndexByteSize, &cpuIndexArray[0]));
		_mesh->setMaterialColor(_color);

	}

	Line::~Line()
	{
	}

	void Line::draw(GLSLProgram &shader, glm::mat4 &modelMatrix)
	{
		_mesh->draw(shader);
	}
}