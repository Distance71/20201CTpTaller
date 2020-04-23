#include "Logger.h"

using std::stringstream;
using std::string;

//TODO check static instance
Logger* Logger::instance = nullptr;

Logger::Logger(){
	this->logFile = new ofstream();	  
	//TODO check folder
	this->logFile->open(LOG_NAME);
	if (!this->logFile){
	    std::cerr << "ERROR en la creación del archivo log.";
	    exit(1);
	 }

	time_t timestamp;
	time(&timestamp);
	string timestamp_transform(ctime(&timestamp));

	 *(this->logFile) << "##################################################\n"
	 				  << "# TALLER DE PROGRAMACIÓN I - CATEDRA AZCURRA \n"
					  << "# 1° Cuatrimestre 2020 - " << timestamp_transform
					  << "##################################################\n\n";
	//TODO por q flush?
	this->logFile->flush();
}

Logger* Logger::getInstance()
{
  if (instance == nullptr)
    instance = new Logger();
  return instance;
}


//TODO
void Logger::log(LOG_LEVEL level, const string& message){
	time_t timestamp;
	time(&timestamp);
	string timestamp_transform(ctime(&timestamp),24);

	*(this->logFile) << timestamp_transform << " - " << message;
	this->logFile->flush();
}


//TODO
 void Logger::setLevel(const string& level){
 }

Logger::~Logger(){
	this->logFile->close();
	delete this->logFile;
}
