#include "MovementHandler.h"


MovementHandler::MovementHandler(Position* position, Speed* speed){
	position_ = position;
	speed_ = speed;
}

void MovementHandler::move_in_direction(string direction){
    if (direction=="up"){
    }
    else if (direction=="down"){
    }
    else if (direction=="right"){
    }
    else if (direction=="left"){
    }

    else if (direction == "top right"){
    }

    else if (direction == "top left"){
    }
    
    else if (direction == "lower right"){
    }

    else if ( direction == "lower left"){
    }
    else{
    }
}
	/*int ok = map.move_in_direction(direction, id);
	string s_id="";
	s_id = std::to_string(id);
	if (ok==0){
	Logger::getInstance()->log(INFO,"El elemento "+ s_id +  "se movió en la dirección: " + direction );
	}
	else{
		Logger::getInstance()->log(INFO,"Se ha producido un error al intentar mover al elemento " + s_id + "en la dirección  " + direction);
	}*/

