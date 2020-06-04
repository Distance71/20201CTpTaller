#ifndef _PARSERJSON_H_
#define _PARSERJSON_H_

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"
#include "Logger.h"

#define DEFAULT_CONFIGURATION "../default/ConfigurationDefault.json"

using namespace std;
using json = nlohmann::json;

//Encargado de manejar el parseo de JSON

class ParserJson {

    private:
        json jsonConfiguration;
        json jsonDefault;

        int getSizeArrayDefault(json::json_pointer jsonPointerPath);
        string getStringDefault(json::json_pointer jsonPointerPath);
        int getUnsignedIntDefault(json::json_pointer jsonPointerPath);
        bool isNull(json oneJson, json::json_pointer pathJsonPointer); 

    public:
        ParserJson();
        ~ParserJson();

        bool loadConfiguration(const string &pathFileConfiguration);
        int getSizeArray(string pathJson);
        string getString(string pathJson);
        int getUnsignedInt(string pathJson);
        void setConfigDefault();
};


#endif //_PARSERJSON_H_