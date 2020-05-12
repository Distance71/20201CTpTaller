#ifndef _PLAYER_CONTROLLER_H_
#define _PLAYER_CONTROLLER_H_

#include "MovementHandler.h"
#include "SDL2/SDL.h"
#include "MapElement.h"

class PlayerController{
    
	public:
		PlayerController(Position* position, Speed* speed);
		int detect_event();
};

#endif
