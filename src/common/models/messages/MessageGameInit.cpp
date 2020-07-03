#include "MessageGameInit.h"

Event* deSerialize(){
    return (Event *) new EventGameInit();
}