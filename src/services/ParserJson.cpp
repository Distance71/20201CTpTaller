#include "ParserJson.h"

ParserJson::ParserJson(){

};

ParserJson::~ParserJson(){
    
}

ifstream ParserJson::loadFile(const string &pathFile, string valueDefault){
    ifstream i(pathFile, ifstream::in);
    
    if (!i.is_open()){
        i.open(valueDefault, ifstream::in);
    }

    return i;
};

bool ParserJson::loadConfiguration(const string &pathFileConfiguration){
    
    ifstream fileConfiguration = loadFile(pathFileConfiguration, DEFAULT_CONFIGURATION);

    fileConfiguration >> jsonConfiguration;

    fileConfiguration.close(); 

    return (!jsonConfiguration.is_null());
};


int ParserJson::getSizeArray(string pathJson){

    json::json_pointer jsonPointerPath(pathJson);

    if (!jsonConfiguration[jsonPointerPath].is_array()){
        if (jsonConfiguration[jsonPointerPath].is_null()){
            Logger::getInstance()->log(ERROR, "No se encontro la ruta " + jsonPointerPath.to_string() + " en el archivo de configuracion.");
        } else {
            Logger::getInstance()->log(ERROR, "Error al leer la ruta " + jsonPointerPath.to_string() + " del archivo de configuracion. Se esperaba un dato del tipo array.");
        }
        
        return -1;
    }

    return jsonConfiguration[jsonPointerPath].size();
};

string ParserJson::getString(string pathJson){

    json::json_pointer jsonPointerPath(pathJson);

    if (!jsonConfiguration[jsonPointerPath].is_string()){
        if (jsonConfiguration[jsonPointerPath].is_null()){
            Logger::getInstance()->log(ERROR, "No se encontro la ruta " + jsonPointerPath.to_string() + " en el archivo de configuracion.");
        } else {
            Logger::getInstance()->log(ERROR, "Error al leer la ruta " + jsonPointerPath.to_string() + " del archivo de configuracion. Se esperaba un dato del tipo string.");
        }
        
        return "";
    }

    return jsonConfiguration[jsonPointerPath].get<string>();
};

int ParserJson::getUnsignedInt(string pathJson){
    
    json::json_pointer jsonPointerPath(pathJson);

    if (!jsonConfiguration[jsonPointerPath].is_number_unsigned()){
        if (jsonConfiguration[jsonPointerPath].is_null()) {
            Logger::getInstance()->log(ERROR, "No se encontro la ruta " + jsonPointerPath.to_string() + " en el archivo de configuracion.");
        } else {
            Logger::getInstance()->log(ERROR, "Error al leer la ruta " + jsonPointerPath.to_string() + " del archivo de configuracion. Se esperaba un dato del tipo unsigned int.");
        }
        
        return -1;
    }
    
    return jsonConfiguration[jsonPointerPath].get<unsigned int>(); 
};
