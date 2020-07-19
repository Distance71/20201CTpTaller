#include "EventBackgroundUpdate.h"

Message* EventBackgroundUpdate::serialize() {
    return (Message *) new MessageBackgroundUpdate(this->layer_, this->stage_, this->step_);
}

void EventBackgroundUpdate::update(){
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento BackgroundLayer");
    }
    else{
      Client * client = (Client*) Event::context_;
      client ->updateBackgroundLayer(this->layer_, this->stage_, this->step_);
      Logger::getInstance()->log(DEBUG, "Se ejecutó el evento BackgroundLayer");
    }
}