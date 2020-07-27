#ifndef _PROJECTILEIA_H_
#define _PROJECTILEIA_H_

#include "MovementHandler.h"
#include "../../common/models/State.h"
#include "../../common/services/Logger.h"
#include "../../common/types.h"


class ProjectileIA: public MovementHandler {

	public:
		ProjectileIA();
		void update(unordered_map<string, State *> states_);
};

#endif