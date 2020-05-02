#ifndef _CONFIGURATIONHANDLER_H_
#define _CONFIGURATIONHANDLER_H_

#include "ParserJson.h"

using namespace std;

//Encargado de manejar la configuracion inicial del programa

class ConfigurationHandler {

    private: 
        static ConfigurationHandler* instance;

        ParserJson *parserJson;

        ConfigurationHandler();
    public:
        static ConfigurationHandler* getInstance();
        //~ConfigurationHandler();
        bool loadFileConfiguration(const string &pathFileConfiguration);
        void setLogLevel();
};


#endif