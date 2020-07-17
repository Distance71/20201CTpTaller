#ifndef EVENT_REQUEST_LOGIN_PLAYER_H_
#define EVENT_REQUEST_LOGIN_PLAYER_H_

#include "../events/Event.h"
#include "../messages/MessageRequestLoginPlayer.h"
#include "../messages/Message.h"
#include "../../types.h"
#include "EventResponseLoginPlayer.h"
#include "../../../server/Server.h"


#ifndef MAX_SIZE_CREDENTIALS
#define MAX_SIZE_CREDENTIALS 30
#endif


using namespace std;

class EventRequestLoginPlayer: public Event {

	private:
		char* userName_;
        char* password_;

    public:
    	EventRequestLoginPlayer(char userName[MAX_SIZE_CREDENTIALS], char password[MAX_SIZE_CREDENTIALS]);
        Message* serialize();
        void update();
};

#endif