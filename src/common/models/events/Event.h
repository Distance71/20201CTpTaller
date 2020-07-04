#pragma once
#ifndef EVENT_H
#define EVENT_H

#include "../messages/Message.h"

class Message;

class Event {

	protected:
        void* context_;

    public:
        void setContext(void* context) {this->context_ = context;};

        virtual Message* serialize();
        virtual void update();
};

#endif