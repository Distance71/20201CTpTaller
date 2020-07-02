#include "MessageSerializer.h"

void MessageSerializer::sendSerializedEvent(User *user, Event *event){
    
    auto socket = user->getSocket();

    Message *message = event->serialize();

    //Check here type of whatever

    if (socket->sendMessage((char *) message, sizeof(message)) <= 0) //HAVE TO SEE THIS EXPRESSION AGAIN
        Logger::getInstance()->log(ERROR, "No se ha podido enviar el mensaje al usuario"); //.append(user->getId())
}