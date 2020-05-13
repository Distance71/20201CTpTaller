#ifndef _ENEMYIA_H_
#define _ENEMYIA_H_

#include "MovementHandler.h"
#include "State.h"
#include "../../services/Logger.h"


class EnemyIA: public MovementHandler {
	private:
	public:
	EnemyIA();
	void update(unordered_map<string, State *> states_);
};

#endif