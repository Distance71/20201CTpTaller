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

    // char path[100];
    // if (socket->receiveMessage((void *&) path, sizeof(path)) <= 0){
    //     Logger::getInstance()->log(DEBUG, "Error al recibir el path EndStage");
    //     return this->_handleErrorStatus();
    // }

    // MessageEndStage *message = new MessageEndStage(path);
    // event = message->deSerialize();
    
    // if(!event){
    //     Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento EndStage");
    //     return this->_handleErrorStatus();
    // }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventGameInit(Socket *socket, Event* &event){
    
    // screen_t screenSizes;

    // if (socket->receiveMessage((void *&) screenSizes, sizeof(screen_t)) <= 0){
    //     Logger::getInstance()->log(DEBUG, "Error al recibir el path EndStage");
    //     return this->_handleErrorStatus();
    // }

    // Message *message = new MessageGameInit(screenSizes);
    // event = message->deSerialize();
    
    // if(!event){
    //     Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento GameInit");
    //     return this->_handleErrorStatus();
    // }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventInitStage(Socket *socket, Event* &event){

    // char layer[7][100];

    // for(size_t i = 0; i < 7; i++){
    //     for(size_t j = 0; j < 100; j++) {
    //         if (socket->receiveMessage((void *&) layer[i], sizeof(char) * 100) <= 0){
    //             Logger::getInstance()->log(DEBUG, "Error al recibir el message en InitStage");
    //             return this->_handleErrorStatus();
    //         }
    //     }
    // }
    
    // MessageInitStage *message = new MessageInitStage(layer);
    // event = message->deSerialize();
    
    // if(!event){
    //     Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento InitStage");
    //     return this->_handleErrorStatus();
    // }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventLog(Socket *socket, Event* &event){
    
    size_t level;
    char messageLog[100];

    this->getInteger(socket, &level, sizeof(size_t));
    this->getString(socket, messageLog);

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
    char imagePath[100];
    position_t position;
    spriteSize_t spriteSize;

    this->getInteger(socket, &id_, sizeof(size_t));
    this->getString(socket, imagePath);
    this->getPosition(socket, position);
    this->getInteger(socket, &spriteSize.width, sizeof(unsigned int));
    this->getInteger(socket, &spriteSize.height, sizeof(unsigned int));

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

    this->getInteger(socket, &id_, sizeof(size_t));

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
    position_t position;

    this->getInteger(socket, &id_, sizeof(size_t));
    this->getPosition(socket, position);

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

    this->getInteger(socket, &id_, sizeof(size_t));

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

    this->getInteger(socket, &id_, sizeof(size_t));

    MessagePlayerReconnect *message = new MessagePlayerReconnect(id_);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento PlayerReconnect");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventRequestLoginPlayer(Socket *socket, Event* &event){
   
    char userName_[100];
    char password_[100];

    this->getString(socket, userName_);
    this->getString(socket, password_);

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
    
    this->getResponseStatus(socket, responseStatus);

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
    
    this->getOrientation(socket, orientation);

    MessageUserMovement *message = new MessageUserMovement(orientation);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento UserMovement");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getInteger(Socket *socket, void *value, size_t size){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje entero.");

    if (socket->receiveMessage(s, sizeof(size)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de typeMessage.");
        return this->_handleErrorStatus();
    }

    string msg = s.str();
    *((int *)value) = (int) atoi(msg.c_str());
}

response_t MessageDeserializer::getTypeMessage(Socket *socket, message_t &message){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje");

    if (socket->receiveMessage(s, sizeof(message_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de typeMessage.");
        return this->_handleErrorStatus();
    }

    string msg = s.str();
    message = (message_t) atoi(msg.c_str());
}

response_t MessageDeserializer::getResponseStatus(Socket *socket, responseStatus_t &response){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje responseStatus");

    if (socket->receiveMessage(s, sizeof(responseStatus_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de responseStatus.");
        return this->_handleErrorStatus();
    }

    string msg = s.str();
    response = (responseStatus_t) atoi(msg.c_str());
}

response_t MessageDeserializer::getString(Socket *socket, char (&path)[100]){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje string.");

    if (socket->receiveMessage(s, sizeof(path)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de string.");
        return this->_handleErrorStatus();
    }

    string msg = s.str();
    strcpy(path, msg.c_str());
}

response_t MessageDeserializer::getPosition(Socket *socket, position_t &position){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje position.");
    
    this->getInteger(socket, &position.axis_x, sizeof(int));
    this->getInteger(socket, &position.axis_y, sizeof(int));
    this->getOrientation(socket, position.orientation);
}

response_t MessageDeserializer::getOrientation(Socket *socket, orientation_t &orientation){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje orientation");

    if (socket->receiveMessage(s, sizeof(orientation_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de orientation.");
        return this->_handleErrorStatus();
    }

    string msg = s.str();
    orientation = (orientation_t) atoi(msg.c_str());
}

response_t MessageDeserializer::getReceivedMessage(Socket *socket, Event* &event){
    message_t messageType;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje en Deserializer.");

    this->getTypeMessage(socket, messageType);

    Logger::getInstance()->log(DEBUG, "Se ha recibido un tipo de mensaje en Deserializer.");
    
    /*switch (messageType){
        case ANIMATION_INIT_STAGE:
            return

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
    }*/

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