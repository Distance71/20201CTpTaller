#include "MessageLoginPlayer.h"

MessageLoginPlayer::MessageLoginPlayer(string username, string password) : Message(LOGIN_PLAYER){
    this->username_ = username;
    this->password_ = password;
}

MessageLoginPlayer::~MessageLoginPlayer(){}


//Server
string MessageLoginPlayer::getStringData(){

    string dataString;
    
    dataString.push_back(this->type_);

    int lenUsername = this->username_.length();
    char* lenUsername_arr = (char*)&lenUsername;
    for (size_t i = 0; i < sizeof(int); ++i)
        dataString.push_back(lenUsername_arr[i]);

    dataString.append(this->username_);

    int lenPassword = this->password_.length();
    char* lenPassword_arr = (char*)&lenPassword;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        dataString.push_back(lenPassword_arr[i]);

    dataString.append(this->password_);
        
    return dataString;
};

string MessageLoginPlayer::getUsername(){
    return this->username_;
};

string MessageLoginPlayer::getPassword(){
    return this->password_;
};

//Client
// void MesssageLoginPlayer::setStringData(){
    
// };