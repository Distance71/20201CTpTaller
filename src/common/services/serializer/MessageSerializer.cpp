#include "MessageSerializer.h"

response_t MessageSerializer::_handleErrorStatus()
{
    Logger::getInstance()->log(ERROR, "No se ha podido obtener el mensaje");
    response_t response = {false, ERROR_CONNECTION};

    return response;
}

response_t MessageSerializer::_handleSuccess()
{
    response_t response = {true, OK};

    return response;
}

response_t MessageSerializer::sendSerializedEvent(Socket *socket, Event *event)
{
    Message *message = event->serialize();
    size_t messageSize = sizeof(*message);
    void *messageRef = (void *) &messageSize;

    if(socket->sendMessage((void *&) messageRef, sizeof(size_t)) <= 0)
        return this->_handleErrorStatus();

    if (socket->sendMessage((void *&) message, sizeof(*message)) <= 0)
        return this->_handleErrorStatus();

    return this->_handleSuccess();
}