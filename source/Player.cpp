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
    currentSpeed = 0.0f;
    deltaTime = 0.0f;
}

// Rotates the player by the given increment and ensures the angle stays within 0-360 degrees.
void Player::rotate(float rotation_increment) {
    angle += rotation_increment;
    if ((angle > 360) || (angle < -360)) {
        angle = 0;
    }
}

// Placeholder for drawing the player, actual drawing is handled in the main loop.
void Player::draw() {
    // Player drawing is handled in the main loop
}

// Moves the player forward or backward based on the 'forward' parameter.
void Player::move(bool forward) {
    if (forward) {
        if (currentSpeed < maxSpeed) {
            currentSpeed += 0.0001f;
        }
    } else {
        if (currentSpeed > -maxSpeed*3/4) {
            currentSpeed -= 0.0001f;
        }
    }
    calculateVelocity(currentSpeed);
    //std::cout << "Player Current position: x= " << position.x << ", y= " << position.y << ", angle: " << angle << std::endl;

    //std::cout << "Player Movement delta: x = " << velocity.x << ", y = " << velocity.y << std::endl;

    position.x += velocity.x;
    position.y += velocity.y;

    checkWallResponse();
}

void Player::breakCar() {
    if (currentSpeed > 0.0005) {
        currentSpeed -= 0.0005f;
    } else if (currentSpeed < -0.0005) {
        currentSpeed += 0.0005f;
    } else {
        currentSpeed = 0;
    }

    calculateVelocity(currentSpeed);

    position.x += velocity.x;
    position.y += velocity.y;
}

// Calculates the player's velocity based on speed and angle.
void Player::calculateVelocity(float current_speed1) {
    new_dx = current_speed1 * cos(glm::radians(angle));
    new_dy = current_speed1 * sin(glm::radians(angle));

    velocity = glm::vec2(new_dx, new_dy);
}

// Checks for collision between this player and another player (p2).
bool Player::isCollided(Player p2) {
    bool collideX = position.x + height >= p2.position.x && p2.position.x + p2.height >= position.x;
    bool collideY = position.y + width >= p2.position.y && p2.position.y + p2.width >= position.y;

    collisionXLoc = position.x + height;
    collisionYLoc = position.y + height;

    bool fullCollision = collideX && collideY;
    if (fullCollision) {
        //std::cout << "collision occured\n";
    }

    return fullCollision;
}

// Resolves collision by adjusting the player's position to prevent overlap.
void Player::collideAndSlide(Player p2) {
    // Implementation needed
}

// Handles wall collision response based on the direction of the wall.
void Player::wallCollisionResponse(bool horizontal) {
    glm::vec2 horizontalWall(0.0f, 1.0f);
    glm::vec2 verticalWall(1.0f, 0.0f);

    glm::vec2 wallNormal = verticalWall;

    if (horizontal) {
        wallNormal = horizontalWall;
    }
    // Get velocity vector
    calculateVelocity(currentSpeed);

    // Find normal and tangent components
    glm::vec2 velocityNormal = glm::dot(velocity, wallNormal) * wallNormal;
    glm::vec2 velocityTangent = velocity - velocityNormal;

    // Reflect normal component
    glm::vec2 reflectedVNorm = -velocityNormal;

    // Combine the components
    glm::vec2 newVelocity = reflectedVNorm + velocityTangent;

    // Find new speed and angle
    float newSpeed = glm::length(newVelocity);
    float newAngle = glm::atan(newVelocity.y, newVelocity.x);

    currentSpeed = newSpeed;
    angle = newAngle;
}

// Checks and responds to wall collisions.
void Player::checkWallResponse() {
    if (position.x < -1) {
        position.x = -1;
        wallCollisionResponse(true);
    } else if (position.x > 1) {
        position.x = 1;
        wallCollisionResponse(true);
    }

    if (position.y < -1) {
        position.y = -1;
        wallCollisionResponse(false);
    } else if (position.y > 1) {
        position.y = 1;
        wallCollisionResponse(false);
    }
}

// Getters and Setters

// Returns the current angle of the player.
float Player::getAngle() {
    return angle;
}

// Sets the player's angle.
void Player::setAngle(float newAngle) {
    angle = newAngle;
}

// Returns the current position of the player.
glm::vec2 Player::getPosition() const {
    return position;
}

// Sets the player's position to the specified coordinates.
void Player::setPosition(float dx, float dy) {
    position.x = dx;
    position.y = dy;
}

// Returns the current velocity of the player.
glm::vec2 Player::getVelocity() {
    return velocity;
}

// Returns the mass of the player.
float Player::getMass() {
    return mass;
}

// Updates the current speed of the player.
void Player::updateCurrentSpeed(float newSpeed) {
    currentSpeed = newSpeed;
}

// Returns the current speed of the player.
float Player::getCurrentSpeed() {
    return currentSpeed;
}

// Returns the maximum speed of the player.
float Player::getMaxSpeed() {
    return maxSpeed;
}

// Returns the height of the player.
float Player::getHeight() {
    return height;
}

// Returns the collision X location of the player.
float Player::getCollisionXLoc() {
    return collisionXLoc;
}

// Sets the collision X location of the player.
void Player::setCollisionXLoc(float newCollisionX) {
    collisionXLoc = newCollisionX;
}

// Returns the collision Y location of the player.
float Player::getCollisionYLoc() {
    return collisionYLoc;
}

// Sets the collision Y location of the player.
void Player::setCollisionYLoc(float newCollisionY) {
    collisionYLoc = newCollisionY;
}

// Returns the width of the player.
float Player::getWidth() {
    return width;
}

// Sets the delta time for the player.
void Player::setDeltaTime(float newDeltaTime) {
    deltaTime = newDeltaTime;
}
