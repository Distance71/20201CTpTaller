#ifndef _MOVEMENTHANDLER_H_
#define _MOVEMENTHANDLER_H_
#include "Map.h"
#include "Action.h"

// Se encarga del manejo interno del state de posicion

class MovementHandler : Action{

	private:
	    int id;

    public:
    MovementHandler(int id_map_element);
    void move_in_direction(string movement_instruction); 
};

#endif
