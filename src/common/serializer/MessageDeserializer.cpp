#include "MessageDeserializer.h"

MessageDeserializer::MessageDeserializer(){};

MessageActionPlayer *MessageDeserializer::receiveActionPlayer(Socket *receives, bool &error){

    char enterKey;
    if (receives->recibirMensaje(&enterKey, sizeof(char)) <= 0){
        error = true;
        return nullptr;
    }

    char quitKey;
    if (receives->recibirMensaje(&quitKey, sizeof(char)) <= 0){
        error = true;
        return nullptr;
    }

    return new MessageActionPlayer(enterKey, quitKey);   
};

MessageInitEntity *MessageDeserializer::receiveInitEntity(Socket *receives, bool &error){

    unsigned int step;
    if (receives->recibirMensaje((char *)&step, sizeof(unsigned int)) <= 0){
        error = true;
        return nullptr;
    }
        
    IdElement id;
    if (receives->recibirMensaje((char *) &id, sizeof(IdElement)) <= 0){
        error = true;
        return nullptr;
    }
    
    int sizeX;
    if (receives->recibirMensaje((char *)&sizeX, sizeof(int)) <= 0){
        error = true;
        return nullptr;
    }
    
    int sizeY;
    if (receives->recibirMensaje((char *)&sizeY, sizeof(int)) <= 0){
        error = true;
        return nullptr;
    }
    
    int posX;
    if (receives->recibirMensaje((char *)&posX, sizeof(int)) <= 0){
        error = true;
        return nullptr;
    }
    
    int posY;
    if (receives->recibirMensaje((char *)&posY, sizeof(int)) <= 0){
        error = true;
        return nullptr;
    }
    
    int source_length;
    if (receives->recibirMensaje((char *)&source_length, sizeof(int)) <= 0){
        error = true;
        return nullptr;
    }
    
    char *source = new char[source_length + 1];
    source[source_length] = '\0';
    if (receives->recibirMensaje(source,  sizeof(char) * source_length) <= 0){
        error = true;
        return nullptr;
    }
    
    char isPlayer;
    if (receives->recibirMensaje(&isPlayer, sizeof(char)) <= 0){
        error = true;
        return nullptr;
    }

    MessageInitEntity *message = new MessageInitEntity(step, id, sizeX, sizeY, posX, posY, source, isPlayer);

    delete [] source;
    return message;    
};

MessageInitLayer *MessageDeserializer::receiveInitLayer(Socket *receives, bool &error){
    
    size_t id;
    if (receives->recibirMensaje((char *)&id, sizeof(size_t)) <= 0){
        error = true;
        return nullptr;
    }
    
    int source_length;
    if (receives->recibirMensaje((char *)&source_length, sizeof(int)) <= 0){
        error = true;
        return nullptr;
    }
    
    char *source = new char[source_length + 1];
    source[source_length] = '\0';
    if (receives->recibirMensaje(source,  sizeof(char) * source_length) <= 0){
        error = true;
        return nullptr;
    }
    
    MessageInitLayer *message = new MessageInitLayer(id, source);

    delete [] source;
    return message;
};

MessageInitScreen *MessageDeserializer::receiveInitScreen(Socket *receives, bool &error){

    unsigned int width;
    if (receives->recibirMensaje((char *) &width, sizeof(unsigned int)) <= 0){
        error = true;
        return nullptr;
    }
        
    unsigned int height;
    if (receives->recibirMensaje((char *) &height, sizeof(unsigned int)) <= 0){
        error = true;
        return nullptr;
    }
    
    return new MessageInitScreen(width, height);
};

MessageLoginPlayer *MessageDeserializer::receiveLoginPlayer(Socket *receives, bool &error){
    
    int name_length;
    if (receives->recibirMensaje((char *)&name_length, sizeof(int)) <= 0){
        error = true;
        return nullptr;
    }
    
    char *username = new char[name_length + 1];
    username[name_length] = '\0';
    if (receives->recibirMensaje(username,  sizeof(char) * name_length) <= 0){
        error = true;
        return nullptr;
    }

    int password_length;
    if (receives->recibirMensaje((char *)&password_length, sizeof(int)) <= 0){
        error = true;
        return nullptr;
    }
    
    char *password = new char[password_length + 1];
    password[password_length] = '\0';
    if (receives->recibirMensaje(password,  sizeof(char) * password_length) <= 0){
        error = true;
        return nullptr;
    }
    
    MessageLoginPlayer *message = new MessageLoginPlayer(username, password);

    delete [] username;
    delete [] password;
    return message;    
};

MessageMovementPlayer *MessageDeserializer::receiveMovementPlayer(Socket *receives, bool &error){

    orientation_t moveOrientation;
    if (receives->recibirMensaje((char *) &moveOrientation, sizeof(orientation_t)) <= 0){
        error = true;
        return nullptr;
    }

    return new MessageMovementPlayer(moveOrientation);
};
        
MessageRequestLoginPlayer *MessageDeserializer::receiveRequestLoginPlayer(Socket *receives, bool &error){

    char authorize;
    if (receives->recibirMensaje(&authorize, sizeof(char)) <= 0){
        error = true;
        return nullptr;
    }

    return new MessageRequestLoginPlayer(authorize);
};

MessageUpdateEntity *MessageDeserializer::receiveUpdateEntity(Socket *receives, bool &error){
            
    unsigned int step;
    if (receives->recibirMensaje((char *)&step, sizeof(unsigned int)) <= 0){
        error = true;
        return nullptr;
    }

    IdElement id;
    if (receives->recibirMensaje((char *) &id, sizeof(IdElement)) <= 0){
        error = true;
        return nullptr;
    }
    
    int posX;
    if (receives->recibirMensaje((char *)&posX, sizeof(int)) <= 0){
        error = true;
        return nullptr;
    }
    
    int posY;
    if (receives->recibirMensaje((char *)&posY, sizeof(int)) <= 0){
        error = true;
        return nullptr;
    }
    
    MessageUpdateEntity *message = new MessageUpdateEntity(step, id, posX, posY);

    return message; 
};

MessageUpdateStage *MessageDeserializer::receiveUpdateStage(Socket *receives, bool &error){

    char level;
    if (receives->recibirMensaje(&level, sizeof(char)) <= 0){
        error = true;
        return nullptr;
    }
    
    char isStart;
    if (receives->recibirMensaje(&isStart, sizeof(char)) <= 0){
        error = true;
        return nullptr;
    }

    char isEnd;
    if (receives->recibirMensaje(&isEnd, sizeof(char)) <= 0){
        error = true;
        return nullptr;
    }

    MessageUpdateStage *message = new MessageUpdateStage((level_t) level, isStart, isEnd);

    return message;        
};

Message *MessageDeserializer::getReceivedMessage(Message *messageReceived, bool &error){
    
    char typeMessage = NONE;

    //Necesidad de usar error?
    // if (error)
    //     return new NoneMessage();
    
    // if (receives->recibirMensaje(&typeMessage, sizeof(char)) <= 0)
    //     error = true;

    switch (messageReceived->getType()){

        case INIT_ENTITY:
            return this->receiveInitEntity(receives, error);

        case UPDATE_ENTITY:
            return this->receiveUpdateEntity(receives, error);

        case INIT_LAYER:
            return this->receiveInitLayer(receives, error);

        case INIT_SCREEN:
            return this->receiveInitScreen(receives, error);

        case UPDATE_STAGE:
            return this->receiveUpdateStage(receives, error);

        case MOVEMENT_PLAYER:
            return this->receiveMovementPlayer(receives, error);

        case ACTION_PLAYER:
            return this->receiveActionPlayer(receives, error);

        case NONE:
        default:
            return new NoneMessage();
    }

};

void MessageDeserializer::pushNewMessage(Socket *receives, bool &error, EventsQueue *queueMessages){
    char typeMessage = NONE;

    if (error)
        return;
    
    if (receives->recibirMensaje(&typeMessage, sizeof(char)) <= 0)
        error = true;

    switch (typeMessage){

        case INIT_ENTITY:
            queueMessages->push(this->receiveInitEntity(receives, error));
            break;

        case UPDATE_ENTITY:
            queueMessage->push_back(this->receiveUpdateEntity(receives, error));
            break;

        case INIT_LAYER:
            queueMessage->push_back(this->receiveInitLayer(receives, error));
            break;

        case INIT_SCREEN:
            queueMessage->push_back(this->receiveInitScreen(receives, error));
            break;

        case UPDATE_STAGE:
            queueMessage->push_back(this->receiveUpdateStage(receives, error));
            break;

        case LOGIN_PLAYER:
            queueMessage->push_back(this->receiveLoginPlayer(receives, error));
            break;

        case MOVEMENT_PLAYER:
            queueMessage->push_back(this->receiveMovementPlayer(receives, error));
            break;

        case REQUEST_LOGIN_PLAYER:
            queueMessage->push_back(this->receiveRequestLoginPlayer(receives, error));
            break;

        case ACTION_PLAYER:
            queueMessage->push_back(this->receiveActionPlayer(receives, error));
            break;

        case NONE:
        default:
            queueMessage->push_back(new NoneMessage());
            break;
    }    
};
