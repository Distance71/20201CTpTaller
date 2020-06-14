#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <iostream>
#include <string.h>
#include "../types.h"

#define IS_FALSE 0
#define IS_TRUE 1

using namespace std;

typedef enum typeMessage {
    NONE,
    INIT_ENTITY,
    UPDATE_ENTITY,
    INIT_LAYER,
    INIT_SCREEN,
    UPDATE_STAGE,
    LOGIN_PLAYER,
    REQUEST_LOGIN_PLAYER,
    MOVEMENT_PLAYER,
    ACTION_PLAYER,
} typeMessage_t;

class Message {

    public:
        typeMessage_t type_;

        Message(typeMessage_t type);
        ~Message();
        typeMessage_t getType();
        virtual string getStringData();

};

class NoneMessage : public Message {

    public:
        NoneMessage();
        ~NoneMessage();
        string getStringData();
};

#endif // MESSAGE_H_