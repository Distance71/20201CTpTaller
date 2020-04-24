#ifndef _PARSERJSON_H_
#define _PARSERJSON_H_

#include <iostream>
#include <stdio.h>
#include <fstream>
#include "nlohmann/json.hpp"

#define DEFAULT_CONFIGURATION "Configuration.json"
#define DEFAULT_LEVEL ".json"

using namespace std;
using json = nlohmann::json;

//Encargado de manejar el parseo de JSON

class ParserJson {

    private:
        json jsonConfiguration;

        ifstream loadFile(string pathFile, string valueDefault);

    public:
        ParserJson();

        void loadLevel(string pathFileLevel);

        void loadConfiguration(string pathFileConfiguration);
};


#endif //_PARSERJSON_H_