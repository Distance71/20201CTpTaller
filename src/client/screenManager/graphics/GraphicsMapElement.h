#ifndef _GRAPHICS_MAP_ELEMENT_H_
#define _GRAPHICS_MAP_ELEMENT_H_

#include <vector>
#include <string>
#include <mutex>
#include "../../../common/models/Sprite.h"
#include "../../../common/models/Position.h"
#include "../../../common/types.h"

class GraphicsMapElement {
    private:
        Sprite* sprite_;
        int size_x_ = 200;
        int size_y_ = 200;
        int pos_x_ = 10;
        int pos_y_ = 10;
        orientation_t orientation_ = FRONT;
        std::mutex mutex_update;
    
    public:
        GraphicsMapElement(const GraphicsMapElement &cpy);
        GraphicsMapElement(const string &source, int size_x, int size_y, int pos_x, int pos_y, orientation_t orientation);
        ~GraphicsMapElement();
        void update();

        void setNewPosition(int pos_x, int pos_y, orientation_t orientation);
        
};

#endif