#ifndef _MAPELEMENT_H_
#define _MAPELEMENT_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;
using IdElement = size_t;

// Es una abstraccion de "cosas" que pueda contener el mapa del juego

class State; // -> void *
class Action; // -> void *

class MapElement {

    private:
        IdElement id_;
        unordered_map<string, State *> states_;
        unordered_map<string, Action *> actions_;

    public:
        MapElement();
        ~MapElement();
        template<typename T> void addState(const string &name, T *t);
        template<typename T> void addAction(const string &name, T *t);
        template<typename T> T* getState(const string &name);
        template<typename T> T* getAction(const string &name);
        vector<Action *> getActions();
        vector<State *> getStates();
        void setIdElement(IdElement oneIdElement);
        IdElement getIdElement();
};

#endif