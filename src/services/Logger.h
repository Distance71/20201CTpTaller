#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/stat.h>
#include <map>

enum LOG_LEVEL {INVALID, ERROR, INFO, DEBUG};
static std::map<std::string, LOG_LEVEL> string2Enum {
    { "ERROR", ERROR }, 
    { "error", ERROR },
    { "INFO", INFO }, 
    { "info", INFO },
    { "DEBUG", DEBUG },
    { "debug", DEBUG } 
};
#define LOG_FOLDER "../logs/"
using namespace std;

class Logger {
    private:
        static Logger* instance;
        LOG_LEVEL level;
        ofstream* logFile;

        Logger();
        string getTime();
        string getFullTime();
        string levelToString(LOG_LEVEL);

    public:   
        static Logger* getInstance();
        void log(LOG_LEVEL level, const string& message);
        // setLevel devuelve false si hubo error, true en caso satisfactorio
        bool setLevel(const string& level);
        virtual ~Logger();
};

#endif