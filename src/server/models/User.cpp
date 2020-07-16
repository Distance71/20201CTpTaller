#include "User.h"

User::User(Socket *socket,UsersManager* userManager){
	string userName_ = "";
    string password_ = "";
	this->socket_ = socket;
	this->connected_ = true;
    bool connected_ = false;
    bool logged_ = false;
	this->sendingQueue_ = new BlockingQueue <Message*>();
	this->usersManager_ = userManager;
}

User::~User() {
	delete this->sendingQueue_;
}


string User::getUserName(){
	return this->userName_;
}

string User::getPassword(){
	return this->password_;
}

void User::setCredentials(string userName, string password){
	this->userName_ = userName;
	this->password_ = password;
}


void User::setLoggedIn(){
	this->logged_ = true;
}


void User::setConnection(){
	this->connected_= true;
}

void User::setDisconnection(){
	this->connected_ = false;
}

bool User::isConnected(){
	return this->connected_;
}

Socket* User::getSocket(){
	return this->socket_;
}

UsersManager* User::getUsersManager(){
	return this->usersManager_;
}

void User::sendEvent(Event* event){
	this->sendingQueue_->push(event->serialize());
}

Message* User::getMessage(){
	if (!this->sendingQueue_->empty()){
		return this->sendingQueue_->pop();
	}
	return NULL;
}


static void* sendMessages(void* arg){
	User* user = (User*) arg;
	MessageSerializer serializer = MessageSerializer();
	Socket* socket = user->getSocket();
	while (user->isConnected()){
		Message* message = user->getMessage();
		if (message){;
			serializer.sendSerializedEvent(socket, message);
			delete message;
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
	}
}


void User::runSendingMessagesThread(){
	pthread_t sending_thread;
    pthread_create(&sending_thread,NULL,sendMessages,this);
}


static void* receivingMessages(void * arg){
	Logger::getInstance()->log(DEBUG, "Se inicia hilo del receptor del ususario ");
	User* user = (User*) arg;
	Socket* socket = user->getSocket();
	UsersManager* userManager = user->getUsersManager();
	MessageDeserializer deserealizer = MessageDeserializer();
	std::mutex mtxErrno;
	while(user->isConnected()){
		Event* event;
		deserealizer.getReceivedMessage(socket,event);
		if(!event){
            mtxErrno.lock();
            if (errno == ECONNREFUSED || errno == ENOTCONN || errno == ENOTSOCK) {
                Logger::getInstance()->log(DEBUG, "Se detecta desconexión del cliente.");
                user->setDisconnection();
                return nullptr;
            }
            mtxErrno.unlock();
            Logger::getInstance()->log(ERROR, "Se ha recibido un evento invalido. Se cerrará la conexión con el cliente");
            return nullptr;
        }
		else{
			userManager->processEvent(event);
		}		
	}
	Logger::getInstance()->log(DEBUG, "Se termina correctamente el hilo del receptor del ususario ");
    return nullptr;
}


void User::runReceivingMessagesThread(){
	pthread_t sending_thread;
    pthread_create(&sending_thread,NULL,receivingMessages,this);
}
