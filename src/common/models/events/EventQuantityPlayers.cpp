#include "EventQuantityPlayers.h"

Message* EventQuantityPlayers::serialize() {
    return (Message *) new MessageQuantityPlayers(this->quantityPlayers_);
}

void EventQuantityPlayers::update(){
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento QuantityPlayers");
    }
    else{
      Client * client = (Client*) Event::context_;

      cout << "Cantidad de Jugadores: " << this->quantityPlayers_ << endl;

      Logger::getInstance()->log(DEBUG, "Se ejecutó el evento QuantityPlayers");
    }
}