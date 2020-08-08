#include "EventScoreUpdate.h"

Message* EventScoreUpdate::serialize() {
    return (Message *) new MessageScoreUpdate(this->positionPlayer_, this->lives_, this->health_, this->score_);
}

void EventScoreUpdate::update(){
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento ScoreUpdate");
    }
    else{
      Client * client = (Client*) Event::context_;
      //client ->updateBackgroundLayer(this->lives_, this->health_);
      Logger::getInstance()->log(DEBUG, "Se ejecutó el evento ScoreUpdate");
    }
}