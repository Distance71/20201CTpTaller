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
		musicType_t musicType_;
        const message_t type_ = MUSIC_UPDATE;

    public:
    	explicit MessageMusicUpdate(musicType_t musicType): musicType_(musicType) {}
    	message_t getType();
        Event* deSerialize();

        musicType_t getMusicType();
        responseStatus_t serialize();
};

#endif