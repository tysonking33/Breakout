#include "../includes/Renderer.h"

// Constructor: Initializes the renderer by setting up the rendering data.
Renderer::Renderer()
{
    initRenderPlayerData();
    initRenderWallData();
    initRenderCopAIData();
}

// Initializes the rendering data, such as vertex arrays and buffers.
void Renderer::initRenderPlayerData()
{
    // Define the vertex data for the player's shape.
    GLfloat playerVertices[] = {
        -0.15f, -0.05f, // Bottom-left corner
        0.05f, -0.05f,  // Bottom-right corner
        0.05f, 0.05f,   // Top-right corner
        -0.15f, 0.05f   // Top-left corner
    };

    // Generate one vertex array object (VAO) and store its ID in playerVAO.
    glGenVertexArrays(1, &playerVAO);
    
    // Generate one vertex buffer object (VBO) and store its ID in playerVBO.
    glGenBuffers(1, &playerVBO);

    // Bind the VAO to set it as the current vertex array object.
    glBindVertexArray(playerVAO);

    // Bind the VBO to set it as the current vertex buffer object.
    glBindBuffer(GL_ARRAY_BUFFER, playerVBO);

    // Upload the vertex data to the GPU.
    // The data is stored in the GL_ARRAY_BUFFER and is used to draw the player's shape.
    glBufferData(GL_ARRAY_BUFFER, sizeof(playerVertices), playerVertices, GL_STATIC_DRAW);

    // Define the vertex attributes for the vertex shader.
    // This tells OpenGL how to interpret the vertex data in the VBO.
    // The first parameter (0) is the index of the vertex attribute.
    // The second parameter (2) specifies the number of components per attribute (x and y coordinates).
    // The third parameter (GL_FLOAT) specifies the data type of the components.
    // The fourth parameter (GL_FALSE) specifies whether fixed-point data should be normalized.
    // The fifth parameter (2 * sizeof(GLfloat)) specifies the byte offset between consecutive vertex attributes.
    // The last parameter ((GLvoid *)0) specifies the offset of the first component in the buffer.
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)0);

    // Enable the vertex attribute array at index 0.
    // This makes the vertex attribute array active so that it will be used in drawing operations.
    glEnableVertexAttribArray(0);

    // Unbind the VBO to avoid accidentally modifying it.
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind the VAO to avoid accidentally modifying it.
    glBindVertexArray(0);
}


void Renderer::initRenderWallData()
{
    GLfloat wallVertices[] = {
        -1.0f, -0.01f,
        1.0f, -0.01f,
        1.0f, 0.01f,
        -1.0f, 0.01f
    };

    glGenVertexArrays(1, &wallVAO);
    glGenBuffers(1, &wallVBO);

    glBindVertexArray(wallVAO);

    glBindBuffer(GL_ARRAY_BUFFER, wallVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wallVertices), wallVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}


// Initializes the rendering data, such as vertex arrays and buffers.
void Renderer::initRenderCopAIData()
{
    // Define the vertex data for the player's shape.
    GLfloat copVertices[] = {
        -0.15f, -0.05f, // Bottom-left corner
        0.05f, -0.05f,  // Bottom-right corner
        0.05f, 0.05f,   // Top-right corner
        -0.15f, 0.05f   // Top-left corner
    };

    // Generate one vertex array object (VAO) and store its ID in copVAO.
    glGenVertexArrays(1, &copVAO);
    
    // Generate one vertex buffer object (VBO) and store its ID in copVBO.
    glGenBuffers(1, &copVBO);

    // Bind the VAO to set it as the current vertex array object.
    glBindVertexArray(copVAO);

    // Bind the VBO to set it as the current vertex buffer object.
    glBindBuffer(GL_ARRAY_BUFFER, copVBO);

    // Upload the vertex data to the GPU.
    // The data is stored in the GL_ARRAY_BUFFER and is used to draw the player's shape.
    glBufferData(GL_ARRAY_BUFFER, sizeof(copVertices), copVertices, GL_STATIC_DRAW);

    // Define the vertex attributes for the vertex shader.
    // This tells OpenGL how to interpret the vertex data in the VBO.
    // The first parameter (0) is the index of the vertex attribute.
    // The second parameter (2) specifies the number of components per attribute (x and y coordinates).
    // The third parameter (GL_FLOAT) specifies the data type of the components.
    // The fourth parameter (GL_FALSE) specifies whether fixed-point data should be normalized.
    // The fifth parameter (2 * sizeof(GLfloat)) specifies the byte offset between consecutive vertex attributes.
    // The last parameter ((GLvoid *)0) specifies the offset of the first component in the buffer.
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)0);

    // Enable the vertex attribute array at index 0.
    // This makes the vertex attribute array active so that it will be used in drawing operations.
    glEnableVertexAttribArray(0);

    // Unbind the VBO to avoid accidentally modifying it.
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind the VAO to avoid accidentally modifying it.
    glBindVertexArray(0);
}


// Draws a shape using the given shader, position, and angle.
void Renderer::drawPlayer(Shader& shader, glm::vec2 position, float angle)
{
    glm::vec4 color(1.0f, 0.0f, 1.0f, 1.0f);

    shader.use();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
    transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

    GLuint modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));

    GLuint colorLoc = glGetUniformLocation(shader.ID, "ourColor");
    glUniform4fv(colorLoc, 1, glm::value_ptr(color));

    glBindVertexArray(playerVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}

void Renderer::drawWall(Shader& shader)
{
    glm::vec4 color(0.0f, 1.0f, 1.0f, 1.0f);

    shader.use();

    GLuint colorLoc = glGetUniformLocation(shader.ID, "ourColor");
    glUniform4fv(colorLoc, 1, glm::value_ptr(color));

    // Ensure no transformation matrix is applied to the wall
    glBindVertexArray(wallVAO);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error after binding VAO: " << error << std::endl;
    }

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error during draw call: " << error << std::endl;
    }

    glBindVertexArray(0);
}


// Draws a shape using the given shader, position, and angle.
void Renderer::drawCopAI(Shader& shader, glm::vec2 position, float angle)
{
    glm::vec4 color(0.5f, 0.5f, 0.5f, 1.0f);
    shader.use();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
    transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

    GLuint modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));

    GLuint colorLoc = glGetUniformLocation(shader.ID, "ourColor");
    glUniform4fv(colorLoc, 1, glm::value_ptr(color));

    glBindVertexArray(copVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}