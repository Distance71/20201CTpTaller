#include "MessageRequestLoginPlayer.h"

MessageRequestLoginPlayer::MessageRequestLoginPlayer(bool authorize) : Message(REQUEST_LOGIN_PLAYER){
    this->authorize_ = authorize;
}

MessageRequestLoginPlayer::~MessageRequestLoginPlayer(){}

string MessageRequestLoginPlayer::getStringData(){
    string dataString;
    
    dataString.push_back(this->type_);
    
    if (this->authorize_){
        dataString.push_back(IS_TRUE);
    } else {
        dataString.push_back(IS_FALSE);
    }
        
    return dataString;    
}

bool MessageRequestLoginPlayer::getAuthorize(){
    return this->authorize_;
}
