#include "MessageDeserializer.h"

void MessageDeserializer::_read(Socket *socket, void *value){
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
}

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
    /*MessageGameInit *message;

    if (socket->receiveMessage((char *) message, sizeof(MessageGameInit)) <= 0)
        return this->_handleErrorStatus();

    event = message->deSerialize();*/
    return this->_handleSuccess();
}

// MessageActionPlayer *MessageDeserializer::receiveActionPlayer(Socket *socket){

//     char enterKey, quitKey;

//     _read(socket, (char *) &enterKey);
//     _read(socket, (char *) &quitKey);

//     return new MessageActionPlayer(enterKey, quitKey);   
// };

// MessageInitEntity *MessageDeserializer::receiveInitEntity(Socket *socket){

//     unsigned int step;
//     IdElement id;
//     int sizeX, sizeY, posX, posY, source_length;
//     char isPlayer;

//     //Also could be better, but's it's less
//     _read(socket, (char *) &step);
//     _read(socket, (char *) &id);
//     _read(socket, (char *) &sizeX);
//     _read(socket, (char *) &sizeY);
//     _read(socket, (char *) &posX);
//     _read(socket, (char *) &posY);
//     _read(socket, (char *) &source_length);

//     char *source = new char[source_length + 1];
//     source[source_length] = '\0';
//     _readString(socket, (void **) &source);

//     _read(socket, (char *) &isPlayer);

//     MessageInitEntity *message = new MessageInitEntity(step, id, sizeX, sizeY, posX, posY, source, isPlayer);

//     delete [] source;
//     return message;
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

/*
eventsManager->generate('PLAYER1_LOG', )


eventsManager->generate('LOG', "El usuario tanto se desconectó")

eventsManager::generate(key, value){
    if(includes('GENERAL'))
    switch(key) {

        case LOG:
            eventsQueue.push(LOG, value);
            break;
    }
    
}

//Hilo procesamiento!messagesQueue.isEmpty()!messagesQueue.isEmpty()
while(eventsQueue.size() && gameIsRunning) {
    auto event = eventsQueue.pop()

    eventSerilized = event.serialize();

    transmition.addMessage(eventSerilized);
}

//Hilo general
transmitionManager::addMessage(message){
    messagesQueue.push(message);
}

//1 hilo por cliente
trasmitionManager::sendingCycle(){
    
}*/


// MessageLoginPlayer *MessageDeserializer::receiveLoginPlayer(Socket *socket){

//     int name_length, password_length;
    
//     _read(socket, (char *) &name_length);

//     char *userName = new char[name_length + 1];
//     userName[name_length] = '\0';
//     //_readString(socket, (char **) userName);

//     _read(socket, (char *) &password_length);
    
//     char *password = new char[password_length + 1];
//     password[password_length] = '\0';
//     //_readString(socket, (char *) password);

//     MessageLoginPlayer *message = new MessageLoginPlayer(userName, password);

//     delete [] userName;
//     delete [] password;
//     return message;    
// };

// MessageMovementPlayer *MessageDeserializer::receiveMovementPlayer(Socket *socket){

//     orientation_t moveOrientation;
//     _read(socket, (char *) &moveOrientation);

//     return new MessageMovementPlayer(moveOrientation);
// };
        
// MessageRequestLoginPlayer *MessageDeserializer::receiveRequestLoginPlayer(Socket *socket){

//     char authorize;
//     _read(socket, (char *) &authorize);

//     return new MessageRequestLoginPlayer(authorize);
// };

// MessageUpdateEntity *MessageDeserializer::receiveUpdateEntity(Socket *socket){
            
//     unsigned int step;
//     IdElement id;
//     int posX, posY;

//     _read(socket, (char *) &step);
//     _read(socket, (char *) &id);
//     _read(socket, (char *) &posX);
//     _read(socket, (char *) &posY);

//     MessageUpdateEntity *message = new MessageUpdateEntity(step, id, posX, posY);

//     return message; 
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
