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

template<typename T>
void MapElement::addState(const string &name, T *state) {
    states_[name] = state;
}

template<typename T>
T* MapElement::getState(const string &name) {
    return (T *) states_[name];
}

template<typename T>
void MapElement::addAction(const string &name, T *action) {
    actions_[name] = action;
}

template<typename T>
T* MapElement::getAction(const string &name) {
    return (T *) actions_[name];
}

void MapElement::setIdElement(IdElement oneIdElement){
    this->id_ = oneIdElement;
}

IdElement MapElement::getIdElement(){
    return this->id_;
}