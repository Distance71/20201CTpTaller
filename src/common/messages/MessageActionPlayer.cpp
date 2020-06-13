#include "MessageActionPlayer.h"

MessageActionPlayer::MessageActionPlayer(bool isEnter, bool isQuit) : Message(ACTION_PLAYER){
    this->isEnterKey_ = isEnter;
    this->isQuitKey_ = isQuitKey_;
}

string MessageActionPlayer::getStringData(){
    string dataString;
    
    dataString.push_back(this->type_);
    
    if (this->isEnterKey_){
        dataString.push_back(IS_TRUE);
    } else {
        dataString.push_back(IS_FALSE);
    }
    
    if (this->isQuitKey_){
        dataString.push_back(IS_TRUE);
    } else {
        dataString.push_back(IS_FALSE);
    }
        
    return dataString;    
}