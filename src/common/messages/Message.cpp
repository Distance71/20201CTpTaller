#include "Message.h"

Message::Message(typeMessage_t type){
    this->type_ = type;
}

NoneMessage::NoneMessage() : Message(NONE){}

string NoneMessage::getStringData(){
    string dataString;

    dataString.push_back(this->type_);

    return dataString;
}