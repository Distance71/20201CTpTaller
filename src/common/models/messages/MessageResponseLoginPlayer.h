#ifndef _MESSAGE_RESPONSE_PLAYER_H_
#define _MESSAGE_RESPONSE_PLAYER_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../../types.h"

using namespace std;

class MessageResponseLoginPlayer : public Message {

    private:
        bool authorize_;

    public:
        MessageResponseLoginPlayer(bool authorize);
        ~MessageResponseLoginPlayer();
        string getStringData();

        bool getAuthorize();

};

#endif // _MESSAGE_REQUEST_PLAYER_H_