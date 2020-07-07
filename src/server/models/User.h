#ifndef USER_H
#define USER_H

#include <string>
#include "../../common/models/Socket.h"
#include "../../common/types.h"
#include "../../common/models/messages/Message.h"
#include "../../common/models/events/Event.h"
#include "../../common/services/serializer/MessageDeserializer.h"
#include "../../common/services/serializer/MessageSerializer.h"

using namespace std;

class Message;

class User {

private:
    string userName_ = "";
    string password_ = "";
    Socket *socket_;
    character_t character_;
    IdUser userId_;
    MessageDeserializer *deserializer_;
    MessageSerializer *serializer_;

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
    void setId(IdUser id);

    bool isConnected();
    void setDisconnection();

    response_t sendMessage(Event* event);
    Event* receiveMessage();
};


#endif //FINAL_FIGHT_USUARIO_H
