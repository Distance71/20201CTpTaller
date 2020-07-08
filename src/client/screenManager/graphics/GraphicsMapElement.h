#ifndef _GRAPHICS_MAP_ELEMENT_H_
#define _GRAPHICS_MAP_ELEMENT_H_

#include <vector>
#include <string>
#include "../../../common/models/Sprite.h"
#include "../../../common/models/Position.h"
#include "../../../common/types.h"

class GraphicsMapElement {
    private:
        Sprite* sprite_;
        int size_x_;
        int size_y_;
        int pos_x_;
        int pos_y_;
        orientation_t orientation_;
    
    public:
        GraphicsMapElement(const string &source, int size_x, int size_y, int pos_x, int pos_y, orientation_t orientation);
        ~GraphicsMapElement();
        void update();

        void setNewPosition(int pos_x, int pos_y, orientation_t orientation);
        
};

#endif