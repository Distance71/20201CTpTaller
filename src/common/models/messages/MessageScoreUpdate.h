#ifndef MESSAGE_SCORE_UPDATE
#define MESSAGE_SCORE_UPDATE

#include "Message.h"
#include "../events/EventScoreUpdate.h"
#include "../events/Event.h"

class MessageScoreUpdate: public Message {

	private:
        elementType_t typePlayer_;
        unsigned int lives_;
        int health_;
        int score_;
        const message_t type_ = SCORE_UPDATE;

    public:
        explicit MessageScoreUpdate(elementType_t typePlayer, unsigned int lives, int health, int score) 
            : typePlayer_(typePlayer), lives_(lives), health_(health), score_(score) {}
        message_t getType();
        Event* deSerialize();
        elementType_t getTypePlayer();
        unsigned int getLives();
        int getHealth();
        int getScore();
        responseStatus_t serialize();
};

#endif
