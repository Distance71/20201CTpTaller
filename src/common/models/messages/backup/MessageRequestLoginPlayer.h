#ifndef _MESSAGE_REQUEST_PLAYER_H_
#define _MESSAGE_REQUEST_PLAYER_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../../types.h"

using namespace std;

class MessageRequestLoginPlayer : public Message {

    private:
        bool authorize_;

    public:
        MessageRequestLoginPlayer(bool authorize);
        ~MessageRequestLoginPlayer();
        string getStringData();

        bool getAuthorize();

};

#endif // _MESSAGE_REQUEST_PLAYER_H_