#ifndef _MOVEMENT_HANDLER_H_
#define _MOVEMENT_HANDLER_H_

#include "Action.h"
#include <string>
#include "MapElement.h"

// Se encarga del manejo interno del state de posicion
class MovementHandler : virtual Action{

	private:
        Position* position_;
        Speed * speed_;

    public:
        MovementHandler(Position* position, Speed*speed);
        void move_in_direction(string movement_instruction);
};

#endif
