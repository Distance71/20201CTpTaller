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

response_t MessageDeserializer::receiveGameInit(Socket *socket, Event* &event){
    
    unsigned int width, height;

    if (socket->receiveMessage((char *) &width, sizeof(unsigned int)) <= 0)
        return this->_handleErrorStatus();

    if (socket->receiveMessage((char *) &height, sizeof(unsigned int)) <= 0)
        return this->_handleErrorStatus();

    MessageGameInit *message = new MessageGameInit(width, height);

    /*event = message->deSerialize();*/
    delete message;

    return this->_handleSuccess();
}

response_t MessageDeserializer::receiveInitEntity(Socket *socket, Event* &event){

    IdElement id;
    int sizeX, sizeY, posX, posY, source_length;
    orientation_t orientation;

    if (socket->receiveMessage((char *) &id, sizeof(IdElement)) <= 0)
        return this->_handleErrorStatus();

    if (socket->receiveMessage((char *) &sizeX, sizeof(int)) <= 0)
        return this->_handleErrorStatus();

    if (socket->receiveMessage((char *) &sizeY, sizeof(int)) <= 0)
        return this->_handleErrorStatus();

    if (socket->receiveMessage((char *) &posX, sizeof(int)) <= 0)
        return this->_handleErrorStatus();

    if (socket->receiveMessage((char *) &posY, sizeof(int)) <= 0)
        return this->_handleErrorStatus();

    if (socket->receiveMessage((char *) &orientation, sizeof(orientation_t)) <= 0)
        return this->_handleErrorStatus();

    if (socket->receiveMessage((char *) &source_length, sizeof(int)) <= 0)
        return this->_handleErrorStatus();

    char *source = new char[source_length + 1];
    source[source_length] = '\0';

    if (socket->receiveMessage(source, sizeof(char) * source_length) <= 0){
        delete [] source;
        return this->_handleErrorStatus();
    }
    
    MessageInitEntity *message = new MessageInitEntity(id, sizeX, sizeY, posX, posY, orientation, source);

    delete [] source;
    delete message;
    return this->_handleSuccess();
};

response_t MessageDeserializer::receiveUpdateEntity(Socket *socket, Event* &event){
            
    IdElement id;
    int posX, posY;
    orientation_t orientation;

    if (socket->receiveMessage((char *) &id, sizeof(IdElement)) <= 0)
        return this->_handleErrorStatus();

    if (socket->receiveMessage((char *) &posX, sizeof(int)) <= 0)
        return this->_handleErrorStatus();

    if (socket->receiveMessage((char *) &posY, sizeof(int)) <= 0)
        return this->_handleErrorStatus();

    if (socket->receiveMessage((char *) &orientation, sizeof(orientation_t)) <= 0)
        return this->_handleErrorStatus();

    MessageUpdateEntity *message = new MessageUpdateEntity(id, posX, posY, orientation);

    delete message;
    return this->_handleSuccess(); 
};

response_t MessageDeserializer::receiveRequestLoginPlayer(Socket *socket, Event* &event){

    int name_length, password_length;
    
    if (socket->receiveMessage((char *) &name_length, sizeof(int)) <= 0)
        return this->_handleErrorStatus();

    char *userName = new char[name_length + 1];
    userName[name_length] = '\0';

    if (socket->receiveMessage(userName, sizeof(char) * name_length) <= 0){
        delete [] userName;
        return this->_handleErrorStatus();
    }

    if (socket->receiveMessage((char *) &password_length, sizeof(int)) <= 0)
        return this->_handleErrorStatus();

    char *password = new char[password_length + 1];
    password[password_length] = '\0';

    if (socket->receiveMessage(password, sizeof(char) * password_length) <= 0){
        delete [] password;
        return this->_handleErrorStatus();
    }

    MessageRequestLoginPlayer *message = new MessageRequestLoginPlayer(userName, password);

    delete [] userName;
    delete [] password;

    delete message;
    return this->_handleSuccess(); 
};

response_t MessageDeserializer::receiveMovementPlayer(Socket *socket, Event* &event){

    orientation_t moveOrientation;

    if (socket->receiveMessage((char *) &moveOrientation, sizeof(orientation_t)) <= 0)
        return this->_handleErrorStatus();

    MessageMovementPlayer *message = new MessageMovementPlayer(moveOrientation);

    delete message;
    return this->_handleSuccess(); 
};


response_t MessageDeserializer::receiveResponseLoginPlayer(Socket *socket, Event* &event){

    char successfulConnection, gameFull, wrongCredentials;

    if (socket->receiveMessage(&successfulConnection, sizeof(char)) <= 0)
        return this->_handleErrorStatus();

    if (socket->receiveMessage(&gameFull, sizeof(char)) <= 0)
        return this->_handleErrorStatus();

    if (socket->receiveMessage(&wrongCredentials, sizeof(char)) <= 0)
        return this->_handleErrorStatus();

    MessageResponseLoginPlayer *message = new MessageResponseLoginPlayer(successfulConnection, gameFull, wrongCredentials);

    delete message;  
    return this->_handleSuccess();      
};

