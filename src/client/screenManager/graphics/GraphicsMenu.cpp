#include "GraphicsMenu.h"

GraphicsMenu::GraphicsMenu(Client* clientOwn){
    this->clientOwn_ = clientOwn;
    SDL_StartTextInput();
    gRenderer = GameProvider::getRenderer();
    this->response_ = NOT_RESPONSE;
    
    loginScreen_t loginScreen = GameProvider::getLoginScreen();
    
    Image* background = new Image(loginScreen.background.c_str());
    addImage("BACKGROUND",background);
    
    Image* normal_box = new Image(loginScreen.normalBox.c_str());
    addImage("NORMAL BOX",normal_box);
   
    Image* invalid_credentials_box = new Image(loginScreen.invalidCredentialsBox.c_str());
    addImage("INVALID CREDENTIALS BOX",invalid_credentials_box);

    Image* full_game_box = new Image(loginScreen.fullGameBox.c_str());
    addImage("FULL GAME BOX",full_game_box);

    Image* already_login_box = new Image(loginScreen.alreadyLoggedIn.c_str());
    addImage("ALREADY LOGIN BOX", already_login_box);
    
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

    Audio::getInstance()->setSong("assets/Music/menu.mp3");   
    Audio::getInstance()->playMusic();
}


GraphicsMenu::~GraphicsMenu(){
    for(auto button : buttons){
        delete button.second;
    }
    for(auto text_box: text_boxes){ 
        delete text_box.second;
    }
    for(auto image: menuImages_){ 
        delete image.second;
    }
}

void GraphicsMenu::addButton(string button_name,Button* button){
    buttons[button_name] = button;
}

void GraphicsMenu::addTextBox(string text_box_name,TextBox* text_box){
    text_boxes[text_box_name] = text_box;
}

void GraphicsMenu::addImage(string element_name,Image* image){
    menuImages_[element_name] = image;
}

void GraphicsMenu::update(int x, int y,bool click){
    
    SDL_RenderClear(gRenderer);
    
    this-> menuImages_["BACKGROUND"]->renderCopy(0,0,-1,-1);
    
    if (this->response_ == NOT_RESPONSE || this->response_ == OK) {
        menuImages_["NORMAL BOX"]->renderCopy(20,50,525,325);
    }
    else if(this->response_ == ERROR_WRONG_CREDENTIALS){
        menuImages_["INVALID CREDENTIALS BOX"]->renderCopy(20,50,525,325);
    }
    else if(this->response_ == ERROR_FULL_GAME){
        menuImages_["FULL GAME BOX"]->renderCopy(20,50,525,325);
    }
    else if (this->response_ == ERROR_ALREADY_LOGGED_IN)
        menuImages_["ALREADY LOGIN BOX"]->renderCopy(20,50,525,325);

    for(auto button : buttons){
        button.second->update(x,y,click,false);
    }
    for(auto text_box: text_boxes){
        text_box.second->update(x,y,click);    
    }
}


void GraphicsMenu::sendCredentialsMessage(){
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


void GraphicsMenu::checkStatus(){
    if (this->response_ == OK)
        this->clientOwn_->setLoggedInStatus();
}

void GraphicsMenu::processEvent(){  
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

void GraphicsMenu::show(){
    update(-1,-1,false);
    SDL_RenderPresent(this->gRenderer);  
}

void GraphicsMenu::setLoginResponse(responseStatus_t response){
    if(response == ERROR_FULL_GAME)
        Logger::getInstance()->log(INFO, "El usuario no ha podido loguearse, juego completo");
    else if (response == ERROR_WRONG_CREDENTIALS)
        Logger::getInstance()->log(INFO, "El usuario no ha podido loguearse, ha ingresado mal sus credenciales");
    else
        Logger::getInstance()->log(INFO, "El usuario se ha logueado con exito en menu");

    this->response_ = response;
}
