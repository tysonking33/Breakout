#include "../includes/Car.h"

// Constructor: Initializes player properties such as position, size, angle, mass, width, height, and speed.
Car::Car() {
    position = glm::vec2(0,0);
    size = 0.01f;
    angle = 0.0f;
    mass = 50.0f;
    width = 0.1f;
    height = 0.2f;
    maxSpeed = 0.005f;  //max speed forwards
    currentSpeed = 0.0f;
    deltaTime = 0.0f;
}

// Rotates the player by the given increment and ensures the angle stays within 0-360 degrees.
void Car::rotate(float rotation_increment) {
    angle += rotation_increment;
    if ((angle > 360) || (angle < -360)) {
        angle = 0;
    }
}

// Placeholder for drawing the player, actual drawing is handled in the main loop.
void Car::draw() {
    // Player drawing is handled in the main loop
}


// Calculates the player's velocity based on speed and angle.
void Car::calculateVelocity(float current_speed1) {
    new_dx = current_speed1 * cos(glm::radians(angle));
    new_dy = current_speed1 * sin(glm::radians(angle));

    velocity = glm::vec2(new_dx, new_dy);
}





// Getters and Setters

// Returns the current angle of the player.
float Car::getAngle() {
    return angle;
}

// Sets the player's angle.
void Car::setAngle(float newAngle) {
    angle = newAngle;
}

// Returns the current position of the player.
glm::vec2 Car::getPosition() const {
    return position;
}

// Sets the player's position to the specified coordinates.
void Car::setPosition(float dx, float dy) {
    position.x = dx;
    position.y = dy;
}

void Car::setVelocity(glm::vec2 newVelocity)
{
    velocity = newVelocity;
}


// Returns the current velocity of the player.
glm::vec2 Car::getVelocity() {
    return velocity;
}

// Returns the mass of the player.
float Car::getMass() {
    return mass;
}

// Updates the current speed of the player.
void Car::updateCurrentSpeed(float newSpeed) {
    currentSpeed = newSpeed;
}

// Returns the current speed of the player.
float Car::getCurrentSpeed() {
    return currentSpeed;
}

// Returns the maximum speed of the player.
float Car::getMaxSpeed() {
    return maxSpeed;
}

// Returns the height of the player.
float Car::getHeight() {
    return height;
}

// Returns the collision X location of the player.
float Car::getCollisionXLoc() {
    return collisionXLoc;
}

// Sets the collision X location of the player.
void Car::setCollisionXLoc(float newCollisionX) {
    collisionXLoc = newCollisionX;
}

// Returns the collision Y location of the player.
float Car::getCollisionYLoc() {
    return collisionYLoc;
}

// Sets the collision Y location of the player.
void Car::setCollisionYLoc(float newCollisionY) {
    collisionYLoc = newCollisionY;
}

// Returns the width of the player.
float Car::getWidth() {
    return width;
}

// Sets the delta time for the player.
void Car::setDeltaTime(float newDeltaTime) {
    deltaTime = newDeltaTime;
}
