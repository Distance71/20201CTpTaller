#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "../models/Action.h"

// Grafico generico "padre", podria encargarse de calcular las posiciones de los graficos
// Notar que renderer grafica solo una parte del mapa -> debe calcularse la posicion en la pantalla
// Mirar SDL_Rect SDL_RenderCopy SDL_Texture

class Graphics: Action {

    public:
    Graphics();
    //~Graphics();
    
};

#endif
