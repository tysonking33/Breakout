#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Player.h"
#include "Shader.h"
#include "Renderer.h"
#include "CopAI.h"

#include <cstdlib> 
#include <iostream> 

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    GLFWwindow* window;
    Shader* shader;
    Renderer* renderer;
    GLuint WIDTH = 800, HEIGHT = 600;

    float deltaTime;


    Player player1;
    Player player2;
    CopAI  cop1;
    CopAI  cop2;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    void init();
    void processInput();
    void update();
    void render();
    void cleanUp();
    static void glfwSetFrameSizeCallback(GLFWwindow *window, int width, int height);

};

#endif
