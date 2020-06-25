#ifndef _GRAPHICS_MAP_ELEMENT_H_
#define _GRAPHICS_MAP_ELEMENT_H_

#include <vector>
#include <string>
#include "../../common/models/Sprite.h"
#include "../../common/models/Position.h"

class Sprite;
class GraphicsMapElement {
    private:
        Sprite* sprite_;
        int size_x_;
        int size_y_;
    
    public:
        GraphicsMapElement(Sprite * sprite, int size_x, int size_y);
        void update(unordered_map<string, State *> states); //Receives Position, Orientation
};

#endif