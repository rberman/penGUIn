//
//  Foot.cpp
//  Basic_Graphics
//
//  Created by Ruthie Berman on 4/26/17.
//
//

#include "Foot.h"

namespace basicgraphics {
    
    Foot::Foot(float length, glm::vec3 legTop) {
        // Note: TEXTURE_PATH is set in config.h
        /**shared_ptr<Texture> tex = Texture::create2DTextureFromFile(TEXTURE_PATH);
         tex->setTexParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
         tex->setTexParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
         tex->setTexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         tex->setTexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         textures.push_back(tex);**/
        _localMat = mat4(1.0);
        _localMat[3] = vec4(legTop, 1.0);
        setupGeometry(length);
    }
    
    void Foot::setupGeometry(float length) {
        std::vector<Mesh::Vertex> cpuVertexArray;
        std::vector<int> cpuIndexArray;
        Mesh::Vertex vert;
        
        float legLength = length*0.75;
//        float footLength = length * 0.25;
        float numLegLenthVertices = 80;
        float legVerticalTriangleLength = legLength / numLegLenthVertices;
        float numCircleVertices = 40;
        float legRadius = length * 0.15;
        float angleDiff = 2 * glm::pi<float>() / numCircleVertices;
        
        int counter = 0;
        
        for (int i = 0; i < numLegLenthVertices; i++){ //go down the cylinder
            float upperY = -legVerticalTriangleLength * i;
            float lowerY = upperY - legVerticalTriangleLength;
            for (int j = 0; j < numCircleVertices; j++) { //go around the cylinder. Each loop draws two triangles to make a square
                float currAngle = angleDiff * j;
                float nextAngle = currAngle + angleDiff;
                //upper left vertex
                vert.position = vec3(legRadius*cos(currAngle), upperY, legRadius * sin(currAngle));
                vert.normal = vert.position;
                cpuVertexArray.push_back(vert);
                cpuIndexArray.push_back(counter);
                counter++;
                
                //upper right vertex
                vert.position = vec3(legRadius*cos(nextAngle), upperY, legRadius*sin(nextAngle));
                vert.normal = vert.position;
                cpuVertexArray.push_back(vert);
                cpuIndexArray.push_back(counter);
                counter++;
                
                //lower left vertex
                vert.position = vec3(legRadius*cos(currAngle), lowerY, legRadius*sin(currAngle));
                vert.normal = vert.position;
                cpuVertexArray.push_back(vert);
                cpuIndexArray.push_back(counter);
                counter++;
                
                //second triangle
                
                //lower left vertex
                cpuVertexArray.push_back(vert);
                cpuIndexArray.push_back(counter);
                counter++;
                
                //lower right vertex
                vert.position = vec3(legRadius*cos(nextAngle), lowerY, legRadius*sin(nextAngle));
                vert.normal = vert.position;
                cpuVertexArray.push_back(vert);
                cpuIndexArray.push_back(counter);
                counter++;
                
                //upper right vertex
                vert.position = vec3(legRadius*cos(nextAngle), upperY, legRadius*sin(nextAngle));
                vert.normal = vert.position;
                cpuVertexArray.push_back(vert);
                cpuIndexArray.push_back(counter);
                counter++;
            }
        }
        //leg drawn, now draw foot
        //hardcoded into a simple foot now. Maybe change later, but maybe just texture, depending on aesthetic desire
        float footHeight = .25 * length;
        float footTopWidth = 3. * legRadius;
        float footBottomWidth = 1.5 * footTopWidth;
        float footBackZ = -legRadius;
        float footFrontZ = 1.5*legRadius;
        float legBottom = -legLength;
        
        //top of foot, two triangles
        float footTopLeft = -footTopWidth / 2.;
        float footTopRight = footTopWidth / 2.;
        vert.position = vec3(footTopRight, legBottom, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footTopLeft, legBottom, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footTopLeft, legBottom, footFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        //second triangle of top
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footTopRight, legBottom, footFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footTopRight, legBottom, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        //end top of foot
        //back of foot
        float footBottomLeft = -footBottomWidth / 2.;
        float footBottomRight = footBottomWidth / 2.;
        float footBottomY = legBottom - footHeight;
        vert.position = vec3(footTopLeft, legBottom, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footBottomLeft, footBottomY, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(0, footBottomY, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        //new triangle
        vert.position = vec3(footTopLeft, legBottom, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(0, footBottomY, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footTopRight, legBottom, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        //final back triangle
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(0, footBottomY, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footBottomRight, footBottomY, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        //end foot back
        
        //start foot front / toes
        float toeLength = (footFrontZ - footBackZ) / 2;
        float toeFrontZ = footFrontZ + toeLength;
        
        vert.position = vec3(footTopLeft, legBottom, footFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footBottomLeft, footBottomY, toeFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(0, footBottomY, toeFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        //new triangle
        vert.position = vec3(footTopLeft, legBottom, footFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(0, footBottomY, toeFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footTopRight, legBottom, footFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        //new triangle
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(0, footBottomY, toeFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footBottomRight, footBottomY, toeFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        //end toe
        
        //start left side
        vert.position = vec3(footTopLeft, legBottom, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footBottomLeft, footBottomY, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footTopLeft, legBottom, footFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        //new triangle
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footBottomLeft, footBottomY, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footBottomLeft, footBottomY, footFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        //new triangle
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footBottomLeft, footBottomY, toeFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footTopLeft, legBottom, footFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        //end foot left side
        
        //start right side
        vert.position = vec3(footTopRight, legBottom, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footBottomRight, footBottomY, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footTopRight, legBottom, footFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        //new triangle
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footBottomRight, footBottomY, footBackZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footBottomRight, footBottomY, footFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        //new triangle
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footBottomRight, footBottomY, toeFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        
        vert.position = vec3(footTopRight, legBottom, footFrontZ);
        vert.normal = vert.position;
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(counter);
        counter++;
        //end foot left side
        
        int numVertices = cpuVertexArray.size();
        int cpuVertexByteSize = sizeof(Mesh::Vertex) * numVertices;
        int cpuIndexByteSize = sizeof(int) * cpuIndexArray.size();
        _mesh.reset(new Mesh(textures, GL_TRIANGLES, GL_STATIC_DRAW,
                             cpuVertexByteSize, cpuIndexByteSize, 0, cpuVertexArray,
                             cpuIndexArray.size(), cpuIndexByteSize, &cpuIndexArray[0]));
        
        
    }
    
    void Foot::draw(GLSLProgram &shader, const glm::mat4 &modelMatrix) {
        // TODO: Draw your mesh.
        mat4 model = modelMatrix * _localMat;
        shader.setUniform("model_mat", model);
        _mesh->setMaterialColor(vec4(1,0.5,0,1));
        _mesh->draw(shader);
    }
}
