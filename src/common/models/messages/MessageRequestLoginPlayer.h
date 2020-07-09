#ifndef _MESSAGE_REQUEST_LOGIN_PLAYER_H_
#define _MESSAGE_REQUEST_LOGIN_PLAYER_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../events/EventRequestLoginPlayer.h"
#include "../events/Event.h"
#include "../../types.h"

#ifndef MAX_SIZE_CREDENTIALS
#define MAX_SIZE_CREDENTIALS 30
#endif

using namespace std;

class MessageRequestLoginPlayer: public Message {

	private:
        const message_t type_ = REQUEST_LOGIN_PLAYER;
		char userName_[MAX_SIZE_CREDENTIALS];
        char password_[MAX_SIZE_CREDENTIALS];

    public:
        explicit MessageRequestLoginPlayer(){}
    	explicit MessageRequestLoginPlayer(char userName[MAX_SIZE_CREDENTIALS], char password[MAX_SIZE_CREDENTIALS]) {
            for(size_t i = 0; i < MAX_SIZE_CREDENTIALS; i++){
                userName_[i] = userName[i];
                password_[i] = password[i];
            }
        }

        Event* deSerialize();
        message_t getType();
     	responseStatus_t serialize() {};
};

#endif