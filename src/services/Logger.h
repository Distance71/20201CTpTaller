#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>

enum LOGLEVEL {ERROR, INFO, DEBUG};

using namespace std;

class Logger {

    public:
    Logger();
    //~Logger();
    void log(LOGLEVEL level_, const string& message);

};


#endif