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
		soundType_t elementType_;

    public:
    	EventMusicUpdate(soundType_t elementType): elementType_(elementType) {}

        Message* serialize();
        void update();
};

#endif