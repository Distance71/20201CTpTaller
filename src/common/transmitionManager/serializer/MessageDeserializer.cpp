#include "MessageDeserializer.h"

MessageDeserializer::MessageDeserializer(){};

MessageActionPlayer *MessageDeserializer::receiveActionPlayer(Socket *receives, int *fdSend, bool &error){
    return nullptr;
};

MessageInitEntity *MessageDeserializer::receiveInitEntity(Socket *receives, int *fdSend, bool &error){
    return nullptr;
};

MessageInitLayer *MessageDeserializer::receiveInitLayer(Socket *receives, int *fdSend, bool &error){
    
    char level;
    if (receives->recibirMensaje(fdSend, &level, sizeof(char)) <= 0){
        error = true;
        return nullptr;
    }
        
    char stage;
    if (receives->recibirMensaje(fdSend, &stage, sizeof(char)) <= 0){
        error = true;
        return nullptr;
    }
    
    char id;
    if (receives->recibirMensaje(fdSend, &id, sizeof(char)) <= 0){
        error = true;
        return nullptr;
    }
    
    int source_length;
    if (receives->recibirMensaje(fdSend, (char *)&source_length, sizeof(int)) <= 0){
        error = true;
        return nullptr;
    }
    
    char *source = new char[source_length + 1];
    source[source_length] = '\0';
    if (receives->recibirMensaje(fdSend, source,  sizeof(char) * source_length) <= 0){
        error = true;
        return nullptr;
    }
    
    MessageInitLayer *message = new MessageInitLayer((level_t)level, (stage_t)stage, (size_t)id, source);

    delete [] source;
    return message;
};

MessageMovementPlayer *MessageDeserializer::receiveMovementPlayer(Socket *receives, int *fdSend, bool &error){
    return nullptr;
};

MessageUpdateEntity *MessageDeserializer::receiveUpdateEntity(Socket *receives, int *fdSend, bool &error){
    return nullptr;
};

MessageUpdateStage *MessageDeserializer::receiveUpdateStage(Socket *receives, int *fdSend, bool &error){
    return nullptr;
};

Message *MessageDeserializer::getReceivedMessage(Socket *receives, int *fdSend, bool &error){
    
    char typeMessage = NONE;

    if (error)
        return new NoneMessage();
    
    if (receives->recibirMensaje(fdSend, &typeMessage, sizeof(char)) <= 0)
        error = true;

    switch (typeMessage){

        case INIT_ENTITY:
            return this->receiveInitEntity(receives, fdSend, error);

        case UPDATE_ENTITY:
            return this->receiveUpdateEntity(receives, fdSend, error);

        case INIT_LAYER:
            return this->receiveInitLayer(receives, fdSend, error);

        case UPDATE_STAGE:
            return this->receiveUpdateStage(receives, fdSend, error);

        case MOVEMENT_PLAYER:
            return this->receiveMovementPlayer(receives, fdSend, error);

        case ACTION_PLAYER:
            return this->receiveActionPlayer(receives, fdSend, error);

        case NONE:
        default:
            return new NoneMessage();
    }

};