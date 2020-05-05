#ifndef _POSITION_H_
#define _POSITION_H_

#include "State.h"
#include "Speed.h"
#include <cmath>
// Se encarga de manejar internamente la informacion de la posicion de los elementos
// La misma se debe requerir al mapa, ya que los elementos dependen de este.

class Position: State  {
    private:
    int x, y;

    public:
    Position(int x, int y);
    int getXPosition();
    int getYPosition();
    void setXPosition(int x);
    void setYPosition(int y);
};

#endif
