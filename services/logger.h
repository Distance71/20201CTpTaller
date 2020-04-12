#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>

using namespace std;

enum LOGLEVEL {ERROR, INFO, DEBUG};

class Logger {

    public:
    Logger();
    //~Logger();
    void log(LOGLEVEL level_, const string& message);

};


#endif