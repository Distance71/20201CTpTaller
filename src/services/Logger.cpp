#include "Logger.h"

Logger* Logger::instance = nullptr;

Logger::Logger(){
	// crea la carpeta logs si no existe
	mkdir(LOG_FOLDER, 0777);
	this->logFile = new ofstream();
	// crea el log con la fecha actual
	this->logFile->open(LOG_FOLDER + getTime(false) + "_log.txt");
	if (!this->logFile){
	    std::cerr << "ERROR creando archivo log. No se puede continuar. \n";
	    exit(1);
	 }
	// inicializa el log con una cabecera
	 *(this->logFile) << "##################################################\n"
	 				  << "# TALLER DE PROGRAMACIÓN I - CATEDRA AZCURRA \n"
					  << "# 1° Cuatrimestre 2020 - " << getTime(true)
					  << "##################################################\n\n";
	this->logFile->flush();
	// setea nivel por defecto al nivel mas alto
	this->level = DEBUG;
}

Logger* Logger::getInstance()
{
  if (instance == nullptr)
    instance = new Logger();
  return instance;
}

string Logger::getTime(bool full){
	time_t timestamp;
	time(&timestamp);
	string timestamp_transform(ctime(&timestamp));
	if (full) return timestamp_transform;
	return timestamp_transform.substr(4,15);
}

void Logger::log(LOG_LEVEL level, const string& message){
	if (this->level >= level) {
		*(this->logFile) << getTime(false) << " - " << levelToString(level) << " - "  << message << " \n";
		this->logFile->flush();
	}
}

 void Logger::setLevel(const string& level){
	// busca level en el mapa para ver si existe
	auto result = string2Enum.find(level);
 	if (result != std::end(string2Enum)) {
		// setea el level del log
        this->level = result->second;
    } 
	else {
		log(ERROR, "Nivel de log invalido: " + level);
	}
 }

 string Logger::levelToString(LOG_LEVEL level) {
    switch (level) {
        case ERROR:
            return "ERROR";
        case INFO:
            return "INFO ";
        case DEBUG:
            return "DEBUG";
    }
}

Logger::~Logger(){
	this->logFile->close();
	delete this->logFile;
}
