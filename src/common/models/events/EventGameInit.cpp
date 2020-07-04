#include "EventGameInit.h"

EventGameInit::EventGameInit(size_t width, size_t height){
    this->width_ = width;
    this->height_ = height;
    this->context_ = nullptr; 
}

Message* EventGameInit::serialize() {
    return (Message *) new MessageGameInit(this->width_, this->height_);
}

void EventGameInit::update() {
    if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

    GameProvider::setWidth(this->width_);
    GameProvider::setHeight(this->height_);
}