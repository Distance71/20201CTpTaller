#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_

#include "MovementHandler.h"

class PlayerController : MovementHandler{
    
	public:
		PlayerController(int id);
		int detect_event();
};

#endif
