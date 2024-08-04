#include "../includes/Game.h"

// Constructor: Initializes the game with default player positions and sets up the game window.
Game::Game() : player1(), player2()
{
    WIDTH = 800;
    HEIGHT = 600;
    init();
}

// Destructor: Cleans up resources when the game object is destroyed.
Game::~Game()
{
    cleanUp();
}

// Initializes GLFW, creates a window, sets up OpenGL context, and initializes the shader and renderer.
void Game::init()
{
    if (!glfwInit())
    {
        std::cerr << "ERROR::GLFW::INIT_FAILED" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Basic 2D Game", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "ERROR::GLFW::WINDOW_CREATION_FAILED" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "ERROR::GLAD::INITIALIZATION_FAILED" << std::endl;
        exit(EXIT_FAILURE);
    }

    shader = new Shader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
    renderer = new Renderer();

    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowUserPointer(window, this); // Set user pointer to the game instance
}

// Main game loop: Handles events, processes input, updates game state, and renders the scene.
void Game::run()
{
    player1.setPosition(0.0f, 0.0f);
    player2.setPosition(-0.5f, -0.5f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        processInput();
        update();
        render();
        glfwSwapBuffers(window);
    }
}

// Key callback function to handle key events (currently commented out).
void Game::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    Game *game = static_cast<Game *>(glfwGetWindowUserPointer(window));

    // if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    // glfwSetWindowShouldClose(window, GL_TRUE);
}

// Processes input: Checks for key presses and updates player positions and rotations accordingly.
void Game::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        player1.rotate(1);
        // std::cout << "GLFW_KEY_UP pressed\n";
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        player1.rotate(-1);
        // std::cout << "GLFW_KEY_DOWN pressed\n";
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        player1.move(false);
        // std::cout << "GLFW_KEY_LEFT pressed\n";
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        player1.move(true);
        // std::cout << "GLFW_KEY_RIGHT pressed\n";
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        player2.rotate(1);
        // std::cout << "GLFW_KEY_W pressed\n";
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        player2.rotate(-1);
        // std::cout << "GLFW_KEY_S pressed\n";
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        player2.move(false);
        // std::cout << "GLFW_KEY_A pressed\n";
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        player2.move(true);
        // std::cout << "GLFW_KEY_D pressed\n";
    }
}

// Updates the game state, including collision detection between players.
void Game::update()
{
    player1.isCollided(player2);
}

// Renders the scene: Clears the screen and draws the players at their current positions and angles.
void Game::render()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer->draw(*shader, player1.getPosition(), player1.getAngle());
    renderer->draw(*shader, player2.getPosition(), player2.getAngle());
}

// Cleans up resources: Deletes shader and renderer objects and terminates GLFW.
void Game::cleanUp()
{
    delete shader;
    delete renderer;
    glfwTerminate();
}
