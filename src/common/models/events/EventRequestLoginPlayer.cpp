#include "EventRequestLoginPlayer.h"

Message* EventRequestLoginPlayer::serialize() {
    return (Message *) new MessageRequestLoginPlayer(this->userName_, this->password_);
}

void EventRequestLoginPlayer::update() {
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay conexto para el evento EventRequestLoginPlayer");
    }
    
    else{
      Server* server = (Server*) Event::context_;
      
      bool res = GameProvider::isValidCredential(this->userName_,this->password_);
      EventResponseLoginPlayer* event = NULL;
      
      if (res == false){
        Logger::getInstance()->log(INFO, "Se intentó loguear un usuario con credenciales erroneas");
        event = new EventResponseLoginPlayer(ERROR_WRONG_CREDENTIALS);
        server->setLoginResponse(this->own_,false,this->userName_);
      }
      
      else {  
        
        if (server->isFullGame()){  
          if (server->wasPreviouslyLogged(this->userName_)){
            Logger::getInstance()->log(INFO, "Se intentó loguear un usuario que ya se habia logueado previamente");
            if (!server->isLoggedIn(this->userName_)){
              Logger::getInstance()->log(INFO, "Se reconecta un usuario");
              event = new EventResponseLoginPlayer(OK);
              server->setLoginResponse(this->own_,true,this->userName_);
            }
            else{
              event = new EventResponseLoginPlayer(ALREADY_LOGGED_IN_ERROR);
              server->setLoginResponse(this->own_,false,this->userName_);
            }
          }
          else{
           event = new EventResponseLoginPlayer(ERROR_FULL_GAME);
           server->setLoginResponse(this->own_,false,this->userName_);
          }
        }
      
        else if (server->isLoggedIn(this->userName_)){
          Logger::getInstance()->log(INFO, "Se intentó loguear un usuario que ya se habia logueado previamente");
          event =  new EventResponseLoginPlayer(ALREADY_LOGGED_IN_ERROR);
          server->setLoginResponse(this->own_,false,this->userName_);
        }
        
        else{
          Logger::getInstance()->log(INFO, "Se loguea un usuario nuevo con éxito");
          event = new EventResponseLoginPlayer(OK);
          server->setLoginResponse(this->own_,true,this->userName_);
        }
      
      }
      
      server->sendToUser(this->own_,event);
      Logger::getInstance()->log(DEBUG, "Se ejecutó el evento EventRequestLoginPlayer");
    
    } 
}