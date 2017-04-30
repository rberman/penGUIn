#include "ExampleApp.h"

using namespace glm;
using namespace std;

namespace basicgraphics {
    ExampleApp::ExampleApp(int argc, char** argv, std::string windowName, int windowWidth, int windowHeight) : BaseApp(argc, argv, windowName, windowWidth, windowHeight)
    {

        _head.reset(new Head(0.5));
        _body.reset(new Body(0.5));
        _leftFoot.reset(new Foot(0.5, vec3(0.15,-0.5,0)));
        _rightFoot.reset(new Foot(0.5, vec3(-0.15,-0.5,0)));
        _leftWing.reset(new Wing());
        _rightWing.reset(new Wing());
        
        _angle = 1.0;
        waddleAngle = 0.0;
        waddleAdjust = 0.5;
        
        rotation = mat4(1.0);
		AnimatedCharacter character = AnimatedCharacter(WALKING_MOCAP_ASF_PATH, WALKING_MOCAP_AMC_PATH);
        
    }
    
    ExampleApp::~ExampleApp() {}
    
    void ExampleApp::onSimulation(double rdt) {
        
    }
    
    
    void ExampleApp::onRenderGraphics() {
        waddleAngle += waddleAdjust;
        if (waddleAngle > 5.0 || waddleAngle < -5.0) {
            waddleAdjust *= -1.0;
        }
        
        // Setup the view matrix to set where the camera is located
        glm::vec3 eye_world = glm::vec3(0, 0, 5);
        glm::mat4 view = glm::lookAt(eye_world, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        
        // Setup the projection matrix so that things are rendered in perspective
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)_windowWidth / (GLfloat)_windowHeight, 0.01f, 100.0f);
        // Setup the model matrix
        glm::mat4 model = glm::mat4(1.0);
        
        
//        model = rotation * model;
        
        
        // Update shader variables
        _shader.setUniform("view_mat", view);
        _shader.setUniform("projection_mat", projection);
        _shader.setUniform("model_mat", model);
        _shader.setUniform("eye_world", eye_world);
        
        mat4 identity = mat4(1.0);
//        mat4 waddle = toMat4(angleAxis(radians(waddleAngle), vec3(0,0,1)));
        mat4 headShift = translate(mat4(1.0), vec3(0, 1, 0));
//        mat4 waddleShift = waddle * headShift * mat4(1.0);
		mat4 leftWingShift = translate(mat4(1.0), vec3(-0.5, 0, 0));
		mat4 rightWingShift = translate(mat4(1.0), vec3(0.5, 0, 0));

        _body->draw(_shader, identity);
        _head->draw(_shader, headShift);
        _leftFoot->draw(_shader, identity);
        _rightFoot->draw(_shader, identity);
		_leftWing->draw(_shader, leftWingShift);
		_rightWing->draw(_shader, rightWingShift);
    }
    
    void ExampleApp::onEvent(shared_ptr<Event> event) {
        string name = event->getName();
        if (name == "kbd_ESC_down") {
            glfwSetWindowShouldClose(_window, 1);
        }
        // Rotate the earth when the user clicks and drags the mouse
        else if (name == "mouse_btn_left_down") {
            mouseDown = true;
            lastMousePos = event->get2DData();
        }
        else if (name == "mouse_btn_left_up") {
            mouseDown = false;
        }
        else if (name == "mouse_pointer") {
            // TODO: Update the "rotation" matrix based on how the user has dragged the mouse
            // Note: the mouse movement since the last frame is stored in dxy.
            if (mouseDown) {
                vec2 dxy = vec2(event->get2DData()) - lastMousePos;
                float rotationScale = .5;//in degrees
                float magnitude = glm::length(dxy);
                vec3 rotationVector = normalize(vec3(dxy.y, dxy.x, 0));
                mat4 newRotation = toMat4(angleAxis(radians(rotationScale*magnitude), rotationVector));
                rotation = newRotation * rotation;
                lastMousePos = vec2(event->get2DData());
            }
        }
    }
}
