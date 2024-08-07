#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include "Shader.h"

class Renderer
{
    public:
        Renderer();
        void drawPlayer(Shader& shader, glm::vec2 position, float angle);
        void drawWall(Shader& shader);
        void drawCopAI(Shader& shader, glm::vec2 position, float angle);

    private:
        GLuint playerVAO, playerVBO;
        GLuint wallVAO, wallVBO;  // For walls
        GLuint copVAO, copVBO;  // For walls

        void initRenderPlayerData();
        void initRenderWallData();
        void initRenderCopAIData();
};


#endif