#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <stdlib.h>
//TODO check includes

enum LOG_LEVEL {INVALID, ERROR, INFO, DEBUG};
//#define LOG_FOLDER "../logs/"
#define LOG_NAME "../logs/corona_logs.txt"
//TODO name dinamico

using namespace std;

class Logger {
    private:
    static Logger* instance;
    LOG_LEVEL level;
    ofstream* logFile;
    Logger();

    public:   
    static Logger* getInstance();
    void log(LOG_LEVEL level, const string& message);
    void setLevel(const string& level);
    virtual ~Logger();
};


#endif