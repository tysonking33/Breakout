#include "../includes/Player.h"

Player::Player() : position(0, 0), size(0.01f), angle(0.0f), speed(0.0f), mass(50.0f), width(0.1f), height(0.2f) {}

void Player::rotate(float rotation_increment)
{
    angle += rotation_increment;
    if (angle > 360)
    {
        angle == 0;
    }
}

float Player::getAngle()
{
    return angle;
}

void Player::draw() {
    // Player drawing is handled in the main loop
}

void Player::move(float dx, float dy) {
    position.x += dx;
    position.y += dy;
}

glm::vec2 Player::getPosition() const {
    return position;
}

void Player::setPosition(float dx, float dy)
{
    position.x = dx;
    position.y = dy;
}

float Player::getSpeed(){
    return speed;
}

float Player::getMass(){
    return mass;
}

bool Player::isCollided(Player p2)
{
    bool collideX = position.x + height >= p2.position.x && p2.position.x + p2.height >= position.x;
    bool collideY = position.y + width >= p2.position.y && p2.position.y + p2.width >= position.y;

    bool fullCollision = collideY && collideY;
    if (fullCollision == true)
    {
        std::cout << "collision occured\n";
    }

    return fullCollision;
}
