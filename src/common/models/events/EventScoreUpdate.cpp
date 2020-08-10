#include "EventScoreUpdate.h"

Message* EventScoreUpdate::serialize() {
    return (Message *) new MessageScoreUpdate(this->typePlayer_, this->lives_, this->health_, this->scoreCurrent_, this->scoreAcc_);
}

void EventScoreUpdate::update(){
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento ScoreUpdate");
    }
    else{
      Client * client = (Client*) Event::context_;
      client->updateScore(this->typePlayer_,this->lives_,this->health_, this->scoreCurrent_,this->scoreAcc_);
      Logger::getInstance()->log(DEBUG, "Se ejecutó el evento ScoreUpdate");
    }
}