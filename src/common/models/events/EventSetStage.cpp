#include "EventSetStage.h"

Message* EventSetStage::serialize() {
    return (Message *) new MessageSetStage(this->stage_);
}

void EventSetStage::update(){
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento SetStage");
    }
    else{
      Client * client = (Client*) Event::context_;
      client ->setBackground(this->stage_);
      Logger::getInstance()->log(DEBUG, "Se ejecutó el evento SetStage");
    }
}