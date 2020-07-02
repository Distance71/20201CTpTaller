#ifndef _MESSAGE_REQUEST_LOGIN_PLAYER_H_
#define _MESSAGE_REQUEST_LOGIN_PLAYER_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../../types.h"

using namespace std;

class MessageRequestLoginPlayer : public Message {

    private:
        string username_;
        string password_;

    public:
        MessageRequestLoginPlayer(string username, string password);
        ~MessageRequestLoginPlayer();
        string getStringData();

        string getUsername();
        string getPassword();
        
        void setStringData();
};

#endif // _MESSAGE_LOGIN_PLAYER_H_