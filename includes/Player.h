#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>

class Player {
public:
    Player();

    // Draw and Movement Methods
    void draw();
    void move(bool forward);
    void breakCar();
    void rotate(float rotation_increment);
    void calculateVelocity(float current_speed1);
    void checkWallResponse();
    void wallCollisionResponse(bool horizontal);
    void collideAndSlide(Player p2);

    // Collision Detection Methods
    bool isCollided(Player p2);

    // Setters
    void setPosition(float dx, float dy);
    void updateCurrentSpeed(float newSpeed);
    void setDeltaTime(float newDeltaTime);
    void setCollisionXLoc(float newCollisionX);
    void setCollisionYLoc(float newCollisionY);
    void setAngle(float newAngle);

    // Getters
    glm::vec2 getPosition() const;
    float getAngle();
    float getCurrentSpeed();
    float getMass();
    float getMaxSpeed();
    glm::vec2 getVelocity();
    float getWidth();
    float getHeight();
    float getCollisionXLoc();
    float getCollisionYLoc();

private:
    glm::vec2 position;
    float size;
    float angle; // in degrees
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
    float deltaTime;
};

#endif
