#include "MessageDeserializer.h"

response_t MessageDeserializer::_handleErrorStatus(){
    Logger::getInstance()->log(ERROR, "No se ha podido obtener el mensaje");
    response_t response = {false, ERROR_CONNECTION};

    return response;
}

response_t MessageDeserializer::_handleErrorMessage() {
    Logger::getInstance()->log(ERROR, "Mensaje invalido.");    
    response_t response = {false, ERROR_MESSAGE};

    return response;
}

response_t MessageDeserializer::_handleSuccess(){
    response_t response = {true, OK};

    return response;
}

response_t MessageDeserializer::getEventEndGame(Socket *socket, Event* &event){

    MessageEndGame *message = new MessageEndGame();
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento EndGame");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventEndStage(Socket *socket, Event* &event){

    char path[100];
    if (socket->receiveMessage((void *&) path, sizeof(path)) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir el path EndStage");
        return this->_handleErrorStatus();
    }

    MessageEndStage *message = new MessageEndStage(path);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento EndStage");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventGameInit(Socket *socket, Event* &event){
    
    screen_t screenSizes;

    if (socket->receiveMessage((void *&) screenSizes, sizeof(screen_t)) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir el path EndStage");
        return this->_handleErrorStatus();
    }

    Message *message = new MessageGameInit(screenSizes);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento GameInit");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventInitStage(Socket *socket, Event* &event){

    char layer[7][100];

    for(size_t i = 0; i < 7; i++){
        for(size_t j = 0; j < 100; j++) {
            if (socket->receiveMessage((void *&) layer[i], sizeof(char) * 100) <= 0){
                Logger::getInstance()->log(DEBUG, "Error al recibir el message en InitStage");
                return this->_handleErrorStatus();
            }
        }
    }
    
    MessageInitStage *message = new MessageInitStage(layer);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento InitStage");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventLog(Socket *socket, Event* &event){
    
    int level;

    if (socket->receiveMessage((void *&) level, sizeof(int)) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir el level en Log");
        return this->_handleErrorStatus();
    }

    char messageLog[100];
    if (socket->receiveMessage((void *&) messageLog, sizeof(char) * 100) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir el message en Log");
        return this->_handleErrorStatus();
    }

    MessageLog *message = new MessageLog(level, messageLog);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento Log");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventMapElementCreate(Socket *socket, Event* &event){
    
    size_t id_;

    if (socket->receiveMessage((void *&) id_, sizeof(size_t)) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir el id en MapElementCreate");
        return this->_handleErrorStatus();
    }

    char imagePath[100];
    if (socket->receiveMessage((void *&) imagePath, sizeof(char) * 100) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir el path en MapElementCreate");
        return this->_handleErrorStatus();
    }

    position_t position;

    if (socket->receiveMessage((void *&) position, sizeof(size_t)) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir la posicion en MapElementCreate");
        return this->_handleErrorStatus();
    }

    spriteSize_t spriteSize;

    if (socket->receiveMessage((void *&) spriteSize, sizeof(spriteSize_t)) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir el sprite en MapElementCreate");
        return this->_handleErrorStatus();
    }

    MessageMapElementCreate *message = new MessageMapElementCreate(id_, imagePath, position, spriteSize);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento MapElementCreate");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventMapElementDelete(Socket *socket, Event* &event){

    size_t id_;

    if (socket->receiveMessage((void *&) id_, sizeof(size_t)) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir el id en MapElementDelete");
        return this->_handleErrorStatus();
    }

    MessageMapElementDelete *message = new MessageMapElementDelete(id_);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento MapElementDelete");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventMapElementUpdate(Socket *socket, Event* &event){

    size_t id_;

    if (socket->receiveMessage((void *&) id_, sizeof(size_t)) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir el id en MapElementUpdate");
        return this->_handleErrorStatus();
    }

    position_t position;

    if (socket->receiveMessage((void *&) position, sizeof(size_t)) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir la posicion en MapElementUpdate");
        return this->_handleErrorStatus();
    }

    MessageMapElementUpdate *message = new MessageMapElementUpdate(id_, position);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento MapElementUpdate");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventPlayerDisconnect(Socket *socket, Event* &event){

    size_t id_;

    if (socket->receiveMessage((void *&) id_, sizeof(size_t)) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir el id en PlayerDisconnect");
        return this->_handleErrorStatus();
    }

    MessagePlayerDisconnect *message = new MessagePlayerDisconnect(id_);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento PlayerDisconnect");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventPlayerReconnect(Socket *socket, Event* &event){
    
    size_t id_;

    if (socket->receiveMessage((void *&) id_, sizeof(size_t)) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir el id en PlayerReconnect");
        return this->_handleErrorStatus();
    }

    MessagePlayerReconnect *message = new MessagePlayerReconnect(id_);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento PlayerReconnect");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventRequestLoginPlayer(Socket *socket, Event* &event){
   
    char userName_[30];
    char password_[30];

    if (socket->receiveMessage((void *&) userName_, sizeof(char) * 30) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir el nombre de usuario en RequestLoginPlayer");
        return this->_handleErrorStatus();
    }

    if (socket->receiveMessage((void *&) password_, sizeof(char) * 30) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir la password de usuario en RequestLoginPlayer");
        return this->_handleErrorStatus();
    }

    MessageRequestLoginPlayer *message = new MessageRequestLoginPlayer(userName_, password_);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento RequestLoginPlayer");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventResponseLoginPlayer(Socket *socket, Event* &event){
    
    responseStatus_t responseStatus;
    if (socket->receiveMessage((void *&) responseStatus, sizeof(responseStatus_t)) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir el path UserMovement");
        return this->_handleErrorStatus();
    }

    MessageResponseLoginPlayer *message = new MessageResponseLoginPlayer(responseStatus);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento ResponseLoginPlayer");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventUserMovement(Socket *socket, Event* &event){
    
    orientation_t orientation;
    if (socket->receiveMessage((void *&) orientation, sizeof(orientation_t)) <= 0){
        Logger::getInstance()->log(DEBUG, "Error al recibir el path UserMovement");
        return this->_handleErrorStatus();
    }

    MessageUserMovement *message = new MessageUserMovement(orientation);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento UserMovement");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

// response_t MessageDeserializer::getEvent(message_t messageType, Socket *socket, Event* &event){
    
//     if(!socket){
//         Logger::getInstance()->log(DEBUG, "Se recibio puntero null al recibir evento");
//         Logger::getInstance()->log(ERROR, "Error interno al recibir evento");
//         cout << "No se ha podido recibir un evento, puntero null" << endl;
//     }

//     Message *buffer = (Message*) malloc (sizeof(MessageRequestLoginPlayer)); //For testing

//     if (socket->receiveMessage((void *&) buffer, sizeof(*buffer)) <= 0){
//         Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento");
//         return this->_handleErrorStatus();
//     }

//     event = ((Message *)buffer)->deSerialize();

//     if(!event){
//         Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento en Deserializer");
//         cout << "No se ha podido recibir un evento en Deserializer" << endl;
//         return this->_handleErrorStatus();
//     }
//     return this->_handleSuccess();
// }

response_t MessageDeserializer::getReceivedMessage(Socket *socket, Event* &event){
    message_t messageType;
    void *messageRef = &messageType;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje en Deserializer.");

    if (socket->receiveMessage((void *&) messageRef, sizeof(message_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje.");
        return this->_handleErrorStatus();
    }

    cout << END_GAME << " " << (message_t)messageType << endl;;

    Logger::getInstance()->log(DEBUG, "Se ha recibido un tipo de mensaje en Deserializer.");
    
    switch (messageType){
        /*
        case ANIMATION_INIT_STAGE:
            return */

        case END_GAME:
            return this->getEventEndGame(socket, event);

        case END_STAGE:
            return this->getEventEndStage(socket, event);

        case GAME_INIT:
            return this->getEventGameInit(socket, event);

        case INIT_STAGE:
            return this->getEventInitStage(socket, event);

        case LOG:
            return this->getEventLog(socket, event);

        case MAP_ELEMENT_CREATE:
            return this->getEventMapElementCreate(socket, event);

        case MAP_ELEMENT_DELETE:
            return this->getEventMapElementDelete(socket, event);

        case MAP_ELEMENT_UPDATE:
            return this->getEventMapElementUpdate(socket, event);
    
        case PLAYER_DISCONNECT:
            return this->getEventPlayerDisconnect(socket, event);

        case PLAYER_RECONNECT:
            return this->getEventPlayerReconnect(socket, event);

        case REQUEST_LOGIN_PLAYER:
            return this->getEventRequestLoginPlayer(socket, event);

        case RESPONSE_LOGIN_PLAYER:
            return this->getEventResponseLoginPlayer(socket, event);

        case USER_MOVEMENT:
            return this->getEventUserMovement(socket, event);
    }

    Logger::getInstance()->log(ERROR, "No se ha recibido un tipo de mensaje conocido.");

    return this->_handleErrorMessage();
};

/*response_t MessageDeserializer::getReceivedMessage(Socket *socket, Event* &event){
    message_t messageType;
    void* _typeRef = (void *) &messageType;

    if (socket->receiveMessage(_typeRef, sizeof(message_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje.");
        return this->_handleErrorStatus();
    }
    Logger::getInstance()->log(DEBUG, "Se recibio el tamaño de un mensaje.");
    return this->getEvent(messageType, socket, event);
};*/