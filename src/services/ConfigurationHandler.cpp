#include "ConfigurationHandler.h"

ConfigurationHandler::ConfigurationHandler(){
    this->parserJson = new ParserJson();
    this->levelData = new vector<stepContent_t>();
}

ConfigurationHandler::~ConfigurationHandler(){
    delete this->parserJson;
    //delete this->levelData;
}

bool ConfigurationHandler::loadFileConfiguration(const string &pathFileConfiguration){
    return this->parserJson->loadConfiguration(pathFileConfiguration);
}

void ConfigurationHandler::initializeData(){
    //this->parserJson->loadLevelsData(this->levelData);

    /*
    Como se iteraria:
    for (vector<levelContent_t>::iterator it = this->levelData->begin(); it != this->levelData->end(); it++){
        cout << it->stage_.layer1 << endl;
        cout << it->stage_.layer2 << endl;
        cout << it->stage_.layer3 << endl;
        for (enemy_t oneEnemy : it->enemies_){
            oneEnemy.type;
            oneEnemy.quantity;
            oneEnemy.sprite;
        }
    }*/
}

void ConfigurationHandler::setLogLevel(){
    this->parserJson->setLogLevel();
}

stageSource_t ConfigurationHandler::getStageData(int oneLevel){
    //return this->levelData->at(oneLevel).stage;
}