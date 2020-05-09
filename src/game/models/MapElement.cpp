#include "MapElement.h"


MapElement::MapElement(elementType_t type) {
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
    for(auto action : actions_){
        action.second->update(this->states_); //execute action
    }
}