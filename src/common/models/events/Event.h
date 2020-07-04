#ifndef EVENT_H_
#define EVENT_H_

#include <stdio.h>
#include "../messages/Message.h"

using namespace std;

class Message;

class Event {

	protected:
        void* context_ = nullptr;
    public:
        void setContext(void* context) {this->context_ = context;};

        virtual Message* serialize() = 0;
        virtual void update() = 0;
};

#endif