#ifndef PLAYER_H
#define PLAYER_H


#include "Car.h"
#include "CopAI.h"

class CopAI;


class Player: public Car {
public:
    Player();

    void move(bool forward);
    void breakCar();


    void checkWallResponse();
    void wallCollisionResponse(bool horizontal);
    void wallCollisionResponse(CopAI cop);
    void collideAndSlide(Player p2);


    // Collision Detection Methods
    bool isCollided(Player p2);

};

#endif
