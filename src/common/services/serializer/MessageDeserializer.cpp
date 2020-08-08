#include "MessageDeserializer.h"

response_t MessageDeserializer::_handleErrorStatus(){
    Logger::getInstance()->log(DEBUG, "No se ha podido obtener el mensaje");
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

response_t MessageDeserializer::getEventSceneAnimatiom(Socket *socket, Event* &event){
    Logger::getInstance()->log(DEBUG, "Se va a recibir un evento sceneAnimation en Deserializer");
    sceneScreen_t scene;

    this->getSceneScreen(socket, scene);

    MessageSceneAnimation *message = new MessageSceneAnimation(scene);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento sceneAnimation");
        return this->_handleErrorStatus();
    }

    Logger::getInstance()->log(DEBUG, "Se recibio un evento sceneAnimation en Deserializer");
    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventEndGame(Socket *socket, Event* &event){
    Logger::getInstance()->log(DEBUG, "Se va a recibir un evento EndGame en Deserializer");

    MessageEndGame *message = new MessageEndGame();
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento EndGame");
        return this->_handleErrorStatus();
    }
    Logger::getInstance()->log(DEBUG, "Se recibio un evento EndGame en Deserializer");

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventGameInit(Socket *socket, Event* &event){
    Logger::getInstance()->log(DEBUG, "Se va a recibir un evento GameInit en Deserializer");
    screen_t screenSizes;

    this->getUInteger(socket, screenSizes.width);
    this->getUInteger(socket, screenSizes.height);

    Message *message = new MessageGameInit(screenSizes);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento GameInit");
        return this->_handleErrorStatus();
    }

    Logger::getInstance()->log(DEBUG, "Se ha recibido un evento GameInit en Deserializer");
    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventLog(Socket *socket, Event* &event){
    Logger::getInstance()->log(DEBUG, "Se va a recibir un evento Log en Deserializer");
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
    Logger::getInstance()->log(DEBUG, "Se recibio un evento Log en Deserializer");
    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventMapElementUpdate(Socket *socket, Event* &event){
    Logger::getInstance()->log(DEBUG, "Se va a recibir un evento MapElementUpdate en Deserializer");
    
    elementType_t elementType;
    position_t position;

    this->getElementType(socket, elementType);
    this->getPosition(socket, position);

    MessageMapElementUpdate *message = new MessageMapElementUpdate(elementType, position);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento MapElementUpdate");
        return this->_handleErrorStatus();
    }

    Logger::getInstance()->log(DEBUG, "Se recibio un evento MapElementUpdate en Deserializer");
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

response_t MessageDeserializer::getEventBackgroundUpdate(Socket *socket, Event* &event){
    Logger::getInstance()->log(DEBUG, "Se va a recibir un evento BackgroundUpdate en Deserializer");
    layer_t layer;
    stage_t stage;
    int step;

    this->getLayer(socket, layer);
    this->getStage(socket, stage);
    this->getInteger(socket, step);

    Message *message = new MessageBackgroundUpdate(layer, stage, step);
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento BackgroundUpdate");
        return this->_handleErrorStatus();
    }

    Logger::getInstance()->log(DEBUG, "Se ha recibido un evento BackgroundUpdate en Deserializer");
    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventUserShoot(Socket *socket, Event *event){
    Logger::getInstance()->log(DEBUG, "Se va a recibir un evento EndGame en Deserializer");

    Message *message = new MessageUserShoot();
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento EndGame");
        return this->_handleErrorStatus();
    }
    Logger::getInstance()->log(DEBUG, "Se recibio un evento EndGame en Deserializer");

    return this->_handleSuccess();
};

response_t MessageDeserializer::getEventUserChangeMode(Socket *socket, Event *event){
    Logger::getInstance()->log(DEBUG, "Se va a recibir un evento UserChangeMode en Deserializer");

    Message *message = new MessageUserChangeMode();
    event = message->deSerialize();
    
    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento UserChangeMode");
        return this->_handleErrorStatus();
    }
    Logger::getInstance()->log(DEBUG, "Se recibio un evento UserChangeMode en Deserializer");

    return this->_handleSuccess();
};

