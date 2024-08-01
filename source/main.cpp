#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "../includes/Player.h"

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Shader program
GLuint shaderProgram;

// Player object
Player player1;
Player player2;

bool shouldClose = false;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{

    float speed = 0.01f;
    float player1_radian_angle = glm::radians(player1.getAngle());
    float p1_dx = speed * cos(player1_radian_angle);
    float p1_dy = speed * sin(player1_radian_angle);

    std::cout << "Movement delta: x = " << p1_dx << ", y = " << p1_dy << std::endl;

    if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS))
    {
        std::cout << "GLFW_KEY_UP pressed\n";
        player1.rotate(1);
    }
    if ((glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS))
    {
        std::cout << "GLFW_KEY_DOWN pressed\n";
        player1.rotate(-1);
    }
    if ((glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS))
    {
        std::cout << "GLFW_KEY_LEFT pressed\n";
        player1.move(-p1_dx, -p1_dy);
    }
    if ((glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS))
    {
        std::cout << "GLFW_KEY_RIGHT pressed\n";
        player1.move(p1_dx, p1_dy);
    }

    glm::vec2 p1_current_postion = player1.getPosition();
    std::cout << "x: " << p1_current_postion.x << ", y: " << p1_current_postion.y << std::endl;


    float player2_radian_angle = glm::radians(player2.getAngle());
    float p2_dx = speed * cos(player2_radian_angle);
    float p2_dy = speed * sin(player2_radian_angle);

    std::cout << "Movement delta: x = " << p2_dx << ", y = " << p2_dy << std::endl;

    if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
    {
        std::cout << "GLFW_KEY_UP pressed\n";
        player2.rotate(1);
    }
    if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS))
    {
        std::cout << "GLFW_KEY_DOWN pressed\n";
        player2.rotate(-1);
    }
    if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS))
    {
        std::cout << "GLFW_KEY_LEFT pressed\n";
        player2.move(-p2_dx, -p2_dy);
    }
    if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS))
    {
        std::cout << "GLFW_KEY_RIGHT pressed\n";
        player2.move(p2_dx, p2_dy);
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        // shouldClose = true;
    }
    glm::vec2 p2_current_postion = player2.getPosition();
    std::cout << "x: " << p2_current_postion.x << ", y: " << p2_current_postion.y << std::endl;

        std::cout << "player1 angle: " << player1.getAngle() << std::endl;

    player1.isCollided(player2);

}

GLuint loadShader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;

    // Read vertex shader code
    std::ifstream vShaderFile(vertexPath);
    if (!vShaderFile)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << vertexPath << std::endl;
        return 0;
    }
    std::stringstream vShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    vertexCode = vShaderStream.str();

    // Read fragment shader code
    std::ifstream fShaderFile(fragmentPath);
    if (!fShaderFile)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << fragmentPath << std::endl;
        return 0;
    }
    std::stringstream fShaderStream;
    fShaderStream << fShaderFile.rdbuf();
    fragmentCode = fShaderStream.str();

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    // Compile shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        return 0;
    }

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        return 0;
    }

    // Shader Program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
        return 0;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shaderProgram;
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "ERROR::GLFW::INIT_FAILED" << std::endl;
        return -1;
    }

    // Set GLFW version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Basic 2D Game", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "ERROR::GLFW::WINDOW_CREATION_FAILED" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "ERROR::GLAD::INITIALIZATION_FAILED" << std::endl;
        return -1;
    }

    // Load and compile shaders
    shaderProgram = loadShader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
    if (shaderProgram == 0)
    {
        std::cerr << "ERROR::SHADER::PROGRAM_CREATION_FAILED" << std::endl;
        return -1;
    }

    // Set the key callback
    glfwSetKeyCallback(window, key_callback);

    // Set the viewport
    glViewport(0, 0, WIDTH, HEIGHT);

    // Vertex data for a square
    GLfloat vertices[] = {
        -0.15f, -0.05f, // Bottom-left corner
        0.05f, -0.05f,  // Bottom-right corner
        0.05f, 0.05f,   // Top-right corner
        -0.15f, 0.05f   // Top-left corner
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    player1.setPosition(0.f,0.f);
    player2.setPosition(-0.5f,-0.5f);

    std::cout << "player1 angle: " << player1.getAngle() << std::endl;

    // Game loop
    while (!glfwWindowShouldClose(window) && shouldClose == false)
    {
        // Check for events
        glfwPollEvents();

        // Render
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // RGBA values
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);

        /*player 1*/
        // Create the transformation matrix
        glm::mat4 p1_transform = glm::translate(glm::mat4(1.0f), glm::vec3(player1.getPosition(), 0.0f));
        p1_transform = glm::rotate(p1_transform, glm::radians(player1.getAngle()), glm::vec3(0.0f, 0.0f, 1.0f));
        GLuint p1_modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(p1_modelLoc, 1, GL_FALSE, glm::value_ptr(p1_transform));

        // Draw the player
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Updated to GL_TRIANGLE_FAN

        /*player 2*/
        // Create the transformation matrix
        glm::mat4 p2_transform = glm::translate(glm::mat4(1.0f), glm::vec3(player2.getPosition(), 0.0f));
        p2_transform = glm::rotate(p2_transform, glm::radians(player2.getAngle()), glm::vec3(0.0f, 0.0f, 1.0f));
        GLuint p2_modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(p2_modelLoc, 1, GL_FALSE, glm::value_ptr(p2_transform));

        // Draw the player
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Updated to GL_TRIANGLE_FAN

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
