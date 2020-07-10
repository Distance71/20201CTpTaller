#include "EventAnimationInitStage.h"

Message* EventAnimationInitStage::serialize() {
    return (Message *) new MessageAnimationInitStage(this->path_);
}

void EventAnimationInitStage::update(){
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento AnimationInitStage");
    }
    else{
      Client * client = (Client*) Event::context_;
      client ->setImage(this->path_);
      Logger::getInstance()->log(DEBUG, "Se ejecutó el evento AnimationInitStage");
    }
}