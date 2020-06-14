#ifndef MESSAGE_DESERIALIZER_H_
#define MESSAGE_DESERIALIZER_H_

#include <iostream>
#include <string.h>
#include "../Socket.h"
#include "../messages/Message.h"
#include "../messages/MessageActionPlayer.h"
#include "../messages/MessageInitEntity.h"
#include "../messages/MessageInitLayer.h"
#include "../messages/MessageMovementPlayer.h"
#include "../messages/MessageUpdateEntity.h"
#include "../messages/MessageUpdateStage.h"
#include "../types.h"

using namespace std;

class MessageDeserializer {

    private:
    
        MessageActionPlayer *receiveActionPlayer(Socket *receives, int *fdSend, bool &error);
        MessageInitEntity *receiveInitEntity(Socket *receives, int *fdSend, bool &error);
        MessageInitLayer *receiveInitLayer(Socket *receives, int *fdSend, bool &error);
        MessageMovementPlayer *receiveMovementPlayer(Socket *receives, int *fdSend, bool &error);
        MessageUpdateEntity *receiveUpdateEntity(Socket *receives, int *fdSend, bool &error);
        MessageUpdateStage *receiveUpdateStage(Socket *receives, int *fdSend, bool &error);

    public:
        MessageDeserializer();
        
        Message *getReceivedMessage(Socket *receives, int *fdSend, bool &error);
    
};

#endif // MESSAGE_DESERIALIZER_H_