#ifndef _ENEMYIA_H_
#define _ENEMYIA_H_

#include "MovementHandler.h"
#include "../../common/models/State.h"
#include "../../common/services/Logger.h"
#include "../../common/types.h"
#include "../../server/models/MapElement.h"

class MapElement;

class EnemyIA: public MovementHandler {
	private:
		MapElement* target_;	

	public:
		EnemyIA();
		void setTarget(MapElement* target);
		void update(unordered_map<string, State *> states_);
};

#endif