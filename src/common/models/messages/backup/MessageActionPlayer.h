#ifndef MESSAGE_ACTION_PLAYER_H_
#define MESSAGE_ACTION_PLAYER_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../../types.h"

using namespace std;

class MessageActionPlayer : public Message {

    private:
        bool isEnterKey_;
        bool isQuitKey_;

    public:
        MessageActionPlayer(bool isEnter, bool isQuitKey);
        ~MessageActionPlayer();
        string getStringData();
        bool getIsEnterKey();
        bool getIsQuitKey();
};

#endif // MESSAGE_ACTION_PLAYER_H_