#include "MessageResponseLoginPlayer.h"

Event* MessageResponseLoginPlayer::deSerialize(){
    return (Event *) new EventResponseLoginPlayer(this->response_);
}