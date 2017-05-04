//
//  Eye.cpp
//  Basic_Graphics
//
//  Created by Ruthie Berman on 5/3/17.
//
//

#include "Eye.h"

namespace basicgraphics {
    using namespace std;
    using namespace glm;

    
    Eye::Eye(float radius, vec3 position) {

        createEye(radius, position);
    }
    
    void Eye::createEye(float radius, vec3 position) {
        _eye.reset(new Sphere(position, radius, vec4(1,1,1,1)));
        vec3 pupilPosition = vec3(position.x, position.y, position.z + radius + .05);
        float zCoord = position.z + radius;
        createPupil(radius * 0.5, pupilPosition, zCoord);
    }
    
    void Eye::createPupil(float radius, vec3 position, float zCoord) {
        std::vector<Mesh::Vertex> vertexArray;
        std::vector<int> indexArray;
        vec3 nextPosition;
        const int SLICES = 30;
        const float angle = 2.0 * glm::pi<float>() / SLICES;
        
        Mesh::Vertex vert;
        vert.position = position;
        vert.normal = vec3(0,0,1);
        vertexArray.push_back(vert);
        indexArray.push_back(0);
        
        for (int i = 0; i <= SLICES; i++) {
            nextPosition = vec3(radius * cos(i * angle) + position.x,
                                radius * sin(i * angle) + position.y,
                                zCoord);
            
            Mesh::Vertex vert1;
            vert1.position = nextPosition;
            vert1.normal = vec3(0,0,1);
            vertexArray.push_back(vert1);
            indexArray.push_back(i + 1);
        }
        
        const int numVertices = vertexArray.size();
        const int vertexByteSize = sizeof(Mesh::Vertex) * numVertices;
        const int indexByteSize = sizeof(int) * indexArray.size();
        _pupil.reset(new Mesh(textures, GL_TRIANGLE_FAN, GL_STATIC_DRAW, vertexByteSize, indexByteSize, 0, vertexArray, indexArray.size(), indexByteSize, &indexArray[0]));
        _pupil->setMaterialColor(vec4(0,0,0,1));
    }
    
    
    void Eye::draw(GLSLProgram &shader, const glm::mat4 &modelMatrix) {
        _eye->draw(shader, modelMatrix);
        _pupil->draw(shader);

    }

}
