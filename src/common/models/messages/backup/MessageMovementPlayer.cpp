#include "MessageMovementPlayer.h"

MessageMovementPlayer::MessageMovementPlayer(orientation_t oneOrientation) : Message(MOVEMENT_PLAYER){
    this->moveOrientation_ = oneOrientation;
}

MessageMovementPlayer::~MessageMovementPlayer(){};

string MessageMovementPlayer::getStringData(){
    string dataString;
    
    dataString.push_back(this->type_);

    char* orientation_arr = (char*)&this->moveOrientation_;
    for (unsigned int i = 0; i < sizeof(orientation_t); ++i)
        dataString.push_back(orientation_arr[i]);
        
    return dataString;
}

orientation_t MessageMovementPlayer::getOrientation(){
    return this->moveOrientation_;
};