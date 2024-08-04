#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>

class Player {
public:
    Player();
    void draw();
    void move(bool forward);
    void setPosition(float dx, float dy);
    glm::vec2 getPosition() const;
    void rotate(float rotation_increment);
    float getAngle();
    float getSpeed();
    float getMass();
    bool isCollided(Player p2);
    void collideAndSlide(Player p2);
    void calculateVelocity();
    glm::vec2 getVelocity();

private:
    glm::vec2 position;
    float size;
    float angle; //in degrees
    float maxSpeed;
    float currentSpeed;
    float mass;
    float width;
    float height;
    float collisionXLoc;
    float collisionYLoc;
    float new_dx;
    float new_dy;
    glm::vec2 velocity;
};

#endif
