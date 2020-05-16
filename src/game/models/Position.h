#ifndef _POSITION_H_
#define _POSITION_H_

#include "State.h"
// Se encarga de manejar internamente la informacion de la posicion de los elementos
// La misma se debe requerir al mapa, ya que los elementos dependen de este.

class Position: public State  {
    
    public:
    Position();
    Position(int x, int y);
    int getX()override;
    int getY()override;
    void setX(int x_)override;
    void setY(int y_)override;
};

#endif
