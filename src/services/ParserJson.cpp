#include "ParserJson.h"

ParserJson::ParserJson(){

    ifstream fileDefault(DEFAULT_CONFIGURATION, ifstream::in);
    fileDefault >> jsonDefault;

    fileDefault.close(); 
};

ParserJson::~ParserJson(){
    
};

bool ParserJson::loadConfiguration(const string &pathFileConfiguration){
    
    ifstream fileConfiguration(pathFileConfiguration, ifstream::in);

    if (fileConfiguration.is_open()){
        fileConfiguration >> jsonConfiguration;
        fileConfiguration.close(); 
    } else {
        Logger::getInstance()->log(ERROR, "Ocurrio un error al intentar abrir el archivo de configuracion. Se lo reemplaza por el archivo default.");
        this->setConfigDefault();
    }

    return (!jsonConfiguration.is_null());
};

int ParserJson::getSizeArray(string pathJson){

    json::json_pointer jsonPointerPath(pathJson);

    if (!jsonConfiguration[jsonPointerPath].is_array()){
        if (this->isNull(jsonConfiguration, jsonPointerPath)){
            Logger::getInstance()->log(ERROR, "No se encontro la ruta " + jsonPointerPath.to_string() + " en el archivo de configuracion.");
        } else {
            Logger::getInstance()->log(ERROR, "Error al leer la ruta " + jsonPointerPath.to_string() + " del archivo de configuracion. Se esperaba un dato del tipo array.");
        }
        
        return this->getSizeArrayDefault(jsonPointerPath);
    }

    return jsonConfiguration[jsonPointerPath].size();
};

string ParserJson::getString(string pathJson){

    json::json_pointer jsonPointerPath(pathJson);

    if (!jsonConfiguration[jsonPointerPath].is_string()){
        if (this->isNull(jsonConfiguration, jsonPointerPath)){
            Logger::getInstance()->log(ERROR, "No se encontro la ruta " + jsonPointerPath.to_string() + " en el archivo de configuracion.");
        } else {
            Logger::getInstance()->log(ERROR, "Error al leer la ruta " + jsonPointerPath.to_string() + " del archivo de configuracion. Se esperaba un dato del tipo string.");
        }
        
        return this->getStringDefault(jsonPointerPath);
    }

    return jsonConfiguration[jsonPointerPath].get<string>();
};

int ParserJson::getUnsignedInt(string pathJson){
    
    json::json_pointer jsonPointerPath(pathJson);

    if (!jsonConfiguration[jsonPointerPath].is_number_unsigned()){
        if (this->isNull(jsonConfiguration, jsonPointerPath)) {
            Logger::getInstance()->log(ERROR, "No se encontro la ruta " + jsonPointerPath.to_string() + " en el archivo de configuracion.");
        } else {
            Logger::getInstance()->log(ERROR, "Error al leer la ruta " + jsonPointerPath.to_string() + " del archivo de configuracion. Se esperaba un dato del tipo unsigned int.");
        }
        
        return this->getUnsignedIntDefault(jsonPointerPath);
    }
    
    return jsonConfiguration[jsonPointerPath].get<unsigned int>(); 
};

int ParserJson::getSizeArrayDefault(json::json_pointer jsonPointerPath) {

    Logger::getInstance()->log(INFO, "Se lee la ruta " + jsonPointerPath.to_string() + " del archivo default de configuracion.");
    
    if (this->isNull(jsonDefault, jsonPointerPath))
        return -1;

    return jsonDefault[jsonPointerPath].size(); 
};

string ParserJson::getStringDefault(json::json_pointer jsonPointerPath){

    Logger::getInstance()->log(INFO, "Se lee la ruta " + jsonPointerPath.to_string() + " del archivo default de configuracion.");
    if (this->isNull(jsonDefault, jsonPointerPath))
        return "";

    return jsonDefault[jsonPointerPath].get<string>(); 
};

int ParserJson::getUnsignedIntDefault(json::json_pointer jsonPointerPath){

    Logger::getInstance()->log(INFO, "Se lee la ruta " + jsonPointerPath.to_string() + " del archivo default de configuracion.");
    if (this->isNull(jsonDefault, jsonPointerPath))
        return -1;

    return jsonDefault[jsonPointerPath].get<unsigned int>(); 
};  

bool ParserJson::isNull(json oneJson, json::json_pointer pathJsonPointer){
    return oneJson[pathJsonPointer].is_null();
};


void ParserJson::setConfigDefault(){
    this->jsonConfiguration = jsonDefault;
};