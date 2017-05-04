#ifndef ExampleApp_h
#define ExampleApp_h

#include "BaseApp.h"
#include "Head.h"
#include "Body.h"
#include "Foot.h"
#include "Wing.h"
#include "AnimatedCharacter.h"
#include <string.h>
#include <glm/glm/gtc/matrix_transform.hpp>
#include "config.h"
#include <iostream>
#include <sstream>
#include <fstream>

namespace basicgraphics {
    
    class ExampleApp : public BaseApp {
    public:
        ExampleApp(int argc, char** argv, std::string windowName, int windowWidth, int windowHeight);
        ~ExampleApp();
        
    private:
        std::unique_ptr<Mesh> _mesh;
        std::vector< std::shared_ptr<Texture> > textures;
        
        std::unique_ptr<Head> _head;
        std::unique_ptr<Body> _body;
        std::unique_ptr<Foot> _leftFoot;
        std::unique_ptr<Foot> _rightFoot;
        std::unique_ptr<Wing> _leftWing;
        std::unique_ptr<Wing> _rightWing;

		std::shared_ptr<AnimatedCharacter> _jimothy;
		bool armyMobilized;
        std::unique_ptr<Box> _ground;

        glm::mat4 rotation;
        bool mouseDown;
        glm::vec2 lastMousePos;
        
        float waddleAngle;
        float waddleAdjust;
        
        void onRenderGraphics() override;
        void onSimulation(double rdt) override;
        void onEvent(std::shared_ptr<Event> event) override;
    };
}

#endif
