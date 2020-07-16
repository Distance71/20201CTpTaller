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
        int size_x_;
        int size_y_;
        int pos_x_;
        int pos_y_;
        bool setted_ = false;
        orientation_t orientation_ = FRONT;
        std::mutex mutex_update;
    
    public:
        GraphicsMapElement(const GraphicsMapElement &cpy);
        GraphicsMapElement(const string &source, int size_x, int size_y, int pos_x, int pos_y, orientation_t orientation);
        ~GraphicsMapElement();
        void update(position_t position);
        void set();
        bool isSet();

        void setNewPosition(int pos_x, int pos_y, orientation_t orientation);
        
};

#endif