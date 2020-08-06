#ifndef _PROJECTILEIA_H_
#define _PROJECTILEIA_H_

#include "MovementHandler.h"
#include "../../common/models/State.h"
#include "../../common/services/Logger.h"
#include "../../common/types.h"
#include "../../server/models/MapElement.h"

class MapElement;

class ProjectileIA: public MovementHandler {

	private:
		MapElement* own_;

	public:
		ProjectileIA();
		void update(unordered_map<string, State *> states_);

		void setOwn(MapElement* own);
		MapElement* getOwn();
};

#endif