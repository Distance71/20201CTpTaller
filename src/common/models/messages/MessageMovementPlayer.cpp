#include "MessageMovementPlayer.h"

MessageMovementPlayer::MessageMovementPlayer(orientation_t oneOrientation) : Message(MOVEMENT_PLAYER){
    this->moveOrientation_ = oneOrientation;
}

MessageMovementPlayer::~MessageMovementPlayer(){};

string MessageMovementPlayer::getStringData(){
    string dataString;
    
    dataString.push_back(this->type_);
    dataString.push_back(this->moveOrientation_);
        
    return dataString;
}

orientation_t MessageMovementPlayer::getOrientation(){
    return this->moveOrientation_;
};