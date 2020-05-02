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

json ParserJson::getJsonDefaultEnemies(){
    json defaultEnemies = json::array();
    json oneEnemy = json::object();
    
    oneEnemy["type"] = DEFAULT_ENEMY_TYPE;
    oneEnemy["quantity"] = (unsigned int) DEFAULT_ENEMY_QUANTITY *3;
    oneEnemy["sprite"] = DEFAULT_ENEMY_SPRITE;
    
    defaultEnemies.insert(defaultEnemies.end(), {oneEnemy});;

    return defaultEnemies;
};

void ParserJson::setLogLevel(){

    string logLevel;

    if (jsonConfiguration["log"]["level"].is_string()){
        
        logLevel = jsonConfiguration["log"]["level"].get<string>();        
        Logger::getInstance()->setLevel(logLevel);
    }
};

bool ParserJson::loadConfiguration(const string &pathFileConfiguration){
    
    ifstream fileConfiguration = loadFile(pathFileConfiguration, DEFAULT_CONFIGURATION);

    fileConfiguration >> jsonConfiguration;
    jsonConfiguration = jsonConfiguration["configuracion"];

    fileConfiguration.close(); 

    return (!jsonConfiguration.is_null());
};

void ParserJson::loadLevel(const string &pathFileLevel){

    ifstream i = loadFile(pathFileLevel, DEFAULT_LEVEL);
    //i >> jsonConfiguration;
    i.close();
};

void ParserJson::setEnemies(){

    json jsonEnemies;

    if (jsonConfiguration["game"]["enemies"].is_array()){
        jsonEnemies = jsonConfiguration["game"]["enemies"].get<json>();
    } else {
        // Falta avisarle al Logger de lo ocurrido
        jsonEnemies = getJsonDefaultEnemies();
    }

    for (auto& oneEnemy: json::iterator_wrapper(jsonEnemies)){

        string typeEnemy;
        unsigned int qunatityEnemy;
        string pathEnemy;

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

        if (oneEnemy.value()["sprite"].is_string()){
            ifstream j(oneEnemy.value()["sprite"].get<string>(), ifstream::in);
            if (j.is_open()){
                pathEnemy = oneEnemy.value()["sprite"].get<string>();
                j.close();
            } else {
                pathEnemy = DEFAULT_ENEMY_SPRITE; 
            }      
        } else {
            pathEnemy = DEFAULT_ENEMY_SPRITE;
        }  

        //Faltaria settearle al encargado de distribuir los enemigos
    }
};

void ParserJson::setStages(){

    json jsonStages;

    if (jsonConfiguration["game"]["stages"].is_array()){
        jsonStages = jsonConfiguration["game"]["stages"].get<json>();
    } else {
        // Leer Stages por defecto y avisarle al Logger
    }

    for (auto& oneStage: json::iterator_wrapper(jsonStages)){

    }
};
