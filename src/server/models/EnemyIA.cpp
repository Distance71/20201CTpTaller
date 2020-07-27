#include "EnemyIA.h"

EnemyIA::EnemyIA(){
}

void EnemyIA::setTarget(MapElement* target){
    target_ = target;
}

void EnemyIA::update(unordered_map<string, State *> states_){
    //En principio mueve el enemigo a velocidad constante para simular que está estatico
    Logger::getInstance()->log(DEBUG, "Entro al update de Enemy IA");
    State* position = states_.at("Position");
    State* speed = states_.at("Speed");
    State* orientation = states_.at("Orientation");

    int xp = position->getX();
    int xs = speed->getX();
    
    int new_xp;
    int new_yp;

    //TODO check si target esta muerto o se desconecto
    //if (this->target_ != nullptr) {
    auto ubicacion = this->target_->getActualPosition();
    //cout << "posicion buscada x " << ubicacion.axis_x<< endl;
    //cout << "posicion buscada y " << ubicacion.axis_y<< endl;

    //WIP es un ejemplo

    if (orientation->getX() == FRONT){
        new_xp = xp + xs;
    } else {
        new_xp = xp - xs;
    }
    position->setX(new_xp);


    int yp = position->getY();
    if (yp < ubicacion.axis_y){
        new_yp = yp + xs;
        position->setY(new_yp);
    } else {
        if (yp > ubicacion.axis_y){
            new_yp = yp - xs;
            position->setY(new_yp);
        }
    }


}