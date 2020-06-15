#include "MessageDeserializer.h"

MessageDeserializer::MessageDeserializer(){};

MessageActionPlayer *MessageDeserializer::receiveActionPlayer(Socket *receives, bool &error){
    return nullptr;
};

MessageInitEntity *MessageDeserializer::receiveInitEntity(Socket *receives, bool &error){
    return nullptr;
};

MessageInitLayer *MessageDeserializer::receiveInitLayer(Socket *receives, bool &error){
    
    char level;
    if (receives->recibirMensaje(&level, sizeof(char)) <= 0){
        error = true;
        return nullptr;
    }
        
    char stage;
    if (receives->recibirMensaje(&stage, sizeof(char)) <= 0){
        error = true;
        return nullptr;
    }
    
    char id;
    if (receives->recibirMensaje(&id, sizeof(char)) <= 0){
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
    
    MessageInitLayer *message = new MessageInitLayer((level_t)level, (stage_t)stage, (size_t)id, source);

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

MessageMovementPlayer *MessageDeserializer::receiveMovementPlayer(Socket *receives, bool &error){
    return nullptr;
};

MessageUpdateEntity *MessageDeserializer::receiveUpdateEntity(Socket *receives, bool &error){
    return nullptr;
};

MessageUpdateStage *MessageDeserializer::receiveUpdateStage(Socket *receives, bool &error){
    return nullptr;
};

Message *MessageDeserializer::getReceivedMessage(Socket *receives, bool &error){
    
    char typeMessage = NONE;

    if (error)
        return new NoneMessage();
    
    if (receives->recibirMensaje(&typeMessage, sizeof(char)) <= 0)
        error = true;

    switch (typeMessage){

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

void MessageDeserializer::pushNewMessage(Socket *receives, bool &error, vector<Message *> *queueMessage){
    char typeMessage = NONE;

    if (error)
        return;
    
    if (receives->recibirMensaje(&typeMessage, sizeof(char)) <= 0)
        error = true;

    switch (typeMessage){

        case INIT_ENTITY:
            queueMessage->push_back(this->receiveInitEntity(receives, error));
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

        case MOVEMENT_PLAYER:
            queueMessage->push_back(this->receiveMovementPlayer(receives, error));
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
