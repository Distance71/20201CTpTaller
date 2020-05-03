#include "GraphicsScenario.h"
#include <string>

GraphicsScenario::GraphicsScenario(int _stage){
    level = _stage;
    SDL_Renderer* renderer = GameProvider::getRenderer();

    /*Creo las variables donde se cargaran  las rutas de las imagenes dependiendo el nivel*/
    
    /*Leo las imagenes segun el nivel*/
    string layer_1_image_path= "";
    string layer_2_image_path = "";
    string layer_3_image_path = "";
    
    switch(level){
        case 1:
            layer_1_image_path= "assets/Stage/Stage1/layer_1_image.png";
            layer_2_image_path= "assets/Stage/Stage1/layer_2_image.png";
            layer_3_image_path= "assets/Stage/Stage1/layer_3_image.png";
            break;
        
        default:
            Logger::getInstance()->log(ERROR, string("No existe el nivel seleccionado. No se puedo acceder a las rutas de las capas del escenario"));
            GameProvider::setErrorStatus("NO existe el nuvel seleccionado. No se puedo acceder a las rutas de las capas del escenario" );
            return;
    }   

    
    /*Almaceno las imagenes en las superficies*/
    SDL_Surface* layer_1_image = IMG_Load( layer_1_image_path.c_str());
    SDL_Surface* layer_2_image = IMG_Load( layer_2_image_path.c_str());
    SDL_Surface* layer_3_image = IMG_Load( layer_3_image_path.c_str());

    if (!layer_1_image || !layer_2_image || !layer_3_image){
        Logger::getInstance()->log(ERROR, string("Error al cargar las capas del nivel! IMG_Error: ").append(IMG_GetError()));
        GameProvider::setErrorStatus(IMG_GetError());
        return;
    }

    /* las convierto en texturas*/
    SDL_Texture* layer_1_texture = SDL_CreateTextureFromSurface( renderer, layer_1_image );
    SDL_Texture* layer_2_texture = SDL_CreateTextureFromSurface( renderer, layer_2_image );
    SDL_Texture* layer_3_texture = SDL_CreateTextureFromSurface( renderer, layer_3_image );

    /*libero el espacio que use para las superficies*/
    SDL_FreeSurface( layer_1_image );
    SDL_FreeSurface( layer_2_image );
    SDL_FreeSurface( layer_3_image);

    /* Variables que se van a usar para controlar la posicion que me encuentro
    mostrando de las capas*/
    int step1 = 0;
    int step2 = 0;
    int step3 = 0;

    /* velocidad con que se mueven las capas*/
    int speed1 = 0;
    int speed2 = 2;
    int speed3 = 5;

    int screen_widht = GameProvider::getWidth();
    int screen_height = GameProvider::getHeight();
   
    /*auxparallax son rectangulos que van a servir para hacer recortes
    sobre las texturas para almacenar en ellos la parte que quiero mostrar
    en cada momento*/
    SDL_Rect auxParallax1  = { step1, 0, screen_widht, screen_height };
    SDL_Rect auxParallax2  = { step2, 0, screen_widht, screen_height };
    SDL_Rect auxParallax3  = { step3, 0, screen_widht, screen_height };
    

    /*las variables layer_n son
    rectangulos que se colocan sobre la pantalla y sobre los 
    cuales puedo mostrar cosas. Son como si fueran las capas sobre las cuales
    dibujo*/

    SDL_Rect layer_1 = { 0,0,screen_widht, screen_height};
    SDL_Rect layer_2 = { 0,0,screen_widht,screen_height};
    SDL_Rect layer_3 = { 0,0,screen_widht, screen_height};

    /*Bucle que maneja la repetición del fondo*/
    
    bool quit = false;
    SDL_Event e;
    while(!quit ){
        /*Se chequea que no se presione salir*/
        while( SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT ){
                quit = true;
            }
        }
        
        /*Se actaulizan las posiciones*/
        Logger::getInstance()->log(INFO, "actualice velocidades");
        step1+= speed1; 
        step2+= speed2;
        step3+= speed3;

        /*Si me voy fuera del rango de la imagen vuelvo a la posicion 0.
        Considero que todas las imagenes tiene el doble del ancho
        de la ventana. Por este motivo justo cuando la posicion incial 
        es el ancho de la ventana se estará mostrando completamente la
        segunda mitad de la imagen y no se podría dar otro paso por lo
        que vuelvo al principio. Con el objetivo de que no se note este
        salto la segunda mitad de la imagen debe der identica a la primera
        mitad. Se pueden usar imagenes más largas cambiando estos condicionales
        pero siempre el final de la imagen tiene que coincidir con
        el principio de la misma. En cuanto al alto, el mismo en todas las imagenes
        deben coincidir con el alto de la ventana para que encaje perfectamente*/
        
        if (step1>= screen_widht){
            step1=0;
        }
        if (step2>= screen_widht){
            step2=0;
        }
        if (step3>= screen_widht){
            step3=0;
        }


        /*actualizo los recortes sobre las texturas partiendo desde las nuevas
        posiciones*/
        SDL_Rect auxParallax1  = { step1, 0, screen_widht, screen_height};
        SDL_Rect auxParallax2  = { step2, 0, screen_widht, screen_height};
        SDL_Rect auxParallax3  = { step3, 0, screen_widht, screen_height};


        /* 
        ahora tomo los respectivos recortes y  los coloco
        sobre cada una de las capas de la ventana. */
        SDL_RenderClear(renderer );
        SDL_RenderCopy( renderer,layer_1_texture,&auxParallax1, &layer_1 );
        SDL_RenderCopy( renderer,layer_2_texture, &auxParallax2, &layer_2 );
        SDL_RenderCopy( renderer,layer_3_texture, &auxParallax3, &layer_3 );
        SDL_RenderPresent( renderer );
        
        

    }

    /*destruyo texturas al finalizar de mostrar*/
    SDL_DestroyTexture(layer_1_texture);
    SDL_DestroyTexture(layer_2_texture);
    SDL_DestroyTexture(layer_3_texture);
}
//GraphicsScenario::~GraphicsScenario(){};