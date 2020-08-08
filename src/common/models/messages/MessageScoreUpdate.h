#ifndef MESSAGE_SCORE_UPDATE
#define MESSAGE_SCORE_UPDATE

#include "Message.h"
#include "../events/EventScoreUpdate.h"
#include "../events/Event.h"

class MessageScoreUpdate: public Message {

	private:
        unsigned int positionPlayer_;
        unsigned int lives_;
        int health_;
        int score_;
        const message_t type_ = SCORE_UPDATE;

    public:
        explicit MessageScoreUpdate(unsigned int positionPlayer, unsigned int lives, int health, int score) 
            : positionPlayer_(positionPlayer), lives_(lives), health_(health), score_(score) {}
        message_t getType();
        Event* deSerialize();
        unsigned int getPlayerPosition();
        unsigned int getLives();
        int getHealth();
        int getScore();
        responseStatus_t serialize();
};

#endif
