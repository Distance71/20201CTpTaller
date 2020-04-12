#include "SDL.h"
#include "game.h"
#include "providers/GameProvider.h"

Game::Game(){
    initializeGraphics();
}

Game::~Game(){
    GameProvider::getLogger()->log(INFO, "Fin del juego");
}

void Game::initializeGraphics() {
    GameProvider::getLogger()->log(DEBUG, "Se inicializan los graficos de render");

    //Inicializo SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        GameProvider::getLogger()->log(ERROR, string("Error al inicializar SDL! Error: ").append(SDL_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return;
    }

    window = SDL_CreateWindow("Gley Lancer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(!window) {
        GameProvider::getLogger()->log(ERROR, string("Error al crear la ventana! SDL_Error: ").append(SDL_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return;
    }

    renderer_ = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer_) {
        GameProvider::getLogger()->log(ERROR, string("Error al crear el renderer SDL! Error: ").append(SDL_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return;
    }
}