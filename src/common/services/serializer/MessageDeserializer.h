#ifndef MESSAGE_DESERIALIZER_H_
#define MESSAGE_DESERIALIZER_H_

#include <iostream>
#include <string.h>
#include "../../models/Socket.h"
#include "../../models/messages/Message.h"
#include "../../models/messages/MessageActionPlayer.h"
#include "../../models/messages/MessageInitEntity.h"
#include "../../models/messages/MessageInitLayer.h"
#include "../../models/messages/MessageInitScreen.h"
#include "../../models/messages/MessageLoginPlayer.h"
#include "../../models/messages/MessageMovementPlayer.h"
#include "../../models/messages/MessageRequestLoginPlayer.h"
#include "../../models/messages/MessageUpdateEntity.h"
#include "../../models/messages/MessageUpdateStage.h"
#include "../../types.h"
#include "../../events/EventsQueue.h"

using namespace std;

class MessageDeserializer {

    private:
        MessageActionPlayer *receiveActionPlayer(Socket *receives, bool &error);
        MessageInitEntity *receiveInitEntity(Socket *receives, bool &error);
        MessageInitLayer *receiveInitLayer(Socket *receives, bool &error);
        MessageInitScreen *receiveInitScreen(Socket *receives, bool &error);
        MessageLoginPlayer *receiveLoginPlayer(Socket *receives, bool &error);
        MessageMovementPlayer *receiveMovementPlayer(Socket *receives, bool &error);
        MessageRequestLoginPlayer *receiveRequestLoginPlayer(Socket *receives, bool &error);
        MessageUpdateEntity *receiveUpdateEntity(Socket *receives, bool &error);
        MessageUpdateStage *receiveUpdateStage(Socket *receives, bool &error);

    public:
        MessageDeserializer();
        
        Message *getReceivedMessage(Socket *receives, bool &error);
        void pushNewMessage(Socket *receives, bool &error, EventsQueue *queueMessage);
    
};

#endif // MESSAGE_DESERIALIZER_H_