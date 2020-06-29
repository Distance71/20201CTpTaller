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
#include "../../services/Logger.h"

#include "../../../server/models/User.h"

using namespace std;

class MessageDeserializer {

    private:
        void _read(Socket *socket, void *value);
        void _readString(Socket *socket, void **value);
        MessageActionPlayer *receiveActionPlayer(Socket *receives);
        MessageInitEntity *receiveInitEntity(Socket *receives);
        MessageInitLayer *receiveInitLayer(Socket *receives);
        MessageInitScreen *receiveInitScreen(Socket *receives);
        MessageLoginPlayer *receiveLoginPlayer(Socket *receives);
        MessageMovementPlayer *receiveMovementPlayer(Socket *receives);
        MessageRequestLoginPlayer *receiveRequestLoginPlayer(Socket *receives);
        MessageUpdateEntity *receiveUpdateEntity(Socket *receives);
        MessageUpdateStage *receiveUpdateStage(Socket *receives);

    public:
        MessageDeserializer();
        
        Message *getReceivedMessage(User *user);
        //Message *getReceivedMessage(Socket *receives, bool &error);
        void pushNewMessage(Socket *receives, bool &error, EventsQueue *queueMessage);
    
};

#endif // MESSAGE_DESERIALIZER_H_