#ifndef EVENT_MUSIC_UPDATE_H_
#define EVENT_MUSIC_UPDATE_H_

#include <iostream>
#include <string.h>
#include "../messages/Message.h"
#include "../messages/MessageMusicUpdate.h"
#include "../events/Event.h"
#include "../../types.h"
#include "../../../client/Client.h"

using namespace std;

class EventMusicUpdate: public Event {

	private:
		musicType_t musicType_;

    public:
    	EventMusicUpdate(musicType_t musicType): musicType_(musicType) {}

        Message* serialize();
        void update();
};

#endif