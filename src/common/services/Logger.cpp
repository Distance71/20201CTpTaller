#include "Logger.h"

Logger* Logger::instance = nullptr;

Logger::Logger(){
	// crea la carpeta logs si no existe
	mkdir(LOG_FOLDER, 0777);
	this->logFile = new ofstream();
	// crea el log con la fecha actual
	this->logFile->open(LOG_FOLDER + getTime() + "_log.txt");
	if (!this->logFile){
	    std::cerr << "ERROR creando archivo log. No se puede continuar. \n";
	    exit(1);
	 }
	// inicializa el log con una cabecera
	 *(this->logFile) << "##################################################\n"
	 				  << "# TALLER DE PROGRAMACIÓN I - CATEDRA AZCURRA \n"
					  << "# 1° Cuatrimestre 2020 - " << getFullTime()
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

string Logger::getFullTime(){
	time_t timestamp;
	time(&timestamp);
	string timestamp_transform(ctime(&timestamp));
	return timestamp_transform;
}

string Logger::getTime(){
	return (getFullTime()).substr(4,15);
}

void Logger::log(LOG_LEVEL level, const string& message){
	if (this->level >= level) {
		*(this->logFile) << getTime() << " - " << levelToString(level) << " - "  << message << " \n";
		this->logFile->flush();
	}
}

 bool Logger::setLevel(const string& level){
	// busca level en el mapa para ver si existe
	auto result = string2Enum.find(level);
 	if (result != std::end(string2Enum)) {
		// setea el level del log
        this->level = result->second;
		return true;
    } 
	else {
		log(ERROR, "Nivel de log invalido: " + level);		
	}
	return false;
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
