#ifndef EVENT_SCORE_UPDATE
#define EVENT_SCORE_UPDATE

#include "Event.h"
#include "../messages/MessageScoreUpdate.h"
#include "../messages/Message.h"
#include "../../providers/GameProvider.h"
#include "../../services/Logger.h"
#include "../../../client/Client.h"

using namespace std;

class EventScoreUpdate: public Event {

	private:
        elementType_t typePlayer_;
        unsigned int lives_;
        int health_;
        int score_;

    public:
        EventScoreUpdate(elementType_t typePlayer, unsigned int lives, int health, int score)
            : typePlayer_(typePlayer), lives_(lives), health_(health), score_(score) {}
        
        Message* serialize();
        void update();
};

#endif
