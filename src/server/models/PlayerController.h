#ifndef _PLAYER_CONTROLLER_H_
#define _PLAYER_CONTROLLER_H_

#include "../../common/providers/GameProvider.h"
#include "MovementHandler.h"
#include "SDL2/SDL.h"
#include "../../common/models/State.h"
#include "../../common/models/Sprite.h"

class Sprite;
class PlayerController: public MovementHandler {
	private:
	Sprite* sprite;
	public:
	PlayerController(Sprite* sprite_);
	void update(unordered_map<string, State *> states_);
};

#endif
