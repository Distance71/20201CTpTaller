#include "BossIA.h"

BossIA::BossIA(){
}

void BossIA::update(unordered_map<string, State *> states_){
    Logger::getInstance()->log(DEBUG, "Entro al update de Boss IA");
    State* position = states_.at("Position");
    State* speed = states_.at("Speed");
    State* orientation = states_.at("Orientation");

    //TODO implementar IA
    /* 
    int xp = position->getX();
    int xs = speed->getX();
    
    int new_xp;

    if (orientation->getX() == FRONT){
        new_xp = xp + xs;
    } else {
        new_xp = xp - xs;
    }

    position->setX(new_xp); */
}