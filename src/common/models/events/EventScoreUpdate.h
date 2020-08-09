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
        unsigned int positionPlayer_;
        unsigned int lives_;
        int health_;
        int score_;

    public:
        EventScoreUpdate(unsigned int positionPlayer, unsigned int lives, int health, int score)
            : positionPlayer_(positionPlayer), lives_(lives), health_(health), score_(score) {}
        
        Message* serialize();
        void update();
};

#endif
