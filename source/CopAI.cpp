#include "../includes/CopAI.h"

// Constructor: Initializes CopAI properties such as position, size, angle, mass, width, height, and speed.
CopAI::CopAI() {
}

// Moves the CopAI forward or backward based on the 'forward' parameter.
void CopAI::moveCop(glm::vec2 p1_pos) {
    //std::cout << "AI: position (" << p1_pos.x << ", " << p1_pos.y << ")\n";
    findCopToPlayerAngle(p1_pos);

    float currentSpeed = getCurrentSpeed();
    float maxSpeed  =getMaxSpeed();
    glm::vec2 velocity = getVelocity();
    glm::vec2 position = getPosition();
    if (currentSpeed < maxSpeed)
    {
        currentSpeed += 0.001f;
    }
    calculateVelocity(currentSpeed);
    //std::cout << "CopAI Current position: x= " << position.x << ", y= " << position.y << ", angle: " << angle << std::endl;

    //std::cout << "CopAI Movement delta: x = " << velocity.x << ", y = " << velocity.y << std::endl;

    position.x += velocity.x;
    position.y += velocity.y;

    setPosition(position.x, position.y);

    //std::cout << "AI: velocity (" << velocity.x << ", " << velocity.y << ")\n";

    //checkWallResponse();

    //if (isCollided(p1_pos))
    //{
        //std::cout << "Cop collided with Player\n";
    //}
}

// Checks for collision between this player and another player (p2).
bool CopAI::isCollided(glm::vec2 p1_pos)
{
    glm::vec2 position = getPosition();
    float height = getHeight();
    float width = getWidth();
    bool collideX = position.x + height >= p1_pos.x && p1_pos.x + height >= position.x;
    bool collideY = position.y + width >= p1_pos.y && p1_pos.y + width >= position.y;

    setCollisionXLoc(position.x + height);
    setCollisionXLoc(position.y + height);

    bool fullCollision = collideX && collideY;
    if (fullCollision == true)
    {
        //std::cout << "collision occured\n";
    }

    return fullCollision;
}



void CopAI::findCopToPlayerAngle(glm::vec2 p1_pos)
{
    glm::vec2 position = getPosition();

    double PI = 3.14159265358979323846;
    CopToPlayerAngle = std::atan2((p1_pos.y - position.y),(p1_pos.x - position.x));
    setAngle(CopToPlayerAngle * (180.0 / PI));
    //std::cout << "Angle: " << angle << std::endl;
}

