#ifndef _CONFIGURATIONHANDLER_H_
#define _CONFIGURATIONHANDLER_H_

#include "ParserJson.h"
#include "../game/type.h"
#include <vector>

using namespace std;

class ParserJson;

//Encargado de manejar la configuracion inicial del programa

class ConfigurationHandler {

    private: 
        vector<levelContent_t> *levelData;
        ParserJson *parserJson;

    public:
        ConfigurationHandler();
        ~ConfigurationHandler();

        bool loadFileConfiguration(const string &pathFileConfiguration);
        void initializeData();
        void setLogLevel();

        stage_t getStageData(int oneLevel);
};


#endif