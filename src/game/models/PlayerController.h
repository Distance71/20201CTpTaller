#ifndef _PLAYER_CONTROLLER_H_
#define _PLAYER_CONTROLLER_H_

#include "../../providers/GameProvider.h"
#include "MovementHandler.h"
#include "SDL2/SDL.h"
#include "MapElement.h"
#include "State.h"
#include "Sprite.h"

class Sprite;
class PlayerController: public MovementHandler {
	private:
	Sprite* sprite;
	public:
	PlayerController(Sprite* sprite_);
	void update(unordered_map<string, State *> states_);
};

#endif
