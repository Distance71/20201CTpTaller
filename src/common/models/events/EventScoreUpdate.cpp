#include "EventScoreUpdate.h"

Message* EventScoreUpdate::serialize() {
    return (Message *) new MessageScoreUpdate(this->typePlayer_, this->lives_, this->health_, this->score_);
}

void EventScoreUpdate::update(){
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento ScoreUpdate");
    }
    else{
      Client * client = (Client*) Event::context_;
      std::cout << "PLAYER " << this->typePlayer_ << " - LIVES: " << this->lives_ << " - HEALTH: " << this->health_ << " - SCORE: " << this->score_ << std::endl;
      
      //client ->updateBackgroundLayer(this->lives_, this->health_);
      Logger::getInstance()->log(DEBUG, "Se ejecutó el evento ScoreUpdate");
    }
}