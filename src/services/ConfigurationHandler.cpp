#include "ConfigurationHandler.h"

ConfigurationHandler* ConfigurationHandler::instance = nullptr;

ConfigurationHandler::ConfigurationHandler(){
    this->parserJson = new ParserJson();
}

ConfigurationHandler* ConfigurationHandler::getInstance(){
    if (instance == nullptr)
        instance = new ConfigurationHandler();
        
    return instance;
}

bool ConfigurationHandler::loadFileConfiguration(const string &pathFileConfiguration){
    return this->parserJson->loadConfiguration(pathFileConfiguration);
}

void ConfigurationHandler::setLogLevel(){
    this->parserJson->setLogLevel();
}