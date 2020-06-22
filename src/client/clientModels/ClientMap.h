#ifndef _CLIENT_MAP_H_
#define _CLIENT_MAP_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdlib.h>

#include "ClientMapElement.h"
#include "../../common/providers/GameProvider.h"
#include "../graphicsManager/GraphicsScenario.h"
#include "../../common/types.h"

class ClientMapElement;
class GraphicsScenario;

class ClientMap {
    private:
        GraphicsScenario *escenario_;
        vector<ClientStep *> steps_;
        unordered_map<IdElement, ClientMapElement*> mapElements_;
        unordered_map<IdPlayer, ClientMapElement*> players_;
        stageSource_t background_;

        void clearBackground();

    public:    
        ClientMap();
        ~ClientMap();

        void addLayerBackground(size_t idLayer, string oneSource);
        void setStageSource();
        GraphicsScenario *getCurrentScenario();
        void addNewPlayer();
        void addNewEnemy(unsigned int step, IdElement idEnemy, elementType_t type, position_t position, const string &sourceSprite, int size_x, int size_y);
        void deadEnemy(unsigned int step, IdElement idEnemy);
        void endLevel();
};

class ClientStep {
    private:
        unordered_map<IdElement, ClientMapElement*> mapElements_;

    public:    
        ClientStep();
        ~ClientStep();

        void addNewEnemy(IdElement idEnemy, elementType_t type, position_t position, const string &sourceSprite, int size_x, int size_y);
        void deadEnemy(IdElement idEnemy);
        void endStep();
};

#endif // _CLIENT_MAP_H_