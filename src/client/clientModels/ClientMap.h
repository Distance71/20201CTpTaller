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

// Es el contenedor principal del juego. Se va mostrando una parte de este en la pantalla
class ClientMapElement;
class Step;
class Stage;
class Level;
class GraphicsScenario;

class ClientMap {
    private:
        vector <ClientLevel *> levels_;  
        GraphicsScenario *escenario_;
        unordered_map<IdPlayer, ClientMapElement*> players_;

    public:    
        ClientMap();
        ~ClientMap();
};

class ClientLevel: public ClientMap {
    private:
        vector<ClientStage *> stages_;

    public:
        ClientLevel();
        ~ClientLevel();
};

class ClientStage: public ClientLevel {
    private:
        vector<ClientStep *> steps_;

    public:
        ClientStage();
        ~ClientStage();
};

class ClientStep: public ClientStage {
    private:
        unordered_map<IdElement, ClientMapElement*> mapElements_;
        IdElement lastId_ = 0;

    public:
        ClientStep();
        ~ClientStep();

};

#endif // _CLIENT_MAP_H_