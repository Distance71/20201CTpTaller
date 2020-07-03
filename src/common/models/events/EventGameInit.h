#ifndef EVENT_GAME_INIT_H
#define EVENT_GAME_INIT_H

#include "Event.h"
#include "../../providers/GameProvider.h"

using namespace std;

class EventGameInit:public Event {

    public:
        
        EventGameInit(size_t _width,size_t _height);
        ~EventGameInit();
        
        Message* serialize() override;
        void update() override;
    
    private:
        size_t width;
        size_t height;
};

#endif