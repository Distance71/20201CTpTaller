#ifndef EVENT_RESPONSE_LOGIN_PLAYER
#define EVENT_RESPONSE_LOGIN_PLAYER

#include "Event.h"
#include "../../types.h"

class EventResponseLoginPlayer: public Event{
    
    public:
        EventResponseLoginPlayer(login_answer _answer);
        void update();

    private:
        login_answer answer;
};

#endif