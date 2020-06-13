#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <iostream>
#include <string.h>

#define IS_FALSE 0
#define IS_TRUE 1

using namespace std;

typedef enum typeMessage {
    NONE,
    INIT_ENTITY,
    UPDATE_ENTITY,
    INIT_LAYER,
    UPDATE_STAGE,
    MOVEMENT_PLAYER,
    ACTION_PLAYER,
} typeMessage_t;

class Message {

    public:
        typeMessage_t type_;

        Message(typeMessage_t type);
        virtual string getStringData();

};

class NoneMessage : public Message {

    public:
        NoneMessage();
        string getStringData();
};

#endif // MESSAGE_H_