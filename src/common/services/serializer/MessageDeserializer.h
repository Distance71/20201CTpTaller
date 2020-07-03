#ifndef MESSAGE_DESERIALIZER_H_
#define MESSAGE_DESERIALIZER_H_

#include <iostream>
#include <string.h>
#include "../../models/Socket.h"
#include "../../models/events/Event.h"
// #include "../../models/messages/MessageActionPlayer.h"
#include "../../models/messages/MessageInitEntity.h"
// #include "../../models/messages/MessageInitLayer.h"
#include "../../models/messages/MessageGameInit.h"
// #include "../../models/messages/MessageLoginPlayer.h"
// #include "../../models/messages/MessageMovementPlayer.h"
// #include "../../models/messages/MessageRequestLoginPlayer.h"
#include "../../models/messages/MessageUpdateEntity.h"
// #include "../../models/messages/MessageUpdateStage.h"
#include "../../models/events/EventGameInit.h"
#include "../../types.h"
//#include "../../models/BlockingQueue.h"
#include "../../services/Logger.h"

#include "../../../server/models/User.h"

using namespace std;

class MessageDeserializer {

    private:
        void _read(Socket *socket, void *value);
        void _readString(Socket *socket, void **value);
        // MessageActionPlayer *receiveActionPlayer(Socket *receives);
        // MessageInitEntity *receiveInitEntity(Socket *receives);
        // MessageInitLayer *receiveInitLayer(Socket *receives);
        // MessageInitScreen *receiveInitScreen(Socket *receives);
        // MessageLoginPlayer *receiveLoginPlayer(Socket *receives);
        // MessageMovementPlayer *receiveMovementPlayer(Socket *receives);
        // MessageRequestLoginPlayer *receiveRequestLoginPlayer(Socket *receives);
        // MessageUpdateEntity *receiveUpdateEntity(Socket *receives);
        // MessageUpdateStage *receiveUpdateStage(Socket *receives);
        
        //EventGameInit *receiveGameInit(Socket *socket);
        
        response_t receiveInitEntity(Socket *socket, Event* &event);
        response_t receiveInitLayer(Socket *socket, Event* &event);
        response_t receiveGameInit(Socket *socket, Event* &event);
        response_t receiveLoginPlayer(Socket *socket, Event* &event);
        response_t receiveMovementPlayer(Socket *socket, Event* &event);
        response_t receiveRequestLoginPlayer(Socket *socket, Event* &event);
        response_t receiveResponseLoginPlayer(Socket *socket, Event* &event);
        response_t receiveUpdateEntity(Socket *socket, Event* &event);

        response_t _handleErrorStatus();
        response_t _handleSuccess();
        response_t _handleErrorMessage();


    public:
        MessageDeserializer() = default;
        ~MessageDeserializer() = default;

        Event *getReceivedMessage(User *user);
        //Message *getReceivedMessage(Socket *receives, bool &error);
        //void pushNewMessage(Socket *receives, bool &error, EventsQueue *queueMessage);
    
};

#endif // MESSAGE_DESERIALIZER_H_