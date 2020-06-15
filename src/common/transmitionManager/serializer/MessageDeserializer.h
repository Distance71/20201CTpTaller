#ifndef MESSAGE_DESERIALIZER_H_
#define MESSAGE_DESERIALIZER_H_

#include <iostream>
#include <string.h>
#include "../Socket.h"
#include "../../messages/Message.h"
#include "../../messages/MessageActionPlayer.h"
#include "../../messages/MessageInitEntity.h"
#include "../../messages/MessageInitLayer.h"
#include "../../messages/MessageInitScreen.h"
#include "../../messages/MessageLoginPlayer.h"
#include "../../messages/MessageMovementPlayer.h"
#include "../../messages/MessageRequestLoginPlayer.h"
#include "../../messages/MessageUpdateEntity.h"
#include "../../messages/MessageUpdateStage.h"
#include "../../types.h"

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
        void pushNewMessage(Socket *receives, bool &error, vector<Message *> *queueMessage);
    
};

#endif // MESSAGE_DESERIALIZER_H_