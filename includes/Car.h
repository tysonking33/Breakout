#ifndef CAR_H
#define CAR_H

#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>

class Car
{
    public:
    Car();

    // Draw and Movement Methods
    void draw();
    void rotate(float rotation_increment);
    void calculateVelocity(float current_speed1);


    // Setters
    void setPosition(float dx, float dy);
    void updateCurrentSpeed(float newSpeed);
    void setDeltaTime(float newDeltaTime);
    void setCollisionXLoc(float newCollisionX);
    void setCollisionYLoc(float newCollisionY);
    void setAngle(float newAngle);
    
    void setVelocity(glm::vec2 newVelocity);

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