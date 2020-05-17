#include "MapElement.h"

MapElement::MapElement(elementType_t type,int x_pos,int y_pos,int x_speed,int y_speed, const string &sourceSprite, int size_x, int size_y){
    Position* position =new Position(x_pos,y_pos);
    Speed* speed = new Speed(x_speed,y_speed);
    addState("Position", position);
    addState("Speed", speed);
    
    this->size_x_ = size_x;
    this->size_y_ = size_y;

    Sprite* sprite = new Sprite(sourceSprite);
    GraphicsMapElement* graficador = new GraphicsMapElement(sprite, this->size_x_, this->size_y_);
    addAction("Graphics", graficador);

    if (type == PLAYER){
        PlayerController* playercontroller= new PlayerController(sprite);
        addAction("PlayerController", playercontroller);
    } else if(type == ENEMY){
        EnemyIA* enemyia = new EnemyIA();
        addAction("EnemyIA", enemyia);
    }
}

MapElement::~MapElement() {
}

vector<Action *> MapElement::getActions() {
    vector<Action *> actions(actions_.size());
    auto action_selector = [](auto pair) { return pair.second; };
    transform(actions_.begin(), actions_.end(), actions.begin(), action_selector);
    return actions;
}

vector<State *> MapElement::getStates() {
    vector<State *> states(states_.size());
    auto state_selector = [](auto pair) { return pair.second; };
    transform(states_.begin(), states_.end(), states.begin(), state_selector);
    return states;
}

void MapElement::setIdElement(IdElement oneIdElement){
    this->id_ = oneIdElement;
}

IdElement MapElement::getIdElement(){
    return this->id_;
}

void MapElement::update(){
     GraphicsMapElement *graficador = dynamic_cast<GraphicsMapElement*>(actions_.at("Graphics")); 
     graficador->update(states_);
    for(auto action : actions_){
        action.second->update(states_); 
    }
}

bool MapElement::leftScreen(){
    return (this->getState<Position>("Position")->getX() + this->size_x_ <= 0);
}
