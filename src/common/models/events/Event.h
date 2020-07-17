#ifndef EVENT_H_
#define EVENT_H_

#include <stdio.h>
#include "../../types.h"
#include "../messages/Message.h"
#include "../../services/Logger.h"

using namespace std;

class Message;

class Event {

	protected:
        void* context_ = nullptr;
        Id own_;
    
    public:
        void setContext(void* context) {this->context_ = context;};
        void setOwn(Id eventOwn) { this->own_ = eventOwn;}
        virtual Message* serialize() = 0;
        virtual void update() = 0;
        Id getOwn(){return this->own_;};
};

#endif