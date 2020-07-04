#include "EventResponseLoginPlayer.h"

EventResponseLoginPlayer::EventResponseLoginPlayer(login_answer _answer){
    answer = _answer;
}

void EventResponseLoginPlayer::update(){
    if(client){
        Menu* menu = client-> getGameScreen()-> getMenu();
        if(menu){
            menu->setCredentialsResponse(answer);
        }
    }
}
