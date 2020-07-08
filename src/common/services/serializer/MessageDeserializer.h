#ifndef MESSAGE_DESERIALIZER_H_
#define MESSAGE_DESERIALIZER_H_

#include <iostream>
#include <string.h>
#include "../../models/Socket.h"
#include "../../models/events/Event.h"
#include "../../types.h"
#include "../../services/Logger.h"
#include <stdlib.h>
#include "../../models/messages/MessageEndGame.h"
#include "../../models/messages/MessageEndStage.h"
#include "../../models/messages/MessageGameInit.h"
#include "../../models/messages/MessageInitStage.h"
#include "../../models/messages/MessageLog.h"
#include "../../models/messages/MessageMapElementCreate.h"
#include "../../models/messages/MessageMapElementDelete.h"
#include "../../models/messages/MessageMapElementUpdate.h"
#include "../../models/messages/MessagePlayerDisconnect.h"
#include "../../models/messages/MessagePlayerReconnect.h"
#include "../../models/messages/MessageRequestLoginPlayer.h"
#include "../../models/messages/MessageResponseLoginPlayer.h"

class Event;
using namespace std;

class MessageDeserializer {

    private:
        response_t _handleErrorStatus();
        response_t _handleSuccess();
        response_t _handleErrorMessage();

        response_t getEvent(message_t messageType, Socket *socket, Event* &event);

        response_t getEventEndGame(Socket *socket, Event* &event);
        response_t getEventEndStage(Socket *socket, Event* &event);
        response_t getEventGameInit(Socket *socket, Event* &event);
        response_t getEventInitStage(Socket *socket, Event* &event);
        response_t getEventLog(Socket *socket, Event* &event);
        response_t getEventMapElementCreate(Socket *socket, Event* &event);
        response_t getEventMapElementDelete(Socket *socket, Event* &event);
        response_t getEventMapElementUpdate(Socket *socket, Event* &event);
        response_t getEventPlayerDisconnect(Socket *socket, Event* &event);
        response_t getEventPlayerReconnect(Socket *socket, Event* &event);
        response_t getEventRequestLoginPlayer(Socket *socket, Event* &event);
        response_t getEventResponseLoginPlayer(Socket *socket, Event* &event);
        response_t getEventUserMovement(Socket *socket, Event* &event);
        

    public:
        response_t getReceivedMessage(Socket *socket, Event* &event);
};

#endif // MESSAGE_DESERIALIZER_H_