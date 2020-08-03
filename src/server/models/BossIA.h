#ifndef _BOSSIA_H_
#define _BOSSIA_H_

#include "MovementHandler.h"
#include "../../common/models/State.h"
#include "../../common/services/Logger.h"
#include "../../common/providers/GameProvider.h"
#include "../../common/types.h"
#include "../../server/models/MapElement.h"
#include "../../common/services/RandomGenerate.h"

class MapElement;

class BossIA: public MovementHandler {
	private:
		MapElement* owner_;
		unsigned long timeShoot;
		unsigned long timeLimitShoot;

		const unsigned long FRECUENCIA = 200;

		void randomShoot();

	public:
		BossIA(MapElement* owner);
		void update(unordered_map<string, State *> states_);
};

#endif