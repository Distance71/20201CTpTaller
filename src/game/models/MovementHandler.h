#ifndef _MOVEMENT_HANDLER_H_
#define _MOVEMENT_HANDLER_H_

#include "Action.h"
#include <string>

// Se encarga del manejo interno del state de posicion

class MovementHandler : virtual Action{

	private:
    int id;

    public:
    MovementHandler(int id_map_element);
    void move_in_direction(string movement_instruction);
};

#endif
