#include "ParserJson.h"

ParserJson::ParserJson(){

};

ifstream ParserJson::loadFile(const string &pathFile, string valueDefault){
    ifstream i(pathFile, ifstream::in);
    
    if (!i.is_open()){
        i.open(valueDefault, ifstream::in);
    }

    return i;
};

void ParserJson::setLogLevel(){

    string logLevel;

    if (jsonConfiguration["log"]["level"].is_string()){
        logLevel = jsonConfiguration["log"]["level"].get<string>();
    } else {
        logLevel = DEFAULT_LOG_LEVEL;
    }

    Logger::getInstance()->setLevel(logLevel);
};

void ParserJson::loadConfiguration(const string &pathFileConfiguration){
    
    ifstream fileConfiguration = loadFile(pathFileConfiguration, DEFAULT_CONFIGURATION);

    fileConfiguration >> jsonConfiguration;
    jsonConfiguration = jsonConfiguration["configuracion"];

    fileConfiguration.close(); 
};

void ParserJson::loadLevel(const string &pathFileLevel){

    ifstream i = loadFile(pathFileLevel, DEFAULT_LEVEL);
    //i >> jsonConfiguration;
    i.close();
};

void ParserJson::setEnemies(){

    json jsonEnemies;

    if (jsonConfiguration["enemies"]["game"].is_array()){
        jsonEnemies = jsonConfiguration["enemies"]["game"].get<json>();
    } else {
        // Avisarle al LOG que no se pasaron enemigo y cargar por defecto
    }

    for (auto& oneEnemy: json::iterator_wrapper(jsonEnemies)){

        string typeEnemy;
        unsigned int qunatityEnemy;

        if (oneEnemy.value()["type"].is_string()){
            typeEnemy = oneEnemy.value()["type"].get<string>();
        } else {
            typeEnemy = DEFAULT_ENEMY_TYPE;
        }

        if (oneEnemy.value()["quantity"].is_number_unsigned()){
            qunatityEnemy = oneEnemy.value()["quantity"].get<unsigned int>();
        } else {
            qunatityEnemy = DEFAULT_ENEMY_QUANTITY;
        }

        //Faltaria settearle al encargado de distribuir los enemigos
    }
};
