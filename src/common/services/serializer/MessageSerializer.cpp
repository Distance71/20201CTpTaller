#include "MessageSerializer.h"

response_t MessageSerializer::_handleErrorStatus(){
    Logger::getInstance()->log(ERROR, "No se ha podido obtener el mensaje");
    response_t response = {false, ERROR_CONNECTION};

    return response;
}

response_t MessageSerializer::_handleSuccess(){
    response_t response = {true, OK};

    return response;
}

response_t MessageSerializer::sendSerializedEvent(User *user, Event *event){
    auto socket = user->getSocket();

    Message *message = event->serialize();

    if (socket->sendMessage((char *) message, sizeof(*message)) <= 0)
        return this->_handleErrorStatus();
    
    return this->_handleSuccess();
}