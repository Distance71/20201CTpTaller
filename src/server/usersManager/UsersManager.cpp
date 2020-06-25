// #include "UsersManager.h"

// UsersManager::UsersManager(Server *server){
//     //this->id_ = idPlayer;
//     //this->socket_ = socket;
//     this->serverOwn_ = server;
// }

// UsersManager::~UsersManager(){}

// unordered_map<IdPlayer *> UsersManager::getUsers(){
// 	return this->users_;
// }

// //Checks remains players
// bool UsersManager::playersConnected(IdPlayer id) {
	
// 	if(users_.size())
// 		return true;

// 	return false;

// 	for ( auto User = users_.begin(); it != users_.end(); ++it )
// 		if()
// 		User->first
// 		it->second;
// }

// void UsersManager::setPlayer(IdPlayer idPlayer, User* user){
//     users_[idPlayer] = user;
// }

// bool UsersManager::isGameFull(){
// 	size_t maxPlayers = GameProvider::getQuantityPlayers();

// 	return users_.size() == maxPlayers
// }

// User* UsersManager::getPlayer(IdPlayer idPlayer){
// 	if (users_.find(idPlayer) == users_.end())
// 		return NULL;

// 	return users_[idPlayer];
// }