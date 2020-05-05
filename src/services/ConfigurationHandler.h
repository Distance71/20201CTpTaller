#ifndef _CONFIGURATIONHANDLER_H_
#define _CONFIGURATIONHANDLER_H_

#include "ParserJson.h"

using namespace std;

//Encargado de manejar la configuracion inicial del programa

class ConfigurationHandler {

    private: 
        vector<Level_t> *levelData;
        ParserJson *parserJson;

    public:
        ConfigurationHandler();
        ~ConfigurationHandler();

        bool loadFileConfiguration(const string &pathFileConfiguration);
        void initializeData();
        void setLogLevel();

        Stage_t getStageData(int oneLevel);
};


#endif