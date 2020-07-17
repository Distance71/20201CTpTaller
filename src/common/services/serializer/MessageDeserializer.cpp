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
    Logger::getInstance()->log(DEBUG, "Se va a recibir un mensaje EndGame en Deserializer");

    MessageEndGame *message = new MessageEndGame();
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento EndGame");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventEndStage(Socket *socket, Event* &event){
    // Logger::getInstance()->log(DEBUG, "Se va a recibir un mensaje EndStage en Deserializer");

    // char path[100];
    
    // this->getString(socket, path);

    // MessageEndStage *message = new MessageEndStage(path);
    // event = message->deSerialize();
    
    // if(!event){
    //     Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento EndStage");
    //     return this->_handleErrorStatus();
    // }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventGameInit(Socket *socket, Event* &event){
    Logger::getInstance()->log(DEBUG, "Se va a recibir un mensaje GameInit en Deserializer");
    screen_t screenSizes;

    this->getUInteger(socket, screenSizes.width);
    this->getUInteger(socket, screenSizes.height);

    Message *message = new MessageGameInit(screenSizes);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento GameInit");
        return this->_handleErrorStatus();
    }

    Logger::getInstance()->log(DEBUG, "Se ha recibido un mensaje GameInit en Deserializer");
    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventInitStage(Socket *socket, Event* &event){
    Logger::getInstance()->log(DEBUG, "Se va a recibir un mensaje InitStage en Deserializer");
    char layer[7][100];

    for(size_t i = 0; i < 7; i++)
        this->getString(socket, layer[i]);
    
    MessageInitStage *message = new MessageInitStage(layer);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento InitStage");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventLog(Socket *socket, Event* &event){
    Logger::getInstance()->log(DEBUG, "Se va a recibir un mensaje Log en Deserializer");
    size_t level;
    char messageLog[100];

    this->getLongInteger(socket, level);
    this->getString(socket, messageLog);

    MessageLog *message = new MessageLog(level, messageLog);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento Log");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventMapElementUpdate(Socket *socket, Event* &event){
    // Logger::getInstance()->log(DEBUG, "Se va a recibir un mensaje MapElementUpdate en Deserializer");
    
    // size_t id_;
    // position_t position;

    // this->getLongInteger(socket, id_);
    // this->getPosition(socket, position);

    // MessageMapElementUpdate *message = new MessageMapElementUpdate(id_, position);
    // event = message->deSerialize();
    
    // if(!event){
    //     Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento MapElementUpdate");
    //     return this->_handleErrorStatus();
    // }

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventRequestLoginPlayer(Socket *socket, Event* &event){
   Logger::getInstance()->log(DEBUG, "Se va a recibir un mensaje RequestLogin en Deserializer");
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
    
    Logger::getInstance()->log(DEBUG, "Se va a recibir un evento ResponseLoginPlayer en Deserializer");
    responseStatus_t responseStatus;
    
    this->getResponseStatus(socket, responseStatus);

    MessageResponseLoginPlayer *message = new MessageResponseLoginPlayer(responseStatus);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento ResponseLoginPlayer");
        return this->_handleErrorStatus();
    }

    Logger::getInstance()->log(DEBUG, "Se recibio un evento ResponseLoginPlayer en Deserializer");

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventAnimationInitStage(Socket *socket, Event* &event){
    // Logger::getInstance()->log(DEBUG, "Se va a recibir un mensaje AnimationInitStage en Deserializer");
    // char path[100];

    // this->getString(socket, path);

    // MessageAnimationInitStage *message = new MessageAnimationInitStage(path);
    // event = message->deSerialize();
    
    // if(!event){
    //     Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento RequestLoginPlayer");
    //     return this->_handleErrorStatus();
    // }

    return this->_handleSuccess();
}


response_t MessageDeserializer::getEventUserMovement(Socket *socket, Event* &event){
    Logger::getInstance()->log(DEBUG, "Se va a recibir un mensaje UserMovement Deserializer");
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

response_t MessageDeserializer::getLongInteger(Socket *socket, size_t &value){
    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje entero.");

    if (socket->receiveMessage(s, sizeof(size_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de typeMessage.");
        return this->_handleErrorStatus();
    }

    string msg = s.str();
    value = atoi(msg.c_str());
}

response_t MessageDeserializer::getUInteger(Socket *socket, unsigned int &value){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje entero.");

    if (socket->receiveMessage(s, sizeof(unsigned int)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de typeMessage.");
        return this->_handleErrorStatus();
    }

    string msg = s.str();
    value = atoi(msg.c_str());
}

response_t MessageDeserializer::getInteger(Socket *socket, int &value){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje entero.");

    if (socket->receiveMessage(s, sizeof(int)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de typeMessage.");
        return this->_handleErrorStatus();
    }

    string msg = s.str();
    value = atoi(msg.c_str());
}

response_t MessageDeserializer::getTypeMessage(Socket *socket, message_t &message){

    stringstream s;

    int res = socket->receiveMessage(s, sizeof(message_t));
    if (res){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de typeMessage.");
        return this->_handleErrorStatus();
    }
    else if (res==0){
        return {false, DISCONNECTION};
    }

    string msg = s.str();

    message = (message_t) atoi(msg.c_str());
    Logger::getInstance()->log(DEBUG, "Se ha recibido con exito un tipo de mensaje");

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
    
    this->getInteger(socket, position.axis_x);
    this->getInteger(socket, position.axis_y);
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

    response_t res = this->getTypeMessage(socket, messageType);
    
    if (res.status == DISCONNECTION){
        return res;
    }

    switch (messageType){
        case ANIMATION_INIT_STAGE:
            return this->getEventAnimationInitStage(socket, event);

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

        case MAP_ELEMENT_UPDATE:
            return this->getEventMapElementUpdate(socket, event);
    
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