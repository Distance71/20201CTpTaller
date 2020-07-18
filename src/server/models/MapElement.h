#ifndef _MAP_ELEMENT_H_
#define _MAP_ELEMENT_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../../common/models/State.h"
#include "../../common/models/Action.h"
#include "../../common/models/Orientation.h"
#include "../../common/models/Position.h"
#include "Speed.h"
#include "../../common/types.h"
#include "PlayerController.h"
#include "EnemyIA.h"

using namespace std;

class MapElement {

    private:
        Id id_;
        elementType_t type;
        unordered_map<string, State *> states_;
        unordered_map<string, Action *> actions_;
        int size_x_;
        int size_y_;

        vector<Action *> getActions();
        vector<State *> getStates();
        

    public:
        MapElement(elementType_t type, position_t position_, int x_speed, int y_speed, int size_x, int size_y);
        ~MapElement();
       
       
        template<typename T> void addState(const string name, T *t);
        template<typename T> void addAction(const string name, T *t);
        template<typename T> T* getState(const string name);
        template<typename T> T* getAction(const string name);
        
        void update();
        position_t getActualPosition();
        string getImageSource();

        elementType_t getType();
        void setType(elementType_t type);

        void moveTo(orientation_t oneOrientation);    

        void setIdElement(Id oneIdElement);
        Id getIdElement();
        bool leftScreen();
};

template<typename T>
void MapElement::addState(const string name, T *state) {
    states_[name] = (State *) state;
}

template<typename T>
T* MapElement::getState(const string name) {
    return (T *) states_[name];
}

template<typename T>
void MapElement::addAction(const string name, T *action) {
    actions_[name] = (Action *) action;
}

template<typename T>
T* MapElement::getAction(const string name) {
    return (T *) actions_[name];
}

#endif