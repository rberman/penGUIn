// Wing class for penGUIn project
//
// Created by Connor Valenti on 4/20/2017

#include "Wing.h"

namespace basicgraphics {
	Wing::Wing() {
		_localMat = mat4(1.0);
		createWing(0.1);
	}

	void Wing::createWing(float radius) {
		const int STACKS = 20;
		const int SLICES = 40;

		std::vector<Mesh::Vertex> vertexArray;
		std::vector<int> indexArray;

		const float stackAngle = glm::pi<float>() / STACKS;
		const float sliceAngle = 2.0 * glm::pi<float>() / SLICES;
		const float texStackHeight = 1.0 / STACKS;
		const float texSliceWidth = 1.0 / SLICES;
		const float scaleFactor = 3.5;

		std::vector<vec3> topVerts;
		std::vector<vec3> botVerts;
		float stackTopY;
		float stackBottomY;
		float stackTopRadius;
		float stackBotRadius;

		glm::vec3 prevTop;
		glm::vec3 prevBottom;
		glm::vec3 nextTop;
		glm::vec3 nextBottom;

		int VBOindex;

		stackTopY = radius;
		stackBottomY = radius * cos(stackAngle);
		stackBotRadius = sqrt(pow(radius, 2) - pow(stackBottomY, 2));
		stackTopY *= scaleFactor;
		stackBottomY *= scaleFactor;
		nextTop = vec3(0, stackTopY, 0);
		nextBottom = vec3(0, stackBottomY, stackBotRadius);
		botVerts.push_back(nextBottom);

		for (int sliceIndex = 0; sliceIndex <= SLICES; sliceIndex++) {
			prevBottom = nextBottom;
			nextBottom = vec3(stackBotRadius * sin(sliceAngle * (sliceIndex + 1)), stackBottomY, stackBotRadius * cos(sliceAngle * (sliceIndex + 1)));
			botVerts.push_back(nextBottom);

			Mesh::Vertex vert1;
			vert1.position = nextTop;
			vert1.normal = normalize(nextTop);
			vert1.texCoord0 = vec2(0, 0);
			vertexArray.push_back(vert1);
			indexArray.push_back(sliceIndex * 3);

			Mesh::Vertex vert2;
			vert2.position = prevBottom;
			vert2.normal = normalize(prevBottom);
			vert2.texCoord0 = vec2(0, 0);
			vertexArray.push_back(vert2);
			indexArray.push_back(sliceIndex * 3 + 1);

			Mesh::Vertex vert3;
			vert3.position = nextBottom;
			vert3.normal = normalize(nextBottom);
			vert3.texCoord0 = vec2(0, 0);
			vertexArray.push_back(vert3);
			indexArray.push_back(sliceIndex * 3 + 2);
		}

		for (int stackIndex = 1; stackIndex < STACKS - 5; stackIndex++) {
			stackTopY = stackBottomY;
			stackBottomY = radius * cos(stackAngle * (stackIndex + 1));
			stackTopRadius = stackBotRadius;
			stackBotRadius = sqrt(pow(radius, 2) - pow(stackBottomY, 2));
			stackBottomY *= scaleFactor;

			topVerts = botVerts;
			botVerts.clear();
			nextTop = topVerts[0];
			nextBottom = vec3(0, stackBottomY, stackBotRadius);
			botVerts.push_back(nextBottom);

			VBOindex = vertexArray.size();

			for (int sliceIndex = 0; sliceIndex <= SLICES; sliceIndex++) {
				prevTop = nextTop;
				nextTop = topVerts[sliceIndex + 1];
				prevBottom = nextBottom;
				nextBottom = vec3(stackBotRadius * sin(sliceAngle * (sliceIndex + 1)), stackBottomY, stackBotRadius * cos(sliceAngle * (sliceIndex + 1)));
				botVerts.push_back(nextBottom);

				Mesh::Vertex vert1;
				vert1.position = prevTop;
				vert1.normal = normalize(prevTop);
				vert1.texCoord0 = vec2(0, 0);
				vertexArray.push_back(vert1);
				indexArray.push_back(sliceIndex * 6 + VBOindex);

				Mesh::Vertex vert2;
				vert2.position = prevBottom;
				vert2.normal = normalize(prevBottom);
				vert2.texCoord0 = vec2(0, 0);
				vertexArray.push_back(vert2);
				indexArray.push_back(sliceIndex * 6 + 1 + VBOindex);

				Mesh::Vertex vert3;
				vert3.position = nextBottom;
				vert3.normal = normalize(nextBottom);
				vert3.texCoord0 = vec2(0, 0);
				vertexArray.push_back(vert3);
				indexArray.push_back(sliceIndex * 6 + 2 + VBOindex);

				Mesh::Vertex vert4;
				vert4.position = prevTop;
				vert4.normal = normalize(prevTop);
				vert4.texCoord0 = vec2(0, 0);
				vertexArray.push_back(vert4);
				indexArray.push_back(sliceIndex * 6 + 3 + VBOindex);

				Mesh::Vertex vert5;
				vert5.position = nextBottom;
				vert5.normal = normalize(nextBottom);
				vert5.texCoord0 = vec2(0, 0);
				vertexArray.push_back(vert5);
				indexArray.push_back(sliceIndex * 6 + 4 + VBOindex);

				Mesh::Vertex vert6;
				vert6.position = nextTop;
				vert6.normal = normalize(nextTop);
				vert6.texCoord0 = vec2(0, 0);
				vertexArray.push_back(vert6);
				indexArray.push_back(sliceIndex * 6 + 5 + VBOindex);
			}
		}

		stackTopY = stackBottomY;
		stackTopRadius = stackBotRadius;
		topVerts = botVerts;

		nextTop = topVerts[0];
		nextBottom = vec3(0, stackBottomY, 0);
		VBOindex = vertexArray.size();

		for (int sliceIndex = 0; sliceIndex <= SLICES; sliceIndex++) {
			prevTop = nextTop;
			nextTop = topVerts[sliceIndex + 1];

			Mesh::Vertex vert1;
			vert1.position = prevTop;
			vert1.normal = normalize(prevTop);
			vert1.texCoord0 = vec2(0, 0);
			vertexArray.push_back(vert1);
			indexArray.push_back(sliceIndex * 3 + VBOindex);

			Mesh::Vertex vert2;
			vert2.position = nextBottom;
			vert2.normal = normalize(nextBottom);
			vert2.texCoord0 = vec2(0, 0);
			vertexArray.push_back(vert2);
			indexArray.push_back(sliceIndex * 3 + 1 + VBOindex);

			Mesh::Vertex vert3;
			vert3.position = nextTop;
			vert3.normal = normalize(nextTop);
			vert3.texCoord0 = vec2(0, 0);
			vertexArray.push_back(vert3);
			indexArray.push_back(sliceIndex * 3 + 2 + VBOindex);
		}

		const int numVertices = vertexArray.size();
		const int vertexByteSize = sizeof(Mesh::Vertex) * numVertices;
		const int indexByteSize = sizeof(int) * indexArray.size();

		_mesh.reset(new Mesh(textures, GL_TRIANGLES, GL_STATIC_DRAW, vertexByteSize, indexByteSize, 0, vertexArray, indexArray.size(), indexByteSize, &indexArray[0]));
	}

	void Wing::draw(GLSLProgram &shader, const glm::mat4 &modelMatrix) {
		mat4 model = modelMatrix * _localMat;
		shader.setUniform("model_mat", model);
		_mesh->draw(shader);
	}
}