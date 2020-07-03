#ifndef MESSAGE_DESERIALIZER_H_
#define MESSAGE_DESERIALIZER_H_

#include <iostream>
#include <string.h>
#include "../../models/Socket.h"
#include "../../models/events/Event.h"
// #include "../../models/messages/MessageActionPlayer.h"
// #include "../../models/messages/MessageInitEntity.h"
// #include "../../models/messages/MessageInitLayer.h"
// #include "../../models/messages/MessageInitScreen.h"
// #include "../../models/messages/MessageLoginPlayer.h"
// #include "../../models/messages/MessageMovementPlayer.h"
// #include "../../models/messages/MessageRequestLoginPlayer.h"
// #include "../../models/messages/MessageUpdateEntity.h"
// #include "../../models/messages/MessageUpdateStage.h"
#include "../../models/events/Event.h"
#include "../../models/messages/MessageGameInit.h"
#include "../../types.h"
//#include "../../models/BlockingQueue.h"
#include "../../services/Logger.h"

#include "../../../server/models/User.h"

using namespace std;

class MessageDeserializer {

    private:

        //Event *receiveUserLogin(Socket *socket, Event* &event);
        //Event *receiveUserMovement(Socket *socket, Event* &event);
        response_t receiveGameInit(Socket *socket, Event* &event);

        response_t _handleErrorStatus();
        response_t _handleSuccess();
        response_t _handleErrorMessage();
    public:
        //MessageDeserializer() = default;

        response_t getReceivedMessage(User* user, Event* &event);
        //Message *getReceivedMessage(Socket *receives, bool &error);
        //void pushNewMessage(Socket *receives, bool &error, EventsQueue *queueMessage);
    
};

#endif // MESSAGE_DESERIALIZER_H_