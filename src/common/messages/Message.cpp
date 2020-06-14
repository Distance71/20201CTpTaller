#include "Message.h"

Message::Message(typeMessage_t type){
    this->type_ = type;
}

Message::~Message(){
}

string Message::getStringData(){
    string dataString;

    dataString.push_back(this->type_);

    return dataString;
}

typeMessage_t Message::getType(){
    return this->type_;
}

NoneMessage::NoneMessage() : Message(NONE){

}

NoneMessage::~NoneMessage(){

}

string NoneMessage::getStringData(){
    string dataString;

    dataString.push_back(this->type_);

    return dataString;
}