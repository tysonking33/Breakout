#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Player.h"
#include "Shader.h"
#include "Renderer.h"

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


    Player player1;
    Player player2;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    void init();
    void processInput();
    void update();
    void render();
    void cleanUp();
};

#endif