// MessageActionPlayer *MessageDeserializer::receiveActionPlayer(Socket *socket){

//     char enterKey, quitKey;

//     _read(socket, (char *) &enterKey);
//     _read(socket, (char *) &quitKey);

//     return new MessageActionPlayer(enterKey, quitKey);   
// };

// MessageInitLayer *MessageDeserializer::receiveInitLayer(Socket *socket){
    
//     size_t id;
//     int source_length;

//     _read(socket, (char *) &id);
//     _read(socket, (char *) &source_length);

//     char *source = new char[source_length + 1];
//     source[source_length] = '\0';
//     //_readString(socket, (char *) source);

//     MessageInitLayer *message = new MessageInitLayer(id, source);

//     delete [] source;
//     return message;
// };

// MessageInitScreen *MessageDeserializer::receiveInitScreen(Socket *socket){

//     unsigned int width;
//     unsigned int height;

//     _read(socket, (char *) &width);
//     _read(socket, (char *) &height);

//     return new MessageInitScreen(width, height);
// };

// MessageUpdateStage *MessageDeserializer::receiveUpdateStage(Socket *socket){

//     char level, isStart, isEnd;

//     _read(socket, (char *) &level);
//     _read(socket, (char *) &isStart);
//     _read(socket, (char *) &isEnd);

//     MessageUpdateStage *message = new MessageUpdateStage((level_t) level, isStart, isEnd);

//     return message;        
// };

/*
Event *MessageDeserializer::getReceivedMessage(User *user){
    
    char typeMessage; //message_t ?

    auto socket = user->getSocket();

    if (socket->receiveMessage(&typeMessage, sizeof(char)) <= 0) {
        Logger::getInstance()->log(ERROR, "No se ha podido obtener el mensaje");
    }

    switch (typeMessage){

        case INIT_GAME:
            return this->receiveGameInit(socket);
        // case INIT_ENTITY:
        //     return this->receiveInitEntity(socket);

        // case UPDATE_ENTITY:
        //     return this->receiveUpdateEntity(socket);

        // case INIT_LAYER:
        //     return this->receiveInitLayer(socket);

        // case INIT_SCREEN:
        //     return this->receiveInitScreen(socket);

        // case UPDATE_STAGE:
        //     return this->receiveUpdateStage(socket);

        // case MOVEMENT_PLAYER:
        //     return this->receiveMovementPlayer(socket);

        // case ACTION_PLAYER:
        //     return this->receiveActionPlayer(socket);

        default:
            //Log error
            Logger::getInstance()->log(ERROR, "Mensaje invalido.");
    }

};*/

// void MessageDeserializer::pushNewMessage(Socket *socket, bool &error, EventsQueue *queueEvents){
//     char typeMessage = NONE;

//     if (error)
//         return;
    
//     if (socket->receiveMessage(&typeMessage, sizeof(char)) <= 0)
//         error = true;

//     switch (typeMessage){

//         case LOG:

//             break;

//         case INIT_ENTITY:
//             queueEvents->push(this->receiveInitEntity(socket, error));
//             break;

//         case UPDATE_ENTITY:
//             queueMessage->push_back(this->receiveUpdateEntity(socket, error));
//             break;

//         case INIT_LAYER:
//             queueMessage->push_back(this->receiveInitLayer(socket, error));
//             break;

//         case INIT_SCREEN:
//             queueMessage->push_back(this->receiveInitScreen(socket, error));
//             break;

//         case UPDATE_STAGE:
//             queueMessage->push_back(this->receiveUpdateStage(socket, error));
//             break;

//         case LOGIN_PLAYER:
//             queueMessage->push_back(this->receiveLoginPlayer(socket, error));
//             break;

//         case MOVEMENT_PLAYER:
//             queueMessage->push_back(this->receiveMovementPlayer(socket, error));
//             break;

//         case REQUEST_LOGIN_PLAYER:
//             queueMessage->push_back(this->receiveRequestLoginPlayer(socket, error));
//             break;

//         case ACTION_PLAYER:
//             queueMessage->push_back(this->receiveActionPlayer(socket, error));
//             break;

//         case NONE:
//         default:
//             queueMessage->push_back(new NoneMessage());
//             break;
//     }    
// };

/*void MessageDeserializer::_read(Socket *socket, void *value){
    int status = socket->receiveMessage((char *)value, sizeof(value));
    if (status < 0){
        //handle error
    }
}

void MessageDeserializer::_readString(Socket *socket, void **value){
    int status = socket->receiveMessage((char *) *value, strlen((char *) *value) + 1);
    if (status < 0){
        //handle error
    }
}*/