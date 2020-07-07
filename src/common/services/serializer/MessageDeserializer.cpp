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

response_t MessageDeserializer::getEvent(size_t messageSize, Socket *socket, Event* &event){
    void* buffer;

    if (socket->receiveMessage(buffer, messageSize) <= 0)
        return this->_handleErrorStatus();

    event = ((Message *) buffer)->deSerialize(); //Dudando esta expresión, debo probarlo
    return this->_handleSuccess();
}

response_t MessageDeserializer::getReceivedMessage(Socket *socket, Event* &event){
    cout << "daseas" << endl;
    size_t messageSize;
    void* _messageSize = (void *) &messageSize;
    cout << "casi" << endl;
    if (socket->receiveMessage(_messageSize, sizeof(size_t)) <= 0)
        return this->_handleErrorStatus();
    cout << "done"<< endl;
    return this->getEvent(messageSize, socket, event);
};