/*#include "EventResponseLoginPlayer.h"

EventResponseLoginPlayer::EventResponseLoginPlayer(loginAnswer_t answer){
    this->answer_ = answer;
    this->context_ = nullptr;
}

void EventResponseLoginPlayer::update(){
    if(this->context_){
        Menu* menu = ((Client *) this->context_)-> getGameScreen()-> getMenu();
        if(menu){
            menu->setCredentialsResponse(answer);
        }
    }
}

Message* EventResponseLoginPlayer::serialize(){
	
}
*/