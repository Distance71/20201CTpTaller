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

response_t MessageDeserializer::getEvent(message_t messageType, Socket *socket, Event* &event){
    
    if(!socket){
        Logger::getInstance()->log(DEBUG, "Se recibio puntero null al recibir evento");
        Logger::getInstance()->log(ERROR, "Error interno al recibir evento");
        cout << "No se ha podido recibir un evento, puntero null" << endl;
    }

    Message *buffer = (Message*) malloc (sizeof(MessageRequestLoginPlayer)); //For testing

    cout << "Here" << endl;
    if (socket->receiveMessage((void *&) buffer, sizeof(*buffer)) <= 0)
        return this->_handleErrorStatus();

    cout << "el tipo " << endl;
    event = ((Message *)buffer)->deSerialize();

    if(!event){
        Logger::getInstance()->log(ERROR, "No se ha podido recibir un evento");
        cout << "No se ha podido recibir un evento" << endl;
        return this->_handleErrorStatus();
    }
    return this->_handleSuccess();
}

response_t MessageDeserializer::getReceivedMessage(Socket *socket, Event* &event){
    message_t messageType;
    void* _typeRef = (void *) &messageType;

    if (socket->receiveMessage(_typeRef, sizeof(message_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al recibir el mensaje.");
        return this->_handleErrorStatus();
    }
    Logger::getInstance()->log(DEBUG, "Se recibio el tamaño de un mensaje.");
    return this->getEvent(messageType, socket, event);
};