#ifndef _CLIENT_MAP_ELEMENT_H_
#define _CLIENT_MAP_ELEMENT_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../../common/types.h"
#include "../graphics/GraphicsMapElement.h"
#include "../controllers/ClientController.h"
#include "../../common/models/Action.h"
#include "../../common/models/State.h"
#include "../../common/models/Position.h"
#include "../../common/models/Orientation.h"

using namespace std;

class ClientMapElement {

    private:
        IdElement id_;
        elementType_t type;
        unordered_map<string, State *> states_;
        unordered_map<string, Action *> actions_;
        int size_x_;
        int size_y_;

    public:
        ClientMapElement(elementType_t type, position_t position_, const string &sourceSprite, int size_x, int size_y);
        ~ClientMapElement();
       
        template<typename T> void addState(const string name, T *t);
        template<typename T> void addAction(const string name, T *t);
        template<typename T> T* getState(const string name);
        template<typename T> T* getAction(const string name);
        
        void update();
        void updatePosition(position_t newPosition);
        void setIdElement(IdElement oneIdElement);
        IdElement getIdElement();
};

template<typename T>
void ClientMapElement::addState(const string name, T *state) {
    this->states_[name] = (State *) state;
}

template<typename T>
T* ClientMapElement::getState(const string name) {
    return (T *) this->states_[name];
}

template<typename T>
void ClientMapElement::addAction(const string name, T *action) {
    this->actions_[name] = (Action *) action;
}

template<typename T>
T* ClientMapElement::getAction(const string name) {
    return (T *) this->actions_[name];
}

#endif // _CLIENT_MAP_ELEMENT_H_