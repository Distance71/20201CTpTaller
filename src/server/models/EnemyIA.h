#ifndef _ENEMYIA_H_
#define _ENEMYIA_H_

#include "MovementHandler.h"
#include "../../common/models/State.h"
#include "../../common/services/Logger.h"
#include "../../common/types.h"


class EnemyIA: public MovementHandler {

	public:
		EnemyIA();
		void update(unordered_map<string, State *> states_);
};

#endif