#include "MessageGameInit.h"

MessageGameInit::MessageGameInit(unsigned int width, unsigned int height) : Message(INIT_GAME){
    this->screenWidth_ = width;
    this->screenHeight_ = height;
}

MessageGameInit::~MessageGameInit(){

}

string MessageGameInit::getStringData(){
    string dataString;

    dataString.push_back(this->type_);

    char* screenWidth_arr = (char*)&this->screenWidth_;
    for (unsigned int i = 0; i < sizeof(unsigned int); ++i)
        dataString.push_back(screenWidth_arr[i]);

    char* screenHeight_arr = (char*)&this->screenHeight_;
    for (unsigned int i = 0; i < sizeof(unsigned int); ++i)
        dataString.push_back(screenHeight_arr[i]);

    return dataString;
}

unsigned int MessageGameInit::getWidth(){
    return this->screenWidth_;
};

unsigned int MessageGameInit::getHeight(){
    return this->screenHeight_;
};
