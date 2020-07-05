#include "MessageEndGame.h"

Event* MessageEndGame::deSerialize(){
    return (Event *) new EventEndGame();
}