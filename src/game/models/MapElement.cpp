#include "MapElement.h"


MapElement::MapElement() {
}

MapElement::~MapElement() {

}

//Personaje::addAction("controller", Controller); -> 
// controller: HandlerEvents
//             IAEnemy
//Personaje::addState("position", Position);
//Personaje::addState("orientation", Orientation);
//Personaje::addAction("graphics", Graphics);

template<typename T> 
void MapElement::addState(const string name, T *t){
    if(!name.length || !t)
        return;

    states_[name] = t;
}

template<typename T> 
void MapElement::addAction(const string name, T *t){
    if(!name.length || !t)
        return;

    actions_[name] = t;
}

template<typename T>
T* MapElement::getState(const string name){
    if(!name.length)
        return NULL;
    return states_[name];
}

template<typename T>
T* MapElement::getAction(const string name){
    if(!name.length)
        return NULL;

    return actions_[name];
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
    for(auto action : actions_){
        action.second->update(this->states_); //execute action
    }
}