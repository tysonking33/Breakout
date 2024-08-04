#include "../includes/Player.h"

// Constructor: Initializes player properties such as position, size, angle, mass, width, height, and speed.
Player::Player() {
    position = glm::vec2(0,0);
    size = 0.01f;
    angle = 0.0f;
    mass = 50.0f;
    width = 0.1f;
    height = 0.2f;
    maxSpeed = 0.005f;  //max speed forwards
    currentSpeed = 0;
}

// Rotates the player by the given increment and ensures the angle stays within 0-360 degrees.
void Player::rotate(float rotation_increment)
{
    angle += rotation_increment;
    if ((angle > 360) || (angle < -360))
    {
        angle = 0;
    }
}

// Returns the current angle of the player.
float Player::getAngle()
{
    return angle;
}

// Placeholder for drawing the player, actual drawing is handled in the main loop.
void Player::draw() {
    // Player drawing is handled in the main loop
}

// Moves the player forward or backward based on the 'forward' parameter.
void Player::move(bool forward) {
    if (forward == true)
    {
        if (currentSpeed < maxSpeed)
        {
            currentSpeed += 0.0001f;
        }
    }
    else if (forward == false)
    {
        if (currentSpeed > -maxSpeed*3/4)
        {
            currentSpeed -= 0.0001f;
        }
    }
    calculateVelocity();
    std::cout << "Current position: x= " << position.x << ", y= " << position.y << ", angle: " << angle << std::endl;

    std::cout << "Movement delta: x = " << velocity.x << ", y = " << velocity.y << std::endl;

    position.x += velocity.x;
    position.y += velocity.y;
}

// Returns the current position of the player.
glm::vec2 Player::getPosition() const {
    return position;
}

// Sets the player's position to the specified coordinates.
void Player::setPosition(float dx, float dy)
{
    position.x = dx;
    position.y = dy;
}

// Calculates the player's velocity based on speed and angle.
void Player::calculateVelocity()
{
    new_dx = currentSpeed * cos(glm::radians(angle));
    new_dy = currentSpeed * sin(glm::radians(angle));

    velocity = glm::vec2(new_dx, new_dy);
}

// Returns the current velocity of the player.
glm::vec2 Player::getVelocity(){
    return velocity;
}

// Returns the mass of the player.
float Player::getMass(){
    return mass;
}


// Checks for collision between this player and another player (p2).
bool Player::isCollided(Player p2)
{
    bool collideX = position.x + height >= p2.position.x && p2.position.x + p2.height >= position.x;
    bool collideY = position.y + width >= p2.position.y && p2.position.y + p2.width >= position.y;

    collisionXLoc = position.x + height;
    collisionYLoc = position.y + height;

    bool fullCollision = collideY && collideY;
    if (fullCollision == true)
    {
        std::cout << "collision occured\n";
    }

    return fullCollision;
}


// Resolves collision by adjusting the player's position to prevent overlap.
void Player::collideAndSlide(Player p2)
{
    //resolve overlap
    float smallestX = std::min(((position.x + height) - p2.position.x), ((p2.position.x + p2.height) - position.x));
    float smallestY = std::min(((position.y + width) - p2.position.y), ((p2.position.y + p2.width) - position.y));

    if (smallestX > smallestY)
    {
        if (position.x > p2.position.x)
        {
            position.x += smallestX;
        }
        else
        {
            position.x -= smallestX;
        }
    }
    else
    {
        if (position.y > p2.position.y)
        {
            position.y += smallestY;
        }
        else
        {
            position.y -= smallestY;
        }
    }


    //adjust speed
    //velocity = velocity - glm::dot(velocity, normal) * normal;


}
