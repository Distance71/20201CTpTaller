#include "EnemyIA.h"

EnemyIA::EnemyIA(){
}

void EnemyIA::update(unordered_map<string, State *> states_){
    //En principio mueve el enemigo a velocidad constante para simular que está estatico
    Logger::getInstance()->log(DEBUG, "Entro al update de Enemy IA");
    State* position = states_.at("Position");
    State* speed =states_.at("Speed");

    int xp = position->getX();
    int xs = speed->getX();
     
    int new_xp=xp-xs;

    position->setX(new_xp);
}