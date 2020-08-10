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

response_t MessageSerializer::sendMessageSceneAnimation(Socket *socket, Message *message){
    Logger::getInstance()->log(DEBUG, "Se va a enviar un mensaje SceneAnimation.");
    sceneScreen_t scene = ((MessageSceneAnimation *) message)->getScene();

    response_t responseScene = this->sendSceneScreen(socket, scene);

    if(!responseScene.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en sceneAnimation.");
        return this->_handleErrorStatus();
    }
    Logger::getInstance()->log(DEBUG, "Se envio sceneAnimation con exito.");
    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageEndGame(Socket *socket, Message *message){
    Logger::getInstance()->log(DEBUG, "Se envio EndGame con exito.");
    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageGameInit(Socket *socket, Message *message){
    Logger::getInstance()->log(DEBUG, "Se va a enviar un mensaje GameInit.");
    screen_t screenSizes = ((MessageGameInit *) message)->getScreenSizes();

    response_t responseWidth = this->sendUInt(socket, screenSizes.width);
    response_t responseHeight = this->sendUInt(socket, screenSizes.height);

    if(!responseWidth.ok || !responseHeight.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en GameInit.");
        return this->_handleErrorStatus();
    }
    Logger::getInstance()->log(DEBUG, "Se envio GameInit con exito.");
    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageGameOver(Socket *socket, Message *message){
    Logger::getInstance()->log(DEBUG, "Se envio GameOver con exito.");
    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageLog(Socket *socket, Message *message){
    Logger::getInstance()->log(DEBUG, "Se va a enviar un mensaje Log.");
    size_t level = ((MessageLog *) message)->getLevel();
    response_t responseLevel = this->sendLongInteger(socket, level);
    response_t responseMessage = this->sendString(socket, ((MessageLog *) message)->getMessage());

    if(!responseLevel.ok || !responseMessage.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en Log.");
        return this->_handleErrorStatus();
    }
    Logger::getInstance()->log(DEBUG, "Se envio Log con exito.");
    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageMapElementUpdate(Socket *socket, Message *message){
    Logger::getInstance()->log(DEBUG, "Se va a enviar un mensaje MapElementUpdate.");
    elementType_t elementType = ((MessageMapElementUpdate *) message)->getElementType();
    position_t position = ((MessageMapElementUpdate *) message)->getPosition();

    response_t responseElementType = this->sendElementType(socket, elementType);
    response_t responsePosAxisX = this->sendInteger(socket, position.axis_x);
    response_t responsePosAxisY = this->sendInteger(socket, position.axis_y);
    response_t responseOrientation = this->sendOrientation(socket, position.orientation);

    if(!responseElementType.ok || !responsePosAxisX.ok || !responsePosAxisY.ok || !responseOrientation.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en MapElementUpdate.");
        return this->_handleErrorStatus();
    }
    Logger::getInstance()->log(DEBUG, "Se envio MapElementUpdate con exito.");
    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageRequestLoginPlayer(Socket *socket, Message *message){
    Logger::getInstance()->log(DEBUG, "Se va a enviar un mensaje RequestLoginPlayer.");
    response_t responseUser = this->sendString(socket, ((MessageRequestLoginPlayer *) message)->getUserName());
    response_t responsePassword = this->sendString(socket, ((MessageRequestLoginPlayer *) message)->getPassword());

    if(!responseUser.ok || !responsePassword.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en RequestLogin.");
        return this->_handleErrorStatus();
    }
    Logger::getInstance()->log(DEBUG, "Se envio RequestLoginPlayer con exito.");
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
    Logger::getInstance()->log(DEBUG, "Se envio ResponseLoginPlayer con exito.");
    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageUserMovement(Socket *socket, Message *message){
    Logger::getInstance()->log(DEBUG, "Se va a enviar un mensaje UserMovement.");
    orientation_t orientation = ((MessageUserMovement *) message)->getOrientation();

    response_t responseOrientation = this->sendOrientation(socket, orientation);

    if(!responseOrientation.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en UserMovement.");
        return this->_handleErrorStatus();
    }
    Logger::getInstance()->log(DEBUG, "Se envio UserMovement con exito.");
    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageBackgroundUpdate(Socket *socket, Message *message){
    Logger::getInstance()->log(DEBUG, "Se va a enviar un mensaje BackgroundUpdate.");
    layer_t layer = ((MessageBackgroundUpdate *) message)->getLayer();
    stage_t stage = ((MessageBackgroundUpdate *) message)->getStage();
    int step = ((MessageBackgroundUpdate *) message)->getStep();

    response_t responseLayer = this->sendLayer(socket, layer);
    response_t responseStage = this->sendStage(socket, stage);
    response_t responseStep = this->sendInteger(socket, step);


    if(!responseLayer.ok || !responseStep.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en BackgroundUpdate.");
        return this->_handleErrorStatus();
    }
    Logger::getInstance()->log(DEBUG, "Se envio BackgroundUpdate con exito.");
    return this->_handleSuccess();    
};

response_t MessageSerializer::sendMessageUserShoot(Socket *socket, Message *message){
    Logger::getInstance()->log(DEBUG, "Se envio UserShoot con exito.");
    return this->_handleSuccess(); 
};

response_t MessageSerializer::sendMessageUserChangeMode(Socket *socket, Message *message){
    Logger::getInstance()->log(DEBUG, "Se envio UserChangeMode con exito.");
    return this->_handleSuccess(); 
};

response_t MessageSerializer::sendMessageMusicUpdate(Socket *socket, Message *message){
    Logger::getInstance()->log(DEBUG, "Se va a enviar un mensaje MusicUpdate.");
    musicType_t musicType = ((MessageMusicUpdate *) message)->getMusicType();

    response_t responseMusic = this->sendMusicType(socket, musicType);

    if(!responseMusic.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en musicUpdate.");
        return this->_handleErrorStatus();
    }
    Logger::getInstance()->log(DEBUG, "Se envio musicUpdate con exito.");
    return this->_handleSuccess();
}

response_t MessageSerializer::sendMessageScoreUpdate(Socket *socket, Message *message){

    Logger::getInstance()->log(DEBUG, "Se va a enviar un mensaje ScoreUpdate.");

    elementType_t type = ((MessageScoreUpdate *) message)->getTypePlayer();
    unsigned int lives = ((MessageScoreUpdate *) message)->getLives();
    int health = ((MessageScoreUpdate *) message)->getHealth();
    int score = ((MessageScoreUpdate *) message)->getScore();
    
    
    response_t responseType = this->sendElementType(socket, type);
    response_t responseLives = this->sendUInt(socket, lives);
    response_t responseHealth = this->sendInteger(socket, health);
    response_t responseScore = this->sendInteger(socket, score);


    if(!responseType.ok || !responseLives.ok || !responseHealth.ok || !responseScore.ok) {
        Logger::getInstance()->log(ERROR, "No se ha podido enviar un parametro en ScoreUpdate.");
        return this->_handleErrorStatus();
    }
    Logger::getInstance()->log(DEBUG, "Se envio ScoreUpdate con exito.");
    return this->_handleSuccess();  
}

response_t MessageSerializer::sendResponseType(Socket *socket, responseStatus_t value){
    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje responseType.");

    s << value;

    if (socket->sendMessage(s, sizeof(responseStatus_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el mensaje de integer.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendMusicType(Socket *socket, musicType_t &type){
    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje musicType.");

    s << type;

    if (socket->sendMessage(s, sizeof(musicType_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el mensaje de musicType.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendElementType(Socket *socket, elementType_t elementType){
    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje elementType.");

    s << elementType;

    if (socket->sendMessage(s, sizeof(elementType_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el mensaje de elementType.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendSceneScreen(Socket *socket, sceneScreen_t scene){
    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje sceneScreen.");

    s << scene;

    if (socket->sendMessage(s, sizeof(sceneScreen_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el mensaje de sceneScreen.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendOrientation(Socket *socket, orientation_t &orientation){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje orientation.");

    s << orientation << endl;

    if (socket->sendMessage(s, sizeof(orientation)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el mensaje de integer.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendStage(Socket *socket, stage_t &stage){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje Stage.");

    s << stage << endl;

    if (socket->sendMessage(s, sizeof(stage_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el mensaje de stage.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();    
};

response_t MessageSerializer::sendLayer(Socket *socket, layer_t &layer){
    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje layer.");

    s << layer << endl;

    if (socket->sendMessage(s, sizeof(layer_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el mensaje de layer.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();  
}

response_t MessageSerializer::sendInteger(Socket *socket, int &value){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje entero.");

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

    if (socket->sendMessage(s, sizeof(message_t)) <= 0){
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el mensaje.");
        return this->_handleErrorStatus();
    }

    return this->_handleSuccess();
}

response_t MessageSerializer::sendUInt(Socket *socket, unsigned int size){

    stringstream s;

    Logger::getInstance()->log(DEBUG, "Se va a enviar un tipo de mensaje unsigned entero");

    //cout << "El valor que se va a pasar " << size << endl;

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
        Logger::getInstance()->log(ERROR, "Se ha producido un error al enviar el tipo de mensaje");
    }

    switch (type){
        case SCENE_ANIMATION:
            return this->sendMessageSceneAnimation(socket, message);

        case END_GAME:
            return this->sendMessageEndGame(socket, message);

        case GAME_INIT:
            return this->sendMessageGameInit(socket, message);

        case LOG:
            return this->sendMessageLog(socket, message);

        case MAP_ELEMENT_UPDATE:
            return this->sendMessageMapElementUpdate(socket, message);
    
        case REQUEST_LOGIN_PLAYER:
            return this->sendMessageRequestLoginPlayer(socket, message);

        case RESPONSE_LOGIN_PLAYER:
            return this->sendMessageResponseLoginPlayer(socket, message);

        case USER_MOVEMENT:
            return this->sendMessageUserMovement(socket, message);
        
        case BACKGROUND_UPDATE:
            return this->sendMessageBackgroundUpdate(socket, message);
        
        case USER_SHOOT:
            return this->sendMessageUserShoot(socket, message);

        case USER_CHANGE_MODE:
            return this->sendMessageUserChangeMode(socket, message);

        case MUSIC_UPDATE:
            return this->sendMessageMusicUpdate(socket, message);

        case SCORE_UPDATE:
            return this->sendMessageScoreUpdate(socket, message);

        case GAME_OVER:
            return this->sendMessageGameOver(socket, message);
    }

    Logger::getInstance()->log(ERROR, "No se ha recibido un tipo de mensaje conocido.");


    return this->_handleSuccess();
}