#ifndef _PARSERJSON_H_
#define _PARSERJSON_H_

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"
#include "Logger.h"
#include "../game/types.h"
#include "../game/models/Map.h"

#define DEFAULT_CONFIGURATION "../default/ConfigurationDefault.json"
#define DEFAULT_LOG_LEVEL "INFO"

using namespace std;
using json = nlohmann::json;

//Encargado de manejar el parseo de JSON

class ParserJson {

    private:
        json jsonConfiguration;

        ifstream loadFile(const string &pathFile, string valueDefault);

    public:
        ParserJson();
        ~ParserJson();

        bool loadConfiguration(const string &pathFileConfiguration);
        int getSizeArray(string pathJson);
        string getString(string pathJson);
        int getUnsignedInt(string pathJson);

};


#endif //_PARSERJSON_H_