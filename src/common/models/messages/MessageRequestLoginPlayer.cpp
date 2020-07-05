#include "MessageRequestLoginPlayer.h"

Event* MessageRequestLoginPlayer::deSerialize(){
    return (Event *) new EventRequestLoginPlayer(this->userName_, this->password_);
}