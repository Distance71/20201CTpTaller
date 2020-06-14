#include "MessageInitScreen.h"

MessageInitScreen::MessageInitScreen(size_t width, size_t height) : Message(INIT_SCREEN){
    this->screenWidth_ = width;
    this->screenHeight_ = height;
}

MessageInitScreen::~MessageInitScreen(){

}

string MessageInitScreen::getStringData(){
    string dataString;

    dataString.push_back(this->type_);
    dataString.push_back(this->screenWidth_);
    dataString.push_back(this->screenHeight_);

    return dataString;
}

size_t MessageInitScreen::getWidth(){
    return this->screenWidth_;
};

size_t MessageInitScreen::getHeight(){
    return this->screenHeight_;
};
