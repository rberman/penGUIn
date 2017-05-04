#include "ExampleApp.h"

using namespace glm;
using namespace std;

namespace basicgraphics {
    ExampleApp::ExampleApp(int argc, char** argv, std::string windowName, int windowWidth, int windowHeight) : BaseApp(argc, argv, windowName, windowWidth, windowHeight)
    {
        const float n = 17.0;
        _ground.reset(new Box(vec3(-n, -2, -n), vec3(n, -2, n), vec4(0.13,0.55,0.13,1)));
        rotation = mat4(1.0);
//		_jimothy.reset(new AnimatedCharacter(WALKING_MOCAP_ASF_PATH, WALKING_MOCAP_AMC_PATH));
        _jimothy.reset(new AnimatedCharacter(DANCE_MOCAP_ASF_PATH, DANCE_MOCAP_AMC_PATH));
		armyMobilized = false;
	}
    
    ExampleApp::~ExampleApp() {}
    
    void ExampleApp::onSimulation(double rdt) {
		_jimothy->nextFrame();
		_jimothy->calculateModelMatrices();
    }
    
    
    void ExampleApp::onRenderGraphics() {
        waddleAngle += waddleAdjust;
        if (waddleAngle > 5.0 || waddleAngle < -5.0) {
            waddleAdjust *= -1.0;
        }
        
        // Setup the view matrix to set where the camera is located
        glm::vec3 eye_world = glm::vec3(0, 7, 15);
//        glm::vec3 eye_world = glm::vec3(0, 4, 4);
        glm::mat4 view = glm::lookAt(eye_world, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        // Setup the projection matrix so that things are rendered in perspective
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)_windowWidth / (GLfloat)_windowHeight, 0.01f, 100.0f);
        // Setup the model matrix
        glm::mat4 model = glm::mat4(1.0);
        
        
       //model = rotation * model;
        
        // Update shader variables
		_shader.use();
        _shader.setUniform("view_mat", view);
        _shader.setUniform("projection_mat", projection);
        _shader.setUniform("model_mat", model);
        _shader.setUniform("eye_world", eye_world);

		_jimothy->simulateMovement();
		if(armyMobilized) {
			cout << "army mobilized" << std::endl;
			int numWide = 5;
			int numHigh = 3;
			float xIncrement = 2.f;
			float zIncrement = 2.f;
			float xRight = 0 - (numWide * xIncrement / 2);
			float zTop = 0 - (numHigh * zIncrement / 2);
			for (int i = 0; i < numWide; i++) {
				float xCoord = xRight + (i * xIncrement);
				for (int j = 0; j < numHigh; j++) {
					float zCoord = zTop + (j * zIncrement);
					/*std::shared_ptr<AnimatedCharacter> newCharacter;
					newCharacter.reset(new AnimatedCharacter(DANCE_MOCAP_ASF_PATH, DANCE_MOCAP_AMC_PATH));
					newCharacter->setLocation(vec3(xCoord, 0, zCoord));*/
					vec3 translation = vec3(xCoord, 0, zCoord);
					mat4 soldierModel = mat4(1.0);
					soldierModel[3] = vec4(translation, 1.0);
					soldierModel = model*soldierModel;
					_jimothy->draw(_shader, soldierModel);
				}
			}
		}
		else {
			_jimothy->draw(_shader, model);
		}

		_ground->draw(_shader, model);
		/*
		_groundShader.use();
		//_groundShader.setUniform("numBladesX", 30);
		//_groundShader.setUniform("numBladesY", 30);
		_groundShader.setUniform("normalLength", 0.2f);
		_groundShader.setUniform("view_mat", view);
		_groundShader.setUniform("projection_mat", projection);
		_groundShader.setUniform("model_mat", model);
		_groundShader.setUniform("eye_world", eye_world);
        _ground->draw(_groundShader, model);*/
    }
    
    void ExampleApp::onEvent(shared_ptr<Event> event) {
        string name = event->getName();
        if (name == "kbd_ESC_down") {
            glfwSetWindowShouldClose(_window, 1);
        }
		else if (name == "kbd_UP_down") {
			std::cout << "up" << std::endl;
			_jimothy->resetASF(WALKING_MOCAP_ASF_PATH, WALKING_MOCAP_AMC_PATH);
			_jimothy->setOrientation(vec3(0, 0, -1));
			_jimothy->setMovement(vec3(0, 0, -.01));
		}
		else if (name == "kbd_RIGHT_down") {
			std::cout << "right" << std::endl;
			_jimothy->resetASF(WALKING_MOCAP_ASF_PATH, WALKING_MOCAP_AMC_PATH);
			_jimothy->setOrientation(vec3(1, 0, 0));
			_jimothy->setMovement(vec3(.01, 0, 0));
		}
		else if (name == "kbd_LEFT_down") {
			std::cout << "left" << std::endl;
			_jimothy->resetASF(WALKING_MOCAP_ASF_PATH, WALKING_MOCAP_AMC_PATH);
			_jimothy->setOrientation(vec3(-1, 0, 0));
			_jimothy->setMovement(vec3(-.01, 0, 0));
		}
		else if (name == "kbd_DOWN_down") {
			std::cout << "down" << std::endl;
			_jimothy->resetASF(WALKING_MOCAP_ASF_PATH, WALKING_MOCAP_AMC_PATH);
			_jimothy->setOrientation(vec3(0, 0, 1));
			_jimothy->setMovement(vec3(0, 0, .01));
		}
		else if (name == "kbd_DOWN_up" || name == "kbd_UP_up" || name == "kbd_RIGHT_up" || name == "kbd_LEFT_up") {
			_jimothy->resetASF(DANCE_MOCAP_ASF_PATH, DANCE_MOCAP_AMC_PATH);
			_jimothy->setMovement(vec3(0, 0, 0));
		}
		else if (name == "kbd_0_down") {
			cout << "zero key pressed" << std::endl;
			armyMobilized = !armyMobilized;
		}
        else if (name == "kbd_1_down") {
            _jimothy->resetASF(DANCE_MOCAP_ASF_PATH, DANCE_MOCAP_AMC_PATH);
        }
        else if (name == "kbd_2_down") {
            _jimothy->resetASF(DANCE_MOCAP_ASF_PATH, PRAIRIE_DOG_MOCAP_AMC_PATH);
        }
        else if (name == "kbd_3_down") {
            _jimothy->resetASF(DANCE_MOCAP_ASF_PATH, GHOST_MOCAP_AMC_PATH);
        }
        else if (name == "kbd_4_down") {
            _jimothy->resetASF(DANCE_MOCAP_ASF_PATH, SUPERHERO_MOCAP_AMC_PATH);
        }
        else if (name == "kbd_5_down") {
            _jimothy->resetASF(DANCE_MOCAP_ASF_PATH, DEVIL_MOCAP_AMC_PATH);
        }
        else if (name == "kbd_6_down") {
            _jimothy->resetASF(DANCE_MOCAP_ASF_PATH, ROADRUNNER_MOCAP_AMC_PATH);
        }
        else if (name == "kbd_7_down") {
            _jimothy->resetASF(DANCE_MOCAP_ASF_PATH, GENIE_MOCAP_AMC_PATH);
        }
        else if (name == "kbd_8_down") {
            _jimothy->resetASF(CARTWHEEL_MOCAP_ASF_PATH, CARTWHEEL_MOCAP_AMC_PATH);
        }
        else if (name == "kbd_9_down") {
            _jimothy->resetASF(CARTWHEEL_MOCAP_ASF_PATH, HOP_MOCAP_AMC_PATH);
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
