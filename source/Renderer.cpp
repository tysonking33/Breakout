#include "../includes/Renderer.h"

// Constructor: Initializes the renderer by setting up the rendering data.
Renderer::Renderer()
{
    initRenderData();
}

// Initializes the rendering data, such as vertex arrays and buffers.
void Renderer::initRenderData()
{
    GLfloat vertices[] = {
        -0.15f, -0.05f, // Bottom-left corner
        0.05f, -0.05f,  // Bottom-right corner
        0.05f, 0.05f,   // Top-right corner
        -0.15f, 0.05f   // Top-left corner
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// Draws a shape using the given shader, position, and angle.
void Renderer::draw(Shader& shader, glm::vec2 position, float angle)
{
    shader.use();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
    transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

    GLuint modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}
