/*!
 *  App.h
 *  
 * This represents the main application. It creates an opengl window and starts rendering when run() is called.
 */

#ifndef App_h
#define App_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_access.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include "GLSLProgram.h"
#include "Model.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Box.h"
#include "Line.h"

class App
{
public:
    
    App(int argc, char** argv);
    ~App();
    
    /*!
     * Starts the main draw loop
     */
    void run();
    
    // Callbacks for user input
    static void error_callback(int error, const char* description);
    static void window_size_callback(GLFWwindow* window, int width, int height);
    static void window_pos_callback(GLFWwindow* window, int xpos, int ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double x, double y);
    static void cursor_enter_callback(GLFWwindow* window, int entered);
    static void scroll_callback(GLFWwindow* window, double x, double y);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
private:
    GLFWwindow* _window; // Pointer to the window
    GLSLProgram _shader; // A basic shader to use.
    
    //Example of how to create a pointer to a model
    std::unique_ptr<Model> _model;
    
    
    /*!
     * Called from the run loop. You should put any of your drawing code in this member function.
     */
    void draw(const int windowWidth, const int windowHeight);
    
    // Keypress helper methods
    static std::string getKeyName(int key);
    static std::string getKeyValue(int key, int mods);
    static std::string getActionName(int action);
    static std::string getButtonName(int button);
    static std::string getModsName(int mods);
    
};

#endif /* App_h */
