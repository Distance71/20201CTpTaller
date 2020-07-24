#ifndef MESSAGE_DESERIALIZER_H_
#define MESSAGE_DESERIALIZER_H_

#include <iostream>
#include <string.h>
#include "../../models/Socket.h"
#include "../../models/events/Event.h"
#include "../../types.h"
#include "../../services/Logger.h"
#include <stdlib.h>

#include "../../models/messages/MessageSceneAnimation.h"
#include "../../models/messages/MessageEndGame.h"
#include "../../models/messages/MessageGameInit.h"
#include "../../models/messages/MessageLog.h"
#include "../../models/messages/MessageMapElementUpdate.h"
#include "../../models/messages/MessageRequestLoginPlayer.h"
#include "../../models/messages/MessageResponseLoginPlayer.h"
#include "../../models/messages/MessageUserMovement.h"
#include "../../models/messages/MessageBackgroundUpdate.h"

class Event;
using namespace std;

class MessageDeserializer {

    private:
        response_t _handleErrorStatus();
        response_t _handleSuccess();
        response_t _handleErrorMessage();

        response_t getTypeMessage(Socket *socket, message_t &message);   
        response_t getEvent(message_t messageType, Socket *socket, Event* &event);

        response_t getEventSceneAnimatiom(Socket *socket, Event* &event);
        response_t getEventEndGame(Socket *socket, Event* &event);
        response_t getEventGameInit(Socket *socket, Event* &event);
        response_t getEventLog(Socket *socket, Event* &event);
        response_t getEventMapElementUpdate(Socket *socket, Event* &event);
        response_t getEventRequestLoginPlayer(Socket *socket, Event* &event);
        response_t getEventResponseLoginPlayer(Socket *socket, Event* &event);
        response_t getEventUserMovement(Socket *socket, Event* &event);
        response_t getEventBackgroundUpdate(Socket *socket, Event* &event);
        
        response_t getInteger(Socket *socket, int &value);
        response_t getUInteger(Socket *socket, unsigned int &value);
        response_t getLongInteger(Socket *socket, size_t &value);
        response_t getResponseStatus(Socket *socket, responseStatus_t &response);
        response_t getString(Socket *socket, char (&path)[100]);
        response_t getPosition(Socket *socket, position_t &position);
        response_t getOrientation(Socket *socket, orientation_t &orientation);
        response_t getSceneScreen(Socket *socket, sceneScreen_t &scene);
        response_t getElementType(Socket *socket, elementType_t &elementType);
        response_t getLayer(Socket *socket, layer_t &layer);
        response_t getStage(Socket *socket, stage_t &stage);
    public:
        response_t getReceivedMessage(Socket *socket, Event* &event);
};

#endif // MESSAGE_DESERIALIZER_H_