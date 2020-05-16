#include "MapElement.h"

MapElement::MapElement(elementType_t type,int x_pos,int y_pos,int x_speed,int y_speed, const string &sourceSprite){
    Position* position =new Position(x_pos,y_pos);
    Speed* speed = new Speed(x_speed,y_speed);
    addState("Position", position);
    addState("Speed", speed);
    
    if (type == PLAYER){
        Sprite* sprite =new Sprite(sourceSprite);
        GraphicsMapElement* graficador = new GraphicsMapElement(sprite);
        addAction("Graphics", graficador);
        PlayerController* playercontroller= new PlayerController(sprite);
        addAction("PlayerController", playercontroller);
    } else if(type==ENEMY_1){
        Sprite* sprite = new Sprite(sourceSprite);
        GraphicsMapElement* graficador = new GraphicsMapElement(sprite);
        addAction("Graphics", graficador);
        EnemyIA* enemyia = new EnemyIA();
        addAction("EnemyIA", enemyia);
    }
    else if(type==ENEMY_2){
        Sprite* sprite =new Sprite(sourceSprite);
        GraphicsMapElement* graficador = new GraphicsMapElement(sprite);
        addAction("Graphics", graficador);
        EnemyIA* enemyia = new EnemyIA();
        addAction("EnemyIA", enemyia);
    }
    // else if(type==BACKGROUND){
    //     Sprite* sprite =new Sprite(sourceSprite);
    //     GraphicsMapElement* graficador = new GraphicsMapElement(sprite);
    // }
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