response_t MessageDeserializer::getLongInteger(Socket *socket, size_t &value){
    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje entero.");

    if (socket->receiveMessage(s, sizeof(size_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de LongInteger.");
        return this->_handleErrorStatus();
    }

    string msg = s.str();
    value = atoi(msg.c_str());
}

response_t MessageDeserializer::getUInteger(Socket *socket, unsigned int &value){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje entero.");

    if (socket->receiveMessage(s, sizeof(unsigned int)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de UInteger.");
        return this->_handleErrorStatus();
    }

    string msg = s.str();
    value = atoi(msg.c_str());
}

response_t MessageDeserializer::getInteger(Socket *socket, int &value){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje entero.");

    if (socket->receiveMessage(s, sizeof(int)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de typeInteger.");
        return this->_handleErrorStatus();
    }

    string msg = s.str();
    value = atoi(msg.c_str());
}

response_t MessageDeserializer::getTypeMessage(Socket *socket, message_t &message){

    stringstream s;

    int res = socket->receiveMessage(s, sizeof(message_t));
 
    if (res < 0 ){
        Logger::getInstance()->log(DEBUG, "Se ha producido un error al recibir el mensaje de typeMessage.");
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

response_t MessageDeserializer::getSceneScreen(Socket *socket, sceneScreen_t &scene){
    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje sceneScreen");

    if (socket->receiveMessage(s, sizeof(sceneScreen_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de sceneScreen.");
        return this->_handleErrorStatus();
    }

    string msg = s.str();
    scene = (sceneScreen_t) atoi(msg.c_str());
}

response_t MessageDeserializer::getElementType(Socket *socket, elementType_t &elementType){
    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje elementType");

    if (socket->receiveMessage(s, sizeof(elementType_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de elementType.");
        return this->_handleErrorStatus();
    }

    string msg = s.str();
    elementType = (elementType_t) atoi(msg.c_str());
}

response_t MessageDeserializer::getLayer(Socket *socket, layer_t &layer){
    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje layer");

    if (socket->receiveMessage(s, sizeof(layer_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de layer.");
        return this->_handleErrorStatus();
    }

    string msg = s.str();
    layer = (layer_t) atoi(msg.c_str());
}

response_t MessageDeserializer::getStage(Socket *socket, stage_t &stage){
    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje stage");

    if (socket->receiveMessage(s, sizeof(stage_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje de stage.");
        return this->_handleErrorStatus();
    }

    string msg = s.str();
    stage = (stage_t) atoi(msg.c_str());
};

response_t MessageDeserializer::getReceivedMessage(Socket *socket, Event* &event){
    message_t messageType;

    Logger::getInstance()->log(DEBUG, "Se va a recibir un tipo de mensaje en Deserializer.");

    response_t res = this->getTypeMessage(socket, messageType);
    
    if (res.status == DISCONNECTION || res.status == ERROR_CONNECTION){
        return res;
    }
    
    switch (messageType){
        case SCENE_ANIMATION:
            return this->getEventSceneAnimatiom(socket, event);

        case END_GAME:
            return this->getEventEndGame(socket, event);

        case GAME_INIT:
            return this->getEventGameInit(socket, event);

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

        case BACKGROUND_UPDATE:
            return this->getEventBackgroundUpdate(socket, event);

        case USER_SHOOT:{
            Message *message = new MessageUserShoot();
            event = message->deSerialize();
            return this->_handleSuccess();
            // return this->getEventUserShoot(socket, event);
        }

        case USER_CHANGE_MODE:{
            Message *message = new MessageUserChangeMode();
            event = message->deSerialize();
            return this->_handleSuccess();
            // return this->getEventUserShoot(socket, event);
        }
    }

    Logger::getInstance()->log(ERROR, "No se ha recibido un tipo de mensaje conocido.");

    return this->_handleErrorMessage();
};
