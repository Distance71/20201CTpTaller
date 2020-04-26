#ifndef _PARSERJSON_H_
#define _PARSERJSON_H_

#include <iostream>
#include <stdio.h>
#include <fstream>
#include "nlohmann/json.hpp"
#include "Logger.h"

#define DEFAULT_CONFIGURATION "../default/ConfigurationDefault.json"
#define DEFAULT_LOG_LEVEL "INFO"
#define DEFAULT_LEVEL ".json"

#define DEFAULT_ENEMY_TYPE "Class_Default"
#define DEFAULT_ENEMY_QUANTITY 10

using namespace std;
using json = nlohmann::json;

//Encargado de manejar el parseo de JSON

class ParserJson {

    private:
        json jsonConfiguration;

        ifstream loadFile(const string &pathFile, string valueDefault);

    public:
        ParserJson();

        void setLogLevel();
        void setEnemies();

        void loadLevel(const string &pathFileLevel);
        void loadConfiguration(const string &pathFileConfiguration);
};


#endif //_PARSERJSON_H_