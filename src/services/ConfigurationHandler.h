#ifndef _CONFIGURATIONHANDLER_H_
#define _CONFIGURATIONHANDLER_H_

#include "ParserJson.h"
#include <vector>
#include "../game/types.h"

using namespace std;

class ParserJson;

//Encargado de manejar la configuracion inicial del programa

class ConfigurationHandler {

    private: 
        //vector<Level_t> *levelData;
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