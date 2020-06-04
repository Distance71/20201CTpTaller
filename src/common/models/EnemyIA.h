#ifndef _ENEMYIA_H_
#define _ENEMYIA_H_

#include "MovementHandler.h"
#include "State.h"
#include "../services/Logger.h"
#include "../types.h"


class EnemyIA: public MovementHandler {

	public:
		EnemyIA();
		void update(unordered_map<string, State *> states_);
};

#endif