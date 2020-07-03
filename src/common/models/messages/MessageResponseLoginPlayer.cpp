// #include "MessageResponseLoginPlayer.h"

// MessageResponseLoginPlayer::MessageResponseLoginPlayer(bool authorize) : Message(RESPONSE_LOGIN_PLAYER){
//     this->authorize_ = authorize;
// }

// MessageResponseLoginPlayer::~MessageResponseLoginPlayer(){}

// string MessageResponseLoginPlayer::getStringData(){
//     string dataString;
    
//     dataString.push_back(this->type_);
    
//     if (this->authorize_){
//         dataString.push_back(IS_TRUE);
//     } else {
//         dataString.push_back(IS_FALSE);
//     }
        
//     return dataString;    
// }

// bool MessageResponseLoginPlayer::getAuthorize(){
//     return this->authorize_;
// }
