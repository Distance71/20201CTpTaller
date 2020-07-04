#ifndef _GRAPHICS_GENERAL_H_
#define _GRAPHICS_GENERAL_H_


#include <unordered_map>
#include "GraphicsMapElement.h"
#include "GraphicsScenario.h"
#include "../../common/types.h"

class GraphicsGeneral {
    private:
        unordered_map<IdElement, GraphicsMapElement*> elements_;
        GraphicsScenario *scenario_ = nullptr;

    public:
        GraphicsGeneral();
        ~GraphicsGeneral();

        void update();

        void createEntity(IdElement id, const string &source, int sizeX, int sizeY, int posX, int posY, orientation_t orientation);
        void updateEntity(IdElement id, int posX, int posY, orientation_t orientation);
        void deadEntity(IdElement id);
        void setBackground(stageSource_t background);

};

#endif // _GRAPHICS_GENERAL_H_