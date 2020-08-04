#include "Menu.h"

Menu::Menu(Client* clientOwn){
    this->clientOwn_ = clientOwn;
    SDL_StartTextInput();
    gRenderer = GameProvider::getRenderer();
    this->response_ = NOT_RESPONSE;
    
    loginScreen_t loginScreen = GameProvider::getLoginScreen();
    
    MenuElement* background = new MenuElement(0,0,-1,-1,loginScreen.background.c_str());
    addMenuElement("BACKGROUND",background);
    
    MenuElement* normal_box = new MenuElement(20,50,525,325,loginScreen.normalBox.c_str());
    addMenuElement("NORMAL BOX",normal_box);
   
    MenuElement* invalid_credentials_box = new MenuElement(20,50,525,325,loginScreen.invalidCredentialsBox.c_str());
    addMenuElement("INVALID CREDENTIALS BOX",invalid_credentials_box);

    MenuElement* full_game_box = new MenuElement(20,50,525,325,loginScreen.fullGameBox.c_str());
    addMenuElement("FULL GAME BOX",full_game_box);

    MenuElement* already_login_box = new MenuElement(20,50,525,325,loginScreen.alreadyLoggedIn.c_str());
    addMenuElement("ALREADY LOGIN BOX", already_login_box);
    
    TextBox* username = new TextBox(80,110,375,60,loginScreen.username1.c_str(),loginScreen.username2.c_str());
    username->setCenteringParameters(50,10,15,10);
    addTextBox("USERNAME",username);
    
    TextBox* password = new TextBox(80,180,375,60,loginScreen.password1.c_str(),loginScreen.password2.c_str());
    password->hideText(true);
    password->setCenteringParameters(50,10,15,10);
    addTextBox("PASSWORD",password);
    
    string cpyLogin = loginScreen.login;
    Button* login = new Button(300,260,200,50,loginScreen.login.c_str(),cpyLogin.c_str());
    addButton("LOGIN",login);

    Music::getInstance()->setSong("assets/Music/menu.mp3");   
    Music::getInstance()->play();  
}


Menu::~Menu(){
    for(auto button : buttons){
        delete button.second;
    }
    for(auto text_box: text_boxes){ 
        delete text_box.second;
    }
    for(auto menu_element: menu_elements){ 
        delete menu_element.second;
    }
}

void Menu::addButton(string button_name,Button* button){
    buttons[button_name] = button;
}

void Menu::addTextBox(string text_box_name,TextBox* text_box){
    text_boxes[text_box_name] = text_box;
}

void Menu::addMenuElement(string element_name,MenuElement* menu_element){
    menu_elements[element_name] = menu_element;
}

void Menu::update(int x, int y,bool click){
    
    SDL_RenderClear(gRenderer);
    
    this-> menu_elements["BACKGROUND"]->renderCopy();
    
    if (this->response_ == NOT_RESPONSE || this->response_ == OK) {
        menu_elements["NORMAL BOX"]->renderCopy();
    }
    else if(this->response_ == ERROR_WRONG_CREDENTIALS){
        menu_elements["INVALID CREDENTIALS BOX"]->renderCopy();
    }
    else if(this->response_ == ERROR_FULL_GAME){
        menu_elements["FULL GAME BOX"]->renderCopy();
    }
    else if (this->response_ == ERROR_ALREADY_LOGGED_IN)
        menu_elements["ALREADY LOGIN BOX"]->renderCopy();

    for(auto button : buttons){
        button.second->update(x,y,click,false);
    }
    for(auto text_box: text_boxes){
        text_box.second->update(x,y,click);    
    }
}


void Menu::sendCredentialsMessage(){
    if (buttons["LOGIN"]->isSelected()){
        const char* username = text_boxes["USERNAME"]->getText();
        const char* password = text_boxes["PASSWORD"]->getText();
        if (strlen(username)<=30 && strlen(password)<=30){
            char _username[30];
            char _password[30];
            strncpy (_username, username, 30);
            strncpy (_password, password, 30);
            MessageRequestLoginPlayer* message = new MessageRequestLoginPlayer(_username,_password);
            this->clientOwn_->sendMessage(message);
        }
        else{
            setLoginResponse(ERROR_WRONG_CREDENTIALS);
        }
        buttons["LOGIN"]->deselect();
    }
}


void Menu::checkStatus(){
    if (this->response_ == OK)
        this->clientOwn_->setLoggedInStatus();
}

void Menu::processEvent(){  
    bool click = false;   
    int x = -1;
    int y = -1;
    SDL_Event e = GameProvider::getLastEvent();
    if(e.type == SDL_MOUSEBUTTONDOWN){
        SDL_GetMouseState(&x, &y);
        click = true;
    }
    else if (e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN){
        for(auto text_box : text_boxes){
            text_box.second->readInput(&e);
        }    
    }
    update(x,y,click);
    sendCredentialsMessage();
}

void Menu::show(){
    update(-1,-1,false);
    SDL_RenderPresent(this->gRenderer);  
}

void Menu::setLoginResponse(responseStatus_t response){
    if(response == ERROR_FULL_GAME)
        Logger::getInstance()->log(INFO, "El usuario no ha podido loguearse, juego completo");
    else if (response == ERROR_WRONG_CREDENTIALS)
        Logger::getInstance()->log(INFO, "El usuario no ha podido loguearse, ha ingresado mal sus credenciales");
    else
        Logger::getInstance()->log(INFO, "El usuario se ha logueado con exito en Menu");

    this->response_ = response;
}
