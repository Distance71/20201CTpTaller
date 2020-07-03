// #include "MessageRequestLoginPlayer.h"

// MessageRequestLoginPlayer::MessageRequestLoginPlayer(string username, string password) : Message(LOGIN_PLAYER){
//     this->username_ = username;
//     this->password_ = password;
// }

// MessageRequestLoginPlayer::~MessageRequestLoginPlayer(){}


// //Server
// string MessageRequestLoginPlayer::getStringData(){

//     string dataString;
    
//     dataString.push_back(this->type_);

//     int lenUsername = this->username_.length();
//     char* lenUsername_arr = (char*)&lenUsername;
//     for (size_t i = 0; i < sizeof(int); ++i)
//         dataString.push_back(lenUsername_arr[i]);

//     dataString.append(this->username_);

//     int lenPassword = this->password_.length();
//     char* lenPassword_arr = (char*)&lenPassword;
//     for (unsigned int i = 0; i < sizeof(int); ++i)
//         dataString.push_back(lenPassword_arr[i]);

//     dataString.append(this->password_);
        
//     return dataString;
// };

// string MessageRequestLoginPlayer::getUsername(){
//     return this->username_;
// };

// string MessageRequestLoginPlayer::getPassword(){
//     return this->password_;
// };

// void MessageRequestLoginPlayer ::setStringData(){
// };

// //Client
// // void MesssageLoginPlayer::setStringData(){
    
// // };