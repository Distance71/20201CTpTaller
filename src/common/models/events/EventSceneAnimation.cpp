#include "EventSceneAnimation.h"

Message* EventSceneAnimation::serialize() {
    return (Message *) new MessageSceneAnimation(this->scene_);
}

void EventSceneAnimation::update(){
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento SceneAnimation");
    }
    else{
      Client * client = (Client*) Event::context_;
      client ->setImage(this->scene_);
      Logger::getInstance()->log(DEBUG, "Se ejecutó el evento SceneAnimation");
    }
}