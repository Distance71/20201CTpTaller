#ifndef MESSAGE_SERIALIZER_H_
#define MESSAGE_SERIALIZER_H_


#include "../../models/Socket.h"
#include "../../models/events/Event.h"
#include "../../services/Logger.h"
#include "../../models/messages/Message.h"
#include "../../models/messages/MessageSceneAnimation.h"
#include "../../models/messages/MessageGameInit.h"
#include "../../models/messages/MessageLog.h"
#include "../../models/messages/MessageMapElementUpdate.h"
#include "../../models/messages/MessageUserMovement.h"
#include "../../models/messages/MessageRequestLoginPlayer.h"
#include "../../models/messages/MessageResponseLoginPlayer.h"
#include "../../models/messages/MessageUserMovement.h"
#include "../../models/messages/MessageBackgroundUpdate.h"
#include "../../models/messages/MessageUserShoot.h"
#include "../../models/messages/MessageUserChangeMode.h"
#include "../../models/messages/MessageMusicUpdate.h"
#include "../../models/messages/MessageScoreUpdate.h"
#include "../../models/messages/MessageGameOver.h"

using namespace std;

class MessageSerializer {
    private:
        response_t _handleErrorStatus();
        response_t _handleSuccess();

        response_t sendMessageSceneAnimation(Socket *socket, Message *message);
        response_t sendMessageEndGame(Socket *socket, Message *message);
        response_t sendMessageGameInit(Socket *socket, Message *message);
        response_t sendMessageLog(Socket *socket, Message *message);
        response_t sendMessageMapElementUpdate(Socket *socket, Message *message);
        response_t sendMessageRequestLoginPlayer(Socket *socket, Message *message);
        response_t sendMessageResponseLoginPlayer(Socket *socket, Message *message);
        response_t sendMessageUserMovement(Socket *socket, Message *message);
        response_t sendMessageBackgroundUpdate(Socket *socket, Message *message);
        response_t sendMessageUserShoot(Socket *socket, Message *message);
        response_t sendMessageUserChangeMode(Socket *socket, Message *message);
        response_t sendMessageMusicUpdate(Socket *socket, Message *message);
        response_t sendMessageScoreUpdate(Socket *socket, Message *message);
        response_t sendMessageGameOver(Socket *socket, Message *message);

        response_t sendResponseType(Socket *socket, responseStatus_t value);

        response_t sendString(Socket *socket, char (path)[100]);
        response_t sendMessageType(Socket *socket, message_t type);
        response_t sendInteger(Socket *socket, int &value);
        response_t sendOrientation(Socket *socket, orientation_t &orientation);
        response_t sendLayer(Socket *socket, layer_t &layer);
        response_t sendLongInteger(Socket *socket, size_t &value);
        response_t sendUInt(Socket *socket, unsigned int size);
        response_t sendElementType(Socket *socket, elementType_t elementType);
        response_t sendSceneScreen(Socket *socket, sceneScreen_t scene);
        response_t sendStage(Socket *socket, stage_t &stage);
        response_t sendMusicType(Socket *socket, musicType_t type);

    public:
        response_t sendSerializedEvent(Socket *socket, Message *message);
};

#endif