#ifndef EVENT_REQUEST_LOGIN_PLAYER_H_
#define EVENT_REQUEST_LOGIN_PLAYER_H_

#include "../events/Event.h"
#include "../messages/MessageRequestLoginPlayer.h"
#include "../messages/Message.h"

#define MAX_SIZE 30

using namespace std;

class EventRequestLoginPlayer: public Event {

	private:
		char userName_[MAX_SIZE];
        char password_[MAX_SIZE];

    public:
    	explicit EventRequestLoginPlayer(char userName[MAX_SIZE], char password[MAX_SIZE]) {
            for(size_t i = 0; i < MAX_SIZE; i++){
                userName_[i] = userName[i];
                password_[i] = password[i];
            }
        }

        Message* serialize();
        void update();
};

#endif