#include "../includes/Player.h"

// Constructor: Initializes player properties such as position, size, angle, mass, width, height, and speed.
Player::Player() {

}

// Moves the player forward or backward based on the 'forward' parameter.
void Player::move(bool forward) {
    float currentSpeed = getCurrentSpeed();
    float maxSpeed = getMaxSpeed();
    glm::vec2 position = getPosition();
    glm::vec2 velocity = getVelocity();
    if (forward) {
        if (currentSpeed < maxSpeed) {
            updateCurrentSpeed(currentSpeed + 0.0001f);
        }
    } else {
        if (currentSpeed > -maxSpeed*3/4) {
            updateCurrentSpeed(currentSpeed - 0.0001f);
        }
    }
    calculateVelocity(currentSpeed);
    //std::cout << "Player Current position: x= " << position.x << ", y= " << position.y << ", angle: " << angle << std::endl;

    //std::cout << "Player Movement delta: x = " << velocity.x << ", y = " << velocity.y << std::endl;

    //position.x += velocity.x;
    //position.y += velocity.y;

    setPosition(position.x + velocity.x, position.y + velocity.y);

    checkWallResponse();
}

void Player::breakCar() {
    float currentSpeed = getCurrentSpeed();
    glm::vec2 position = getPosition();
    glm::vec2 velocity = getVelocity();

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


// Checks for collision between this player and another player (p2).
bool Player::isCollided(Player p2) {
    glm::vec2 position = getPosition();
    glm::vec2 velocity = getVelocity();
    float collisionXLoc = getCollisionXLoc();
    float collisionYLoc = getCollisionYLoc();
    
    float height = getHeight();
    float width = getWidth();

    bool collideX = position.x + height >= p2.getPosition().x && p2.getPosition().x + p2.getHeight() >= position.x;
    bool collideY = position.y + width >= p2.getPosition().y && p2.getPosition().y + p2.getWidth() >= position.y;

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
    float currentSpeed = getCurrentSpeed();
    glm::vec2 velocity = getVelocity();
    float angle = getAngle();



    std::cout << "Collison detected\n";
        double PI = 3.14159265358979323846;

    glm::vec2 horizontalWall(0.0f, 1.0f);
    glm::vec2 verticalWall(1.0f, 0.0f);

    glm::vec2 wallNormal = horizontal ? horizontalWall : verticalWall;

    // Get velocity vector
    calculateVelocity(currentSpeed);

    //2. Calculate the Normal Component of the Velocity
    float normalVelocityComponent = glm::dot(velocity, wallNormal);

    //Inelastic Collision (loses some speed), reducing the normal component by a factor of e where, 0 <= e <= 1
    float e = 0.8f; // Example restitution coefficient; adjust as needed, 
                    //the ratio of the relative velocity of separation after collision to the relative velocity of approach before collision.
                    //https://en.wikipedia.org/wiki/Coefficient_of_restitution
    
    glm::vec2 reflectedVelocity = velocity - 2* normalVelocityComponent * wallNormal;


    //Update Position
    velocity = reflectedVelocity;
    velocity.x = -velocity.x;
    velocity.y = -velocity.y;

    setVelocity(velocity);
    
    


    std::cout << "Old Velocity: (" << velocity.x << ", " << velocity.y << ")\n";
    std::cout << "Wall Normal: (" << wallNormal.x << ", " << wallNormal.y << ")\n";
    std::cout << "Reflected Velocity: (" << reflectedVelocity.x << ", " << reflectedVelocity.y << ")\n";


    std::cout << "Old angle: " << angle << std::endl;
    //update resulting angle
    angle = atan2(velocity.y, velocity.x)* (180.0 / PI);
    std::cout << "New angle: " << angle << std::endl;
    setAngle(angle);
}



// Checks and responds to wall collisions.
void Player::checkWallResponse() {
    glm::vec2 position = getPosition();
    float newX = position.x;
    float newY = position.y;
    if (position.x < -1) {
        position.x = -1;
        wallCollisionResponse(true);
        newX = -1;
    } else if (position.x > 1) {
        position.x = 1;
        wallCollisionResponse(true);
        newX = 1;
    }

    if (position.y < -1) {
        position.y = -1;
        wallCollisionResponse(false);
        newY = -1;
    } else if (position.y > 1) {
        position.y = 1;
        wallCollisionResponse(false);
        newY = 1;
    }
    setPosition(newX, newY);
}


