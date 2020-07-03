#include "Menu.h"

    Menu::Menu(Client* _client){
    SDL_StartTextInput();
    gRenderer = GameProvider::getRenderer();
    client = _client;
    invalid_credentials=false;
    
    MenuElement* background = new MenuElement(0,0,GameProvider::getWidth(),GameProvider::getHeight(),"assets/LoginScreen/background.png");
    addMenuElement("BACKGROUND",background);
    
    MenuElement* normal_box = new MenuElement(20,50,525,325,"assets/LoginScreen/normalBox.png");
    addMenuElement("NORMAL BOX",normal_box);
   
    MenuElement* invalid_credentials_box = new MenuElement(20,50,525,325,"assets/LoginScreen/invalidCredentialsBox.png");
    addMenuElement("INVALID CREDENTIALS BOX",invalid_credentials_box);
    
    TextBox* username = new TextBox(80,110,375,60,"assets/LoginScreen/username1.png","assets/LoginScreen/username2.png");
    username->setCenteringParameters(50,10,15,10);
    addTextBox("USERNAME",username);
    
    TextBox* password = new TextBox(80,180,375,60,"assets/LoginScreen/password1.png","assets/LoginScreen/password2.png");
    password->hideText(true);
    password->setCenteringParameters(50,10,15,10);
    addTextBox("PASSWORD",password);
    
    Button* login = new Button(300,260,200,50,"assets/LoginScreen/login.png","assets/LoginScreen/login.png");
    addButton("LOGIN",login);
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
    menu_elements["BACKGROUND"]->renderCopy();
    if (invalid_credentials){
        menu_elements["INVALID CREDENTIALS BOX"]->renderCopy();
    }
    else{
        menu_elements["NORMAL BOX"]->renderCopy();
    }
    for(auto button : buttons){
        button.second->update(x,y,click,false);
    }
    for(auto text_box: text_boxes){
        text_box.second->update(x,y,click);    
    }
}


void Menu::setCredentialsResponse(login_answer _answer){
    credentials_response = _answer;
}


bool Menu::validateCredentials(){
    if (buttons["LOGIN"]->isSelected()){
        string username = text_boxes["USERNAME"]->getText();
        string password = text_boxes["PASSWORD"]->getText();
        MessageRequestLoginPlayer* message = new MessageRequestLoginPlayer(username,password);
        client->getTransmitionManager()->sendMessage(message);
        //bool response = client_transmition_manager -> getRequestloginPlayerResponse();
        return false;
    }
}



void Menu::processEvent(){  
    bool click = false;   
    int x = -1;
    int y = -1;
    SDL_Event e = GameProvider::getLastEvent();
    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN){
        SDL_GetMouseState(&x, &y);
        if (e.type==SDL_MOUSEBUTTONDOWN){
            click = true;
        }
    }
    else if (e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN){
        for(auto text_box : text_boxes){
            text_box.second->readInput(&e);
        }    
    }
    update(x,y,click);
}



void Menu::show(){
    update(-1,-1,false);
    SDL_RenderPresent(gRenderer);  
}
