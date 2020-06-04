#ifndef _GRAPHICS_MAP_ELEMENT_H_
#define _GRAPHICS_MAP_ELEMENT_H_

#include <vector>
#include <string>
#include "../../common/models/Action.h"
#include "../../common/models/Sprite.h"
#include "../../common/models/Position.h"
#include "../../common/models/Speed.h"

class Sprite;
class GraphicsMapElement: public Action{
    private:
        Sprite* sprite_;
        int size_x_;
        int size_y_;
    
    public:
        GraphicsMapElement(Sprite * sprite, int size_x, int size_y);
        void update(unordered_map<string, State *> states_) override;
};

#endif