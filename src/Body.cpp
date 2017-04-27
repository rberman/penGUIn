//
//  Body.cpp
//  Basic_Graphics
//
//  Created by Ruthie Berman on 4/26/17.
//
//

#include "Body.h"


namespace basicgraphics {
    using namespace std;
    using namespace glm;
    
    Body::Body(float radius) {
//        shared_ptr<Texture> tex = Texture::create2DTextureFromFile(TEXTURE_PATH);
//        tex->setTexParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
//        tex->setTexParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
//        tex->setTexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        tex->setTexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        textures.push_back(tex);
        
        _localMat = mat4(1.0);
        createBody(radius);
    }
    
    void Body::createBody(float radius) {
        const int STACKS = 20;
        const int SLICES = 40;
        
        std::vector<Mesh::Vertex> vertexArray;
        std::vector<int> indexArray;
        
        const float stackAngle = glm::pi<float>() / STACKS;
        const float sliceAngle = 2.0 * glm::pi<float>() / SLICES;
        const float texStackHeight = 1.0 / STACKS;
        const float texSliceWidth = 1.0 / SLICES;
        const float scaleFactor = 1.5;
        
        std::vector<vec3> topVerts;
        std::vector<vec3> bottomVerts;
        float stackTopY;
        float stackBottomY;
        float stackTopRadius;
        float stackBottomRadius;
        
        vec3 prevTop;
        vec3 prevBottom;
        vec3 nextTop;
        vec3 nextBottom;
        
        int VBOIndex;
        
        // Draw top cone of head
        stackTopY = radius;
        stackBottomY = radius * cos(stackAngle);
        stackBottomRadius = sqrt(pow(radius, 2) - pow(stackBottomY, 2));
        stackTopY *= scaleFactor;
        stackBottomY *= scaleFactor;
        nextTop = vec3(0, stackTopY, 0);
        nextBottom = vec3(0, stackBottomY, stackBottomRadius);
        bottomVerts.push_back(nextBottom);
        
        for (int slIndex = 0; slIndex <= SLICES; slIndex++) {
            prevBottom = nextBottom;
            nextBottom = vec3(stackBottomRadius * sin(sliceAngle * (slIndex + 1)), stackBottomY, stackBottomRadius * cos(sliceAngle * (slIndex + 1)));
            bottomVerts.push_back(nextBottom);
            
            Mesh::Vertex vert1;
            vert1.position = nextTop;
            vert1.normal = normalize(nextTop);
            vert1.texCoord0 = vec2(slIndex * texSliceWidth, 1.0);
            vertexArray.push_back(vert1);
            indexArray.push_back(slIndex * 3);
            
            Mesh::Vertex vert2;
            vert2.position = prevBottom;
            vert2.normal = normalize(prevBottom);
            vert2.texCoord0 = vec2(slIndex * texSliceWidth, 1.0 - texStackHeight);
            vertexArray.push_back(vert2);
            indexArray.push_back(slIndex * 3 + 1);
            
            Mesh::Vertex vert3;
            vert3.position = nextBottom;
            vert3.normal = normalize(nextBottom);
            vert3.texCoord0 = vec2((slIndex + 1) * texSliceWidth, 1.0 - texStackHeight);
            vertexArray.push_back(vert3);
            indexArray.push_back(slIndex * 3 + 2);
        }
        
        // Draw body of head
        for (int stIndex = 1; stIndex < STACKS - 5; stIndex++) {
            stackTopY = stackBottomY;
            stackBottomY = radius * cos(stackAngle * (stIndex + 1));
            stackTopRadius = stackBottomRadius;
            stackBottomRadius = sqrt(pow(radius, 2) - pow(stackBottomY, 2));
            stackBottomY *= scaleFactor;
            
            topVerts = bottomVerts;
            bottomVerts.clear();
            nextTop = topVerts[0];
            nextBottom = vec3(0, stackBottomY, stackBottomRadius);
            bottomVerts.push_back(nextBottom);
            
            VBOIndex = vertexArray.size();
            
            for (int slIndex = 0; slIndex <= SLICES; slIndex++) {
                // Set the triangle points
                prevTop = nextTop;
                nextTop = topVerts[slIndex + 1];
                prevBottom = nextBottom;
                nextBottom = vec3(stackBottomRadius * sin(sliceAngle * (slIndex + 1)), stackBottomY, stackBottomRadius * cos(sliceAngle * (slIndex + 1)));
                bottomVerts.push_back(nextBottom);
                
                Mesh::Vertex vert1;
                vert1.position = prevTop;
                vert1.normal = normalize(prevTop);
                vert1.texCoord0 = vec2(slIndex * texSliceWidth, 1 - stIndex * texStackHeight);
                vertexArray.push_back(vert1);
                indexArray.push_back(slIndex * 6 + VBOIndex);
                
                Mesh::Vertex vert2;
                vert2.position = prevBottom;
                vert2.normal = normalize(prevBottom);
                vert2.texCoord0 = vec2(slIndex * texSliceWidth, 1 - (stIndex + 1) * texStackHeight);
                vertexArray.push_back(vert2);
                indexArray.push_back(slIndex * 6 + 1 + VBOIndex);
                
                Mesh::Vertex vert3;
                vert3.position = nextBottom;
                vert3.normal = normalize(nextBottom);
                vert3.texCoord0 = vec2((slIndex + 1) * texSliceWidth, 1 - (stIndex + 1) * texStackHeight);
                vertexArray.push_back(vert3);
                indexArray.push_back(slIndex * 6 + 2 + VBOIndex);
                
                Mesh::Vertex vert4;
                vert4.position = prevTop;
                vert4.normal = normalize(prevTop);
                vert4.texCoord0 = vec2(slIndex * texSliceWidth, 1 - stIndex * texStackHeight);
                vertexArray.push_back(vert4);
                indexArray.push_back(slIndex * 6 + 3 + VBOIndex);
                
                Mesh::Vertex vert5;
                vert5.position = nextBottom;
                vert5.normal = normalize(nextBottom);
                vert5.texCoord0 = vec2((slIndex + 1) * texSliceWidth, 1 - (stIndex + 1) * texStackHeight);
                vertexArray.push_back(vert5);
                indexArray.push_back(slIndex * 6 + 4 + VBOIndex);
                
                Mesh::Vertex vert6;
                vert6.position = nextTop;
                vert6.normal = normalize(nextTop);
                vert6.texCoord0 = vec2((slIndex + 1) * texSliceWidth, 1 - stIndex * texStackHeight);
                vertexArray.push_back(vert6);
                indexArray.push_back(slIndex * 6 + 5 + VBOIndex);
                
                
            }
        }
//        for (Mesh::Vertex vert : vertexArray) {
//            //            vec3 pos = vert.position;
//            //            std::cout << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
//            vec2 tex = vert.texCoord0;
//            std::cout << tex.x << ", " << tex.y << std::endl;
//        }
        
        // Create bottom cone of head
        stackTopY = stackBottomY;
        stackTopRadius = stackBottomRadius;
        topVerts = bottomVerts;
        
        nextTop = topVerts[0];
        nextBottom = vec3(0, stackBottomY, 0);
        VBOIndex = vertexArray.size();
        
        for (int slIndex = 0; slIndex <= SLICES; slIndex++) {
            // Set the triangle points
            prevTop = nextTop;
            nextTop = topVerts[slIndex + 1];
            
            Mesh::Vertex vert1;
            vert1.position = prevTop;
            vert1.normal = normalize(prevTop);
            vert1.texCoord0 = vec2(slIndex * texSliceWidth, texStackHeight);
            vert1.texCoord0 = vec2(0.5, 0.5);
            vertexArray.push_back(vert1);
            indexArray.push_back(slIndex * 3 + VBOIndex);
            
            Mesh::Vertex vert2;
            vert2.position = nextBottom;
            vert2.normal = normalize(nextBottom);
            vert2.texCoord0 = vec2(slIndex * texSliceWidth, 0);
            vert2.texCoord0 = vec2(0.5, 0.5);
            vertexArray.push_back(vert2);
            indexArray.push_back(slIndex * 3 + 1 + VBOIndex);
            
            Mesh::Vertex vert3;
            vert3.position = nextTop;
            vert3.normal = normalize(nextTop);
            vert3.texCoord0 = vec2((slIndex + 1) * texSliceWidth, texStackHeight);
            vert3.texCoord0 = vec2(0.5, 0.5);
            vertexArray.push_back(vert3);
            indexArray.push_back(slIndex * 3 + 2 + VBOIndex);
        }
        
        const int numVertices = vertexArray.size();
        const int vertexByteSize = sizeof(Mesh::Vertex) * numVertices;
        const int indexByteSize = sizeof(int) * indexArray.size();
        _mesh.reset(new Mesh(textures, GL_TRIANGLES, GL_STATIC_DRAW, vertexByteSize, indexByteSize, 0, vertexArray, indexArray.size(), indexByteSize, &indexArray[0]));
    }
    
    void Body::draw(GLSLProgram &shader, const glm::mat4 &modelMatrix) {
        // TODO: Draw your mesh.
        mat4 model = modelMatrix * _localMat;
        shader.setUniform("model_mat", model);
        _mesh->draw(shader);
    }
}
