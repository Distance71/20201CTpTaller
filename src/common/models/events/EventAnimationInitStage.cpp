#include "EventAnimationInitStage.h"

Message* EventAnimationInitStage::serialize() {
    return (Message *) new MessageAnimationInitStage(this->scene_);
}

void EventAnimationInitStage::update(){
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento AnimationInitStage");
    }
    else{
      Client * client = (Client*) Event::context_;
      client ->setImage(this->scene_);
      Logger::getInstance()->log(DEBUG, "Se ejecutó el evento AnimationInitStage");
    }
}