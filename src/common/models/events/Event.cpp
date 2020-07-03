#include "Event.h"

Event::Event(){
    client = NULL;
    server = NULL;
}

void Event::setClientContext(Client* client_){
    client = client_;
}

void Event::setServerContext(Server* server_){
    server = server_;
}


Message* Event:: serialize(){

}

void Event::update(){

}