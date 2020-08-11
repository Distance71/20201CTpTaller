#ifndef _ENEMYIA_H_
#define _ENEMYIA_H_

#include "MovementHandler.h"
#include "../../common/models/State.h"
#include "../../common/services/Logger.h"
#include "../../common/types.h"
#include "../../server/models/MapElement.h"
#include "../../common/services/RandomGenerate.h"

class MapElement;
class Game;

class EnemyIA: public MovementHandler {
	private:
		MapElement* target_;
		MapElement* owner_;
		Game* game_;
		unsigned long timeShoot;
		unsigned long timeLimitShoot;

		const unsigned long FRECUENCIA = 160;

		int randomMovement(int yp, int ys);
		void randomShoot();

	public:
		EnemyIA(MapElement* owner);
		void setTarget(MapElement* target);
		void update(unordered_map<string, State *> states_);
		void setGame(Game *game);
};

#endif