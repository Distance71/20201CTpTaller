#include "MessageDeserializer.h"

response_t MessageDeserializer::receiveGameInit(Socket *socket, Event* &event){
    MessageGameInit *message;

    if (socket->receiveMessage((char *) message, sizeof(MessageGameInit)) <= 0)
        return this->_handleErrorStatus();

    event = message->deSerialize();
    return this->_handleSuccess();
}

response_t MessageDeserializer::_handleErrorStatus(){
    Logger::getInstance()->log(ERROR, "No se ha podido obtener el mensaje");
    response_t response = {false, ERROR_CONNECTION};

    return response;
}

response_t MessageDeserializer::_handleSuccess(){
    response_t response = {true, OK};

    return response;
}

response_t MessageDeserializer::getReceivedMessage(User* user, Event* &event){
    
    message_t typeMessage;

    auto socket = user->getSocket();

    if (socket->receiveMessage((char *) &typeMessage, sizeof(message_t)) <= 0)
        return this->_handleErrorStatus();

    switch (typeMessage){

        case INIT_GAME:
            response_t response = this->receiveGameInit(socket, event);
            return response;
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
    }

};

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
