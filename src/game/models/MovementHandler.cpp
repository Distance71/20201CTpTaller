#include "MovementHandler.h"
#include "Map.h"
#include <string>

MovementHandler::MovementHandler(int id_map_element){
	id = id_map_element;
}

void MovementHandler::move_in_direction(string direction){
	/*int ok = map.move_in_direction(direction, id);
	string s_id="";
	s_id = std::to_string(id);
	if (ok==0){
	Logger::getInstance()->log(INFO,"El elemento "+ s_id +  "se movió en la dirección: " + direction );
	}
	else{
		Logger::getInstance()->log(INFO,"Se ha producido un error al intentar mover al elemento " + s_id + "en la dirección  " + direction);
	}*/
}
