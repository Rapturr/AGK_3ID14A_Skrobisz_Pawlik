#ifndef ENGINE_HPP
#define ENGINE_HPP

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>

// Include GLEW
#include <glm.hpp>
#include <ext.hpp>
#include <glad/glad.h>


// Include GLFW
#include <glfw3.h>

// Include GLM
#include <gtc/matrix_transform.hpp> 
using namespace glm;

#include "common/controls.hpp"
#include "scenes/scenes.hpp"

#include "common/shader.hpp"

class engine
{
private:
    GLFWwindow* window;
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;
    int scenenumber;
    
    sceneSkyBox skyboxScene;
    
    int sceneChoice = 0;
    
public:
    void init();
    void inputHandler();
    void run();
    engine() {}
    ~engine() {}
};

#endif