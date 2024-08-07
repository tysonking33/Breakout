#include "../includes/Game.h"

// Constructor: Initializes the game with default player positions and sets up the game window.
Game::Game() : player1(), player2(), cop1(), cop2()
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

    deltaTime = glfwGetTime();

}

// Main game loop: Handles events, processes input, updates game state, and renders the scene.
void Game::run()
{
    player1.setPosition(0.5f, 0.5f);
    //player2.setPosition(0.5f, 0.5f);

    float copX = (rand() % 100)/100;
    float copY = (rand() % 100)/100;
    
    cop1.setPosition(copX, copY);

    copX = (rand() % 100)/100;
    copY = (rand() % 100)/100;
    
    cop2.setPosition(copX, copY);


    glfwSetFramebufferSizeCallback(window, glfwSetFrameSizeCallback);

    while (!glfwWindowShouldClose(window))
    {
        deltaTime = glfwGetTime();
        player1.setDeltaTime(deltaTime);
        //player2.setDeltaTime(deltaTime);
        cop1.setDeltaTime(deltaTime);
        cop2.setDeltaTime(deltaTime);
        
        glfwPollEvents();
        processInput();
        update();
        render();
        glfwSwapBuffers(window);
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        WIDTH = width;
        HEIGHT = height;
        //std::cout << "Current window size: " << width << ", " << height << std::endl;

        
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
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        player1.rotate(-1);
        // std::cout << "GLFW_KEY_DOWN pressed\n";
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        player1.move(false);
        // std::cout << "GLFW_KEY_LEFT pressed\n";
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        player1.move(true);
        // std::cout << "GLFW_KEY_RIGHT pressed\n";
    }

    if ((glfwGetKey(window, GLFW_KEY_UP) != GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_PRESS))
    {
        player1.breakCar();
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        player2.rotate(1);
        // std::cout << "GLFW_KEY_W pressed\n";
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        player2.rotate(-1);
        // std::cout << "GLFW_KEY_S pressed\n";
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        player2.move(false);
        // std::cout << "GLFW_KEY_A pressed\n";
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        player2.move(true);
        // std::cout << "GLFW_KEY_D pressed\n";
    }
}

// Updates the game state, including collision detection between players.
void Game::update()
{
    //player1.isCollided(player2);
    cop1.moveCop(player1.getPosition());
    cop2.moveCop(player1.getPosition());
}

// Renders the scene: Clears the screen and draws the players at their current positions and angles.
void Game::render()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer->drawPlayer(*shader, player1.getPosition(), player1.getAngle());
    //renderer->drawPlayer(*shader, player2.getPosition(), player2.getAngle());
    //renderer->drawWall(*shader);
    renderer->drawCopAI(*shader, cop1.getPosition(), cop1.getAngle());
    renderer->drawCopAI(*shader, cop2.getPosition(), cop2.getAngle());
}

void Game::glfwSetFrameSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0,0,width, height);
}

// Cleans up resources: Deletes shader and renderer objects and terminates GLFW.
void Game::cleanUp()
{
    delete shader;
    delete renderer;
    glfwTerminate();
}
