#include "EventGameInit.h"


EventGameInit::EventGameInit(size_t _width,size_t _height){
    width = _width;
    height = _height;
}

void EventGameInit::update() {
    if (client){
        GameProvider::setWidth(width);
        GameProvider::setHeight(height);
    }
}

Message* EventGameInit::serialize(){
}