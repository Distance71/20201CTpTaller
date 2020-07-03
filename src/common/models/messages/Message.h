#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <iostream>
#include <string.h>
#include "../../types.h"

#define IS_FALSE 0
#define IS_TRUE 1

using namespace std;

class Message {

    public:
        message_t type_;

        Message(message_t type);
        ~Message();
        message_t getType();
        virtual string getStringData();
        virtual void setStringData();

        //virtual Event* deSerialize(); //Whould be great to add this
};

 class NoneMessage : public Message {

     public:
         NoneMessage();
         ~NoneMessage();
         string getStringData();
 };

#endif // MESSAGE_H_