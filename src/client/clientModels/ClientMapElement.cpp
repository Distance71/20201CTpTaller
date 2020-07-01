#include "ClientMapElement.h"

ClientMapElement::ClientMapElement(elementType_t type, position_t position_, const string &sourceSprite, int size_x, int size_y){
    Position *position = new Position(position_.axis_x, position_.axis_y);
    Orientation *orientation = new Orientation(position_.orientation, 0);
    addState("Position", position);
    addState("Orientation", orientation);
    
    this->size_x_ = size_x;
    this->size_y_ = size_y;

    Sprite* sprite = new Sprite(sourceSprite);
    GraphicsMapElement* graficador = new GraphicsMapElement(sprite, this->size_x_, this->size_y_);
    addAction("Graphics", graficador);

    if (type == PLAYER){
        //ClientController* clientController= new ClientController();
        //addAction("ClientController", clientController);
    } else if(type == ENEMY){
        //EnemyIA* enemyia = new EnemyIA();
        //addAction("EnemyIA", enemyia);
    }
}

ClientMapElement::~ClientMapElement() {
    
}

void ClientMapElement::setIdElement(IdElement oneIdElement){
    this->id_ = oneIdElement;
}

IdElement ClientMapElement::getIdElement(){
    return this->id_;
}

void ClientMapElement::updatePosition(position_t newPosition){
    Position *position = dynamic_cast<Position*>(this->states_.at("Position"));
    Orientation *orientation = dynamic_cast<Orientation*>(this->states_.at("Orientation"));

    position->setX(newPosition.axis_x);
    position->setY(newPosition.axis_y);
    orientation->setX(newPosition.orientation);
}

void ClientMapElement::update(){
    GraphicsMapElement *graficador = dynamic_cast<GraphicsMapElement*>(actions_.at("Graphics")); 
    graficador->update(states_);
    for(auto action : actions_){
        action.second->update(states_); 
    }
}