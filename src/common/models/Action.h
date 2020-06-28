#ifndef _ACTION_H_
#define _ACTION_H_

#include <unordered_map>
#include <string>
#include "../../common/models/State.h"

using namespace std;

// Se encarga del manejo interno del state de posicion

class  Action {

    public:
    Action();
    virtual void update(unordered_map<string, State *> states_);
    ~Action();
    
    private:
    
};

#endif
