#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <iostream>

class Player {
public:
    Player();
    void draw();
    void move(float dx, float dy);
    void setPosition(float dx, float dy);
    glm::vec2 getPosition() const;
    void rotate(float rotation_increment);
    float getAngle();
    float getSpeed();
    float getMass();
    bool isCollided(Player p2);


private:
    glm::vec2 position;
    float size;
    float angle; //in degrees
    float speed;
    float mass;
    float width;
    float height;
};

#endif
