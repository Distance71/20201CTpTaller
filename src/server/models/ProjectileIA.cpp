#include "ProjectileIA.h"

ProjectileIA::ProjectileIA(){
}

void ProjectileIA::update(unordered_map<string, State *> states_){
    Logger::getInstance()->log(DEBUG, "Entro al update del Proyectil");
    State* position = states_.at("Position");
    State* speed = states_.at("Speed");
    State* orientation = states_.at("Orientation");

    int xp = position->getX();
    int xs = speed->getX();
    
    int new_xp;

    if (orientation->getX() == FRONT){
        new_xp = xp + xs;
    } else {
        new_xp = xp - xs;
    }

    position->setX(new_xp);
}