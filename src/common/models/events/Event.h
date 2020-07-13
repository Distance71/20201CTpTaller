#ifndef EVENT_H_
#define EVENT_H_

#include <stdio.h>
#include "../messages/Message.h"
#include "../../services/Logger.h"

using namespace std;

class Message;

class Event {

	protected:
        void* context_ = nullptr;
        string own_ = "";
    public:
        void setContext(void* context) {this->context_ = context;};
        void setOwn(string eventOwn) { this->own_ = eventOwn;}
        virtual Message* serialize() = 0;
        virtual void update() = 0;
};

#endif