#ifndef MESSAGE_SERIALIZER_H_
#define MESSAGE_SERIALIZER_H_


#include "../../models/Socket.h"
#include "../../models/events/Event.h"
#include "../../services/Logger.h"
#include "../../models/messages/Message.h"
#include "../../models/messages/MessageAnimationInitStage.h"
#include "../../models/messages/MessageEndStage.h"
#include "../../models/messages/MessageGameInit.h"
#include "../../models/messages/MessageMapElementCreate.h"
#include "../../models/messages/MessagePlayerDisconnect.h"
#include "../../models/messages/MessageMapElementUpdate.h"
#include "../../models/messages/MessagePlayerReconnect.h"
#include "../../models/messages/MessageUserMovement.h"


using namespace std;

class MessageSerializer {
    private:
        response_t _handleErrorStatus();
        response_t _handleSuccess();

        response_t sendMessageAnimationInitStage(Socket *socket, Message *message);

        response_t sendMessageEndGame(Socket *socket, Message *message);
        response_t sendMessageEndStage(Socket *socket, Message *message);
        response_t sendMessageGameInit(Socket *socket, Message *message);
        response_t sendMessageInitStage(Socket *socket, Message *message);
        response_t sendMessageLog(Socket *socket, Message *message);
        response_t sendMessageMapElementCreate(Socket *socket, Message *message);
        response_t sendMessageMapElementDelete(Socket *socket, Message *message);
        response_t sendMessageMapElementUpdate(Socket *socket, Message *message);
        response_t sendMessagePlayerDisconnect(Socket *socket, Message *message);
        response_t sendMessagePlayerReconnect(Socket *socket, Message *message);
        response_t sendMessageRequestLoginPlayer(Socket *socket, Message *message);
        response_t sendMessageResponseLoginPlayer(Socket *socket, Message *message);
        response_t sendMessageUserMovement(Socket *socket, Message *message);

        response_t sendInteger(Socket *socket, void *value, size_t size);
        response_t sendResponseType(Socket *socket, responseStatus_t value);

        response_t sendString(Socket *socket, char (path)[100]);
        response_t sendMessageType(Socket *socket, message_t type);
        response_t sendUInt(Socket *socket, unsigned int size);

    public:
        response_t sendSerializedEvent(Socket *socket, Message *message);
};

#endif