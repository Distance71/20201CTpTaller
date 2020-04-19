#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>

enum LOGLEVEL {ERROR, INFO, DEBUG};

using namespace std;

//Encargado de escribir los logs en un archivo segun configuracion
// Hay varias opciones. Se puede setear un nivel de log en GameProvider o bien
// invocar a ConfigurationHandler y pedir datos.

class Logger {

    public:
    Logger();
    //~Logger();
    void log(LOGLEVEL level_, const string& message);

};


#endif