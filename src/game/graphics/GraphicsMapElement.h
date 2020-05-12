#ifndef _GRAPHICS_MAP_ELEMENT_H_
#define _GRAPHICS_MAP_ELEMENT_H_

#include "../../game/models/Sprite.h"
#include <vector>
#include <string>
#include "../../game/models/Position.h"
#include "../../game/models/Speed.h"

class Sprite;
class GraphicsMapElement: public Action{
    private:
        Sprite*  sprite_;                             
        Position* position_;

    public:
        GraphicsMapElement(Sprite * sprite, Position* position);
        void update(unordered_map<string, State *> states_) override;
};

#endif