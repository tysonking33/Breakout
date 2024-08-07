#ifndef COPAI_H
#define COPAI_H

#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "Player.h"

class CopAI : public Player {

public:
    CopAI();
    void moveCop(glm::vec2 p1_pos);
    void findCopToPlayerAngle(glm::vec2 p1_pos);
    bool isCollided(glm::vec2 p1_pos);

private:
    float CopToPlayerAngle;
};

#endif
