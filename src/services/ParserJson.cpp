#include "ParserJson.h"

ParserJson::ParserJson(){

};

ParserJson::~ParserJson(){
    
}

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
        Logger::getInstance()->setLevel(logLevel);
    } else {      
        Logger::getInstance()->setLevel(logLevel);
        Logger::getInstance()->log(ERROR, "Hubo un error al leer el nivel del Log en el archivo de configuracion.");
    }
};

bool ParserJson::loadConfiguration(const string &pathFileConfiguration){
    
    ifstream fileConfiguration = loadFile(pathFileConfiguration, DEFAULT_CONFIGURATION);

    fileConfiguration >> jsonConfiguration;
    jsonConfiguration = jsonConfiguration["configuracion"];

    fileConfiguration.close(); 

    return (!jsonConfiguration.is_null());
};

void ParserJson::loadLevelsData(vector<stepContent_t> *levelData){

    json jsonLevels;

    // Logger::getInstance()->log(DEBUG, "Se comienza a cargan la informacion de los niveles del archivo de configuracion.");

    // if (!jsonConfiguration["level"].is_array()){
    //     Logger::getInstance()->log(ERROR, "No se pudo leer la informacion de los niveles del archivo de configuracion.");
    //     return;    
    // } 

    // jsonLevels = jsonConfiguration["level"].get<json>();

    for (auto& oneLevel: json::iterator_wrapper(jsonLevels)){
        stepContent_t level;
        json jsonEnemies;
        unsigned int numberLevel = atoi(oneLevel.key().c_str());

    //     if (oneLevel.value()["layer1"].is_string()){
    //         level.stage_.layer1 = oneLevel.value()["layer1"].get<string>();
    //     } else {
    //         Logger::getInstance()->log(ERROR, "El layer1 para el nivel " + oneLevel.key() + " no se encontro en el archivo de configuracion.");
    //     }

    //     if (oneLevel.value()["layer2"].is_string()){
    //         level.stage_.layer2 = oneLevel.value()["layer2"].get<string>();
    //     } else {
    //         Logger::getInstance()->log(ERROR, "El layer2 para el nivel " + oneLevel.key() + " no se encontro en el archivo de configuracion.");
    //     }

    //     if (oneLevel.value()["layer3"].is_string()){
    //         level.stage_.layer3 = oneLevel.value()["layer3"].get<string>();
    //     } else {
    //         Logger::getInstance()->log(ERROR, "El layer3 para el nivel " + oneLevel.key() + " no se encontro en el archivo de configuracion.");
    //     }

    //     if (oneLevel.value()["enemies"].is_array()){
    //         jsonEnemies = oneLevel.value()["enemies"].get<json>();
    //         level.enemies_ = getEnemies(jsonEnemies, oneLevel.key());
    //     } else {
    //         Logger::getInstance()->log(ERROR, "Los enemigos para el nivel " + oneLevel.key() + " no se encontraron en el archivo de configuracion.");
    //     }

    //     levelData->push_back(level);
    }
};

vector<enemy_t> ParserJson::getEnemies(json jsonEnemies, string numberLevel){

    vector<enemy_t> dataEnemies;

    for (auto& oneEnemy: json::iterator_wrapper(jsonEnemies)){
        enemy_t enemy_t;
        string typeEnemy;
        unsigned int qunatityEnemy;
        string pathEnemy;

        if (oneEnemy.value()["type"].is_string()){
            enemy_t.type = oneEnemy.value()["type"].get<string>();
        } else {
            Logger::getInstance()->log(ERROR, "Error al leer el tipo del enemigo " + oneEnemy.key() + " para el nivel " + numberLevel);
        }

        if (oneEnemy.value()["quantity"].is_number_unsigned()){
            enemy_t.quantity = oneEnemy.value()["quantity"].get<unsigned int>();
        } else {
            enemy_t.quantity = 0;
            Logger::getInstance()->log(ERROR, "Error al leer la cantidad del enemigo " + oneEnemy.key() + " para el nivel " + numberLevel);
        }

        if (oneEnemy.value()["sprite"].is_string()){
            enemy_t.sprite = oneEnemy.value()["sprite"].get<string>();    
        } else {
            Logger::getInstance()->log(ERROR, "Error al leer la ruta del sprite del enemigo " + oneEnemy.key() + " para el nivel " + numberLevel);
        }  

        dataEnemies.push_back(enemy_t);
    }

    return dataEnemies;
}
