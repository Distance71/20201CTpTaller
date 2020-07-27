#ifndef _BOSSIA_H_
#define _BOSSIA_H_

#include "MovementHandler.h"
#include "../../common/models/State.h"
#include "../../common/services/Logger.h"
#include "../../common/types.h"


class BossIA: public MovementHandler {

	public:
		BossIA();
		void update(unordered_map<string, State *> states_);
};

#endif