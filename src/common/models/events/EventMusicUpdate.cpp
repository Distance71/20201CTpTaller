#include "EventMusicUpdate.h"
#include "../../../client/Client.h"

Message* EventMusicUpdate::serialize() {
    return (Message *) new MessageMusicUpdate(this->musicType_);
}

void EventMusicUpdate::update() {
  if (!this->context_){
	  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento EventMusicUpdate");
  }
  else{
    cout << "sii" << endl;
    //Client* client = (Client*) Event::context_;
    //client->updateMusic(this->elementType_);
    Logger::getInstance()->log(DEBUG, "Se ejecutó el evento EventMusicUpdate");
  }
}