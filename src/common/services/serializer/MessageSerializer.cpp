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

response_t MessageSerializer::sendMessageAnimationInitStage(Socket *socket, Message *message){

    response_t response = this->sendString(socket, ((MessageAnimationInitStage *) message)->getPath());
    
    if(!response.ok)
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en AnimationInitStage.");

    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageEndGame(Socket *socket, Message *message){
    return this->_handleSuccess(); //No params
}

response_t MessageSerializer::sendMessageEndStage(Socket *socket, Message *message){

    response_t response = this->sendString(socket, ((MessageEndStage *) message)->getPath());
    
    if(!response.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en EndStage.");
        return this->_handleErrorStatus();
    }
    
    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageGameInit(Socket *socket, Message *message){
    screen_t screenSizes = ((MessageGameInit *) message)->getScreenSizes();

    response_t responseWidth = this->sendUInt(socket, screenSizes.width);
    response_t responseHeight = this->sendUInt(socket, screenSizes.height);

    if(!responseWidth.ok || !responseHeight.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en GameInit.");
        return this->_handleErrorStatus();
    }
    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageInitStage(Socket *socket, Message *message){
    char layers[7][100];

    for(size_t i = 0; i < 7; i++)
        strcpy(layers[i], (*((char (*)[7][100]) (((MessageInitStage *) message))->getLayers()) )[i]);

    for(size_t i = 0; i < 7; i++)
        this->sendString(socket, layers[i]);

    //Validar

    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageLog(Socket *socket, Message *message){
    size_t level = ((MessageLog *) message)->getLevel();
    response_t responseLevel = this->sendLongInteger(socket, level);
    response_t responseMessage = this->sendString(socket, ((MessageLog *) message)->getMessage());

    if(!responseLevel.ok || !responseMessage.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en GameInit.");
        return this->_handleErrorStatus();
    }
    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageMapElementCreate(Socket *socket, Message *message){
    size_t id = ((MessageMapElementCreate *) message)->getId();
    position_t position = ((MessageMapElementCreate *) message)->getPosition();
    spriteSize_t spriteSize = ((MessageMapElementCreate *) message)->getSpriteSize();

    response_t responseId = this->sendLongInteger(socket, id);
    response_t responsePath = this->sendString(socket, ((MessageMapElementCreate *) message)->getPath());
    response_t responsePosAxisX = this->sendInteger(socket, position.axis_x);
    response_t responsePosAxisY = this->sendInteger(socket, position.axis_y);
    response_t responseOrientation = this->sendOrientation(socket, position.orientation);
    response_t responseSizeX = this->sendUInt(socket, spriteSize.width);
    response_t responseSizeY = this->sendUInt(socket, spriteSize.height);

    if(!responseId.ok || !responsePath.ok || !responsePosAxisX.ok || !responsePosAxisY.ok || !responseOrientation.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en MapElementCreate.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageMapElementDelete(Socket *socket, Message *message){
    size_t id = ((MessageMapElementDelete *) message)->getId();

    response_t responseId = this->sendLongInteger(socket, id);

    if(!responseId.ok){
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en MapElementDelete.");
        return this->_handleErrorStatus();
    }
        
    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageMapElementUpdate(Socket *socket, Message *message){
    size_t id = ((MessageMapElementUpdate *) message)->getId();
    position_t position = ((MessageMapElementUpdate *) message)->getPosition();

    response_t responseId = this->sendLongInteger(socket, id);
    response_t responsePosAxisX = this->sendInteger(socket, position.axis_x);
    response_t responsePosAxisY = this->sendInteger(socket, position.axis_y);
    response_t responseOrientation = this->sendOrientation(socket, position.orientation);

    if(!responseId.ok || !responsePosAxisX.ok || !responsePosAxisY.ok || !responseOrientation.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en MapElementUpdate.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessagePlayerDisconnect(Socket *socket, Message *message){
    size_t id = ((MessagePlayerDisconnect *) message)->getId();

    response_t responseId = this->sendLongInteger(socket, id);

    if(!responseId.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en PlayerDisconnect.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessagePlayerReconnect(Socket *socket, Message *message){
    size_t id = ((MessagePlayerReconnect *) message)->getId();

    response_t responseId = this->sendLongInteger(socket, id);

    if(!responseId.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en PlayerDisconnect.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageRequestLoginPlayer(Socket *socket, Message *message){
    
    response_t responseUser = this->sendString(socket, ((MessageRequestLoginPlayer *) message)->getUserName());
    response_t responsePassword = this->sendString(socket, ((MessageRequestLoginPlayer *) message)->getPassword());

    if(!responseUser.ok || !responsePassword.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en RequestLogin.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageResponseLoginPlayer(Socket *socket, Message *message){
    Logger::getInstance()->log(DEBUG, "Se va a enviar un mensaje responseLogin.");    
    
    responseStatus_t userResponseStatus = ((MessageResponseLoginPlayer *) message)->getResponse();

    response_t responseStatus = this->sendResponseType(socket, userResponseStatus);

    if(!responseStatus.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en ResponseLogin.");
        return this->_handleErrorStatus();
    }
    Logger::getInstance()->log(DEBUG, "Se pudo enviar un mensaje responseLogin.");
    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageUserMovement(Socket *socket, Message *message){
    orientation_t orientation = ((MessageUserMovement *) message)->getOrientation();

    response_t responseOrientation = this->sendOrientation(socket, orientation);

    if(!responseOrientation.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en UserMovement.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendResponseType(Socket *socket, responseStatus_t value){
    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje response.");

    s << value;

    if (socket->sendMessage(s, sizeof(responseStatus_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el mensaje de integer.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendOrientation(Socket *socket, orientation_t &orientation){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje entero long.");

    s << orientation << endl;

    if (socket->sendMessage(s, sizeof(orientation)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el mensaje de integer.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendInteger(Socket *socket, int &value){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje entero long.");

    s << value << endl;

    if (socket->sendMessage(s, sizeof(int)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el mensaje de integer.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendLongInteger(Socket *socket, size_t &value){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje entero long.");

    s << value << endl;

    if (socket->sendMessage(s, sizeof(size_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el mensaje de integer.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageType(Socket *socket, message_t type){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje");

    s << type;

    cout << "El tipo " << type << endl;

    if (socket->sendMessage(s, sizeof(message_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el mensaje.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendUInt(Socket *socket, unsigned int size){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje");

    cout << "El valor que se va a pasar " << size << endl;

    s << size;

    if (socket->sendMessage(s, sizeof(unsigned int)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el mensaje.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendString(Socket *socket, char (path)[100]){

    stringstream s;

    std::string str = std::string(path);

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje string.");

    s << str;

    if (socket->sendMessage(s, sizeof(char) * 100) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el mensaje de integer.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendSerializedEvent(Socket *socket, Message *message){
    message_t type = message->getType();

    Logger::getInstance()->log(DEBUG, "Se va a enviar un mensaje en Serializer");

    response_t response = this->sendMessageType(socket, type);

    if(!response.ok){
        cout << "No se pudo enviar el tipo" << endl;
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el tipo de mensaje");
    }

    switch (type){
        case ANIMATION_INIT_STAGE:
            return this->sendMessageAnimationInitStage(socket, message);

        case END_GAME:
            return this->sendMessageEndGame(socket, message);

        case END_STAGE:
            return this->sendMessageEndStage(socket, message);

        case GAME_INIT:
            return this->sendMessageGameInit(socket, message);

        case INIT_STAGE:
            return this->sendMessageInitStage(socket, message);

        case LOG:
            return this->sendMessageLog(socket, message);

        case MAP_ELEMENT_CREATE:
            return this->sendMessageMapElementCreate(socket, message);

        case MAP_ELEMENT_DELETE:
            return this->sendMessageMapElementDelete(socket, message);

        case MAP_ELEMENT_UPDATE:
            return this->sendMessageMapElementUpdate(socket, message);
    
        case PLAYER_DISCONNECT:
            return this->sendMessagePlayerDisconnect(socket, message);

        case PLAYER_RECONNECT:
            return this->sendMessagePlayerReconnect(socket, message);

        case REQUEST_LOGIN_PLAYER:
            return this->sendMessageRequestLoginPlayer(socket, message);

        case RESPONSE_LOGIN_PLAYER:
            return this->sendMessageResponseLoginPlayer(socket, message);

        case USER_MOVEMENT:
            return this->sendMessageUserMovement(socket, message);
    }

    Logger::getInstance()->log(ERROR, "No se ha recibido un tipo de mensaje conocido.");


    return this->_handleSuccess();
}