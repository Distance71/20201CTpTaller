#ifndef MESSAGE_MOVEMENT_PLAYER_H_
#define MESSAGE_MOVEMENT_PLAYER_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../types.h"

using namespace std;

class MessageMovementPlayer : public Message {

    private:
        orientation_t moveOrientation_;

    public:
        MessageMovementPlayer(orientation_t oneOrientation);

        string getStringData();
};

#endif // MESSAGE_MOVEMENT_PLAYER_H_