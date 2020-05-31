#ifndef _MOVEMENT_HANDLER_H_
#define _MOVEMENT_HANDLER_H_

#include "Action.h"
#include <string>
#include "State.h"


class MovementHandler : public Action{

    public:
        MovementHandler();
        void update(string direction,unordered_map<string, State *> states_);

};

#endif
