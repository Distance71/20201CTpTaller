#include "EventSetLevel.h"

Message* EventSetLevel::serialize() {
    return (Message *) new MessageSetLevel(this->level_);
}

void EventSetLevel::update(){
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento SetLevel");
    }
    else{
      Client * client = (Client*) Event::context_;
    //   client ->setImage(this->scene_);
      Logger::getInstance()->log(DEBUG, "Se ejecutó el evento SetLevel");
    }
}