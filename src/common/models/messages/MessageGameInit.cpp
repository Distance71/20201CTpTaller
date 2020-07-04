#include "MessageGameInit.h"

MessageGameInit::MessageGameInit(size_t width, size_t height){
	this->height_ = height;
	this->width_ = width;
}

Event* MessageGameInit::deSerialize(){
    return (Event *) new EventGameInit(this->width_, this->height_);
}