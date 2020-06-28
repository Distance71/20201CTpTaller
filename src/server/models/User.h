#ifndef USER_H
#define USER_H

#include <string>
#include "../../common/models/Socket.h"
#include "../../common/types.h"
#include "../../common/models/messages/Message.h"

using namespace std;

class User {

private:
    string userName_ = "";
    string password_ = "";
    Socket *socket_;
    character_t character_;
    IdUser userId_;

    bool connected_ = false;
    bool logged_ = false;

public:
    //User() = default;
    ~User();
    User(string userName, string password);
    User(Socket *socket);

    string getUserName();
    string getPassword();

    void setUserName(string userName);
    void setPassword(string password);

    void setLoggedIn();

    void setCharacter(character_t character);
    character_t getCharacter();

    void setSocket(Socket *socket);
    Socket *getSocket();

    IdUser getId();

    bool isConnected();
    void setDisconnection();

    void sendMessage(Message *message);
    Message receiveMessage();
};


#endif //FINAL_FIGHT_USUARIO_H
