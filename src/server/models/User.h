#ifndef USER_H
#define USER_H

#include <string>
#include "../../common/models/Socket.h"
#include "../../common/types.h"

using namespace std;


class User {

private:
    string userName_;
    string password_;
    Socket *socket_;
    character_t character_;
    bool connected_ = false;

public:
    User() = default;
    ~User() = default;
    User(string userName, string password);

    string getUserName();
    string getPassword();

    void setUserName(string userName);
    void setPassword(string password);

    void setCharacter(character_t character);
    character_t getCharacter();

    void setSocket(Socket *socket);
    Socket *getSocket();

    bool isConnected();
    void disconnect();
};


#endif //FINAL_FIGHT_USUARIO_H
