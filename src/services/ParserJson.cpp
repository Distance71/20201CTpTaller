#include "ParserJson.h"

ParserJson::ParserJson(){

};

ifstream ParserJson::loadFile(string pathFile, string valueDefault){
    ifstream i(pathFile, ifstream::binary);
    
    if (!i.is_open()){
        i.open(valueDefault, ifstream::binary);
    }

    return i;
};

void ParserJson::loadConfiguration(string pathFileConfiguration){
    
    ifstream i = loadFile(pathFileConfiguration, DEFAULT_CONFIGURATION);
    i >> jsonConfiguration;
    i.close(); 
};

void ParserJson::loadLevel(string pathFileLevel){

    ifstream i = loadFile(pathFileLevel, DEFAULT_LEVEL);
    i >> jsonConfiguration;
    i.close();
}

