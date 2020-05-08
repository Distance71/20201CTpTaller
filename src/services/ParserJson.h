#ifndef _PARSERJSON_H_
#define _PARSERJSON_H_

#include <iostream>
#include <stdio.h>
#include <fstream>
#include "nlohmann/json.hpp"
#include "Logger.h"
#include "../game/type.h"

#define DEFAULT_CONFIGURATION "../default/ConfigurationDefault.json"
#define DEFAULT_LOG_LEVEL "INFO"
#define DEFAULT_LEVEL ".json"

#define DEFAULT_enemy_tYPE "Class_Default"
#define DEFAULT_ENEMY_QUANTITY 10
#define DEFAULT_ENEMY_SPRITE "..default/"

using namespace std;
using json = nlohmann::json;

//Encargado de manejar el parseo de JSON

class ParserJson {

    private:
        json jsonConfiguration;

        ifstream loadFile(const string &pathFile, string valueDefault);
        vector<enemy_t> getEnemies(json jsonEnemies, string numberLevel);

    public:
        ParserJson();
        ~ParserJson();

        void loadLevelsData(vector<levelContent_t> *levelData);
        bool loadConfiguration(const string &pathFileConfiguration);

        void setLogLevel();
};


#endif //_PARSERJSON_H_