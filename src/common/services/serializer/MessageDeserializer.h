#ifndef MESSAGE_DESERIALIZER_H_
#define MESSAGE_DESERIALIZER_H_

#include <iostream>
#include <string.h>
#include "../../models/Socket.h"
#include "../../models/events/Event.h"
#include "../../types.h"
#include "../../services/Logger.h"
#include <stdlib.h>
#include "../../models/messages/MessageRequestLoginPlayer.h"

class Event;
using namespace std;

class MessageDeserializer {

    private:
        response_t _handleErrorStatus();
        response_t _handleSuccess();
        response_t _handleErrorMessage();

        response_t getEvent(message_t messageType, Socket *socket, Event* &event);

    public:
        response_t getReceivedMessage(Socket *socket, Event* &event);
};

#endif // MESSAGE_DESERIALIZER_H_