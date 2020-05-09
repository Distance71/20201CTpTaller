#ifndef _PLAYER_CONTROLLER_H_
#define _PLAYER_CONTROLLER_H_

#include "MovementHandler.h"
#include "SDL2/SDL.h"

class MovementHandler;

class PlayerController: public MovementHandler{
    
	public:
		PlayerController(int id);
		int detect_event();
};

#endif
