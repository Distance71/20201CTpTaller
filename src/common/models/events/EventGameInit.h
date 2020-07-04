#ifndef EVENT_GAME_INIT_H
#define EVENT_GAME_INIT_H

#include "Event.h"
<<<<<<< HEAD
#include "../messages/MessageGameInit.h"
#include "../messages/Message.h"
=======
#include "../../providers/GameProvider.h"
>>>>>>> 1f2af3267d24fb18a8055634c259c385f37a9398

using namespace std;

class EventGameInit:public Event {

    public:
<<<<<<< HEAD
        EventGameInit() = default;
=======
        
        EventGameInit(size_t _width,size_t _height);
        ~EventGameInit();
>>>>>>> 1f2af3267d24fb18a8055634c259c385f37a9398
        
        Message* serialize() override;
        void update() override;
    
    private:
        size_t width;
        size_t height;
};

#endif