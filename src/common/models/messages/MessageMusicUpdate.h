#ifndef MESSAGE_MUSIC_UPDATE_H_
#define MESSAGE_MUSIC_UPDATE_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../events/EventMusicUpdate.h"
#include "../events/Event.h"
#include "../../types.h"

using namespace std;

class MessageMusicUpdate: public Message {

	private:
		soundType_t elementType_;
        const message_t type_ = MUSIC_UPDATE;

    public:
    	explicit MessageMusicUpdate(soundType_t elementType): elementType_(elementType) {}
    	message_t getType();
        Event* deSerialize();

        soundType_t getMusicType();
        responseStatus_t serialize();
};

#endif