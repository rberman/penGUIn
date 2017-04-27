//
//  Wing.cpp
//  Basic_Graphics
//
//  Created by Ruthie Berman on 4/26/17.
//
//

#include "Wing.h"


namespace basicgraphics {
    using namespace std;
    using namespace glm;
    
    Wing::Wing() {
        //        shared_ptr<Texture> tex = Texture::create2DTextureFromFile(TEXTURE_PATH);
        //        tex->setTexParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
        //        tex->setTexParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
        //        tex->setTexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //        tex->setTexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //        textures.push_back(tex);
        _localMat = mat4(1.0);
        createWing(0.5);
    }
    
    void Wing::createWing(float radius) {
        std::vector<Mesh::Vertex> vertexArray;
        std::vector<int> indexArray;
        
        
        Mesh::Vertex vert1;
        vert1.position = vec3(0, 0, 0.5);
        vert1.normal = normalize(vec3(1,0,0));
        vert1.texCoord0 = vec2(0,0);
        vertexArray.push_back(vert1);
        indexArray.push_back(0);
        
        Mesh::Vertex vert2;
        vert2.position = vec3(0.2, -0.5, 0);
        vert2.normal = normalize(vec3(1,0,0));
        vert2.texCoord0 = vec2(0,0);
        vertexArray.push_back(vert2);
        indexArray.push_back(1);
        
        Mesh::Vertex vert3;
        vert3.position = vec3(0.2, 0, -0.5);
        vert3.normal = normalize(vec3(1,0,0));
        vert3.texCoord0 = vec2(0,0);
        vertexArray.push_back(vert3);
        indexArray.push_back(2);
        
        Mesh::Vertex vert4;
        vert4.position = vec3(0.2, -0.5, 0);
        vert4.normal = normalize(vec3(1,0,0));
        vert4.texCoord0 = vec2(0,0);
        vertexArray.push_back(vert4);
        indexArray.push_back(3);
        
        Mesh::Vertex vert5;
        vert5.position = vec3(0.2, 0, -0.5);
        vert5.normal = normalize(vec3(1,0,0));
        vert5.texCoord0 = vec2(0,0);
        vertexArray.push_back(vert5);
        indexArray.push_back(4);
        
        Mesh::Vertex vert6;
        vert6.position = vec3(0, 0, -0.5);
        vert6.normal = normalize(vec3(1,0,0));
        vert6.texCoord0 = vec2(0,0);
        vertexArray.push_back(vert6);
        indexArray.push_back(5);

        
        const int numVertices = vertexArray.size();
        const int vertexByteSize = sizeof(Mesh::Vertex) * numVertices;
        const int indexByteSize = sizeof(int) * indexArray.size();
        _mesh.reset(new Mesh(textures, GL_TRIANGLES, GL_STATIC_DRAW, vertexByteSize, indexByteSize, 0, vertexArray, indexArray.size(), indexByteSize, &indexArray[0]));
    }
    
    void Wing::draw(GLSLProgram &shader, const glm::mat4 &modelMatrix) {
        // TODO: Draw your mesh.
        mat4 model = modelMatrix * _localMat;
        shader.setUniform("model_mat", model);
        _mesh->draw(shader);
    }
}
