#include "GraphicsScenario.h"

GraphicsScenario::GraphicsScenario(level_t level){
    /*Creo las variables donde se cargaran  las rutas de las imagenes dependiendo el nivel*/
    /*Leo las imagenes segun el nivel*/
    string layer1Path= "";
    string layer2Path = "";
    string layer3Path = "";
    stage_t stageData;

    switch(level){
        case LEVEL_ONE:
            stageData = GameProvider::getConfig()->getStageData(LEVEL_ONE);
            layer1Path = stageData.layer1;
            layer2Path = stageData.layer2;
            layer3Path = stageData.layer3;
            break;
        
        default:
            Logger::getInstance()->log(ERROR, string("No existe el nivel seleccionado. No se puedo acceder a las rutas de las capas del escenario"));
            GameProvider::setErrorStatus("No existe el nivel seleccionado. No se pudo acceder a las rutas de las capas del escenario" );
            return;
    }   

    sprites_.push_back(new Sprite(layer1Path));
    sprites_.push_back(new Sprite(layer2Path));
    sprites_.push_back(new Sprite(layer3Path));

    /* velocidad con que se mueven las capas*/
    unordered_map<layer_t, size_t> layersSpeeds = GameProvider::getLayersSpeeds();
    layersSpeeds_.push_back(new Speed(layersSpeeds[LAYER_1], 0));
    layersSpeeds_.push_back(new Speed(layersSpeeds[LAYER_2], 0));
    layersSpeeds_.push_back(new Speed(layersSpeeds[LAYER_3], 0));

    layersPositions_.push_back(new Position(0, 0));
    layersPositions_.push_back(new Position(0, 0));
    layersPositions_.push_back(new Position(0, 0));

}

void GraphicsScenario::update(){
    SDL_Renderer* renderer = GameProvider::getRenderer();
    size_t screenWidht = GameProvider::getWidth();
    size_t screenHeight = GameProvider::getHeight();


    SDL_RenderClear(renderer);
    SDL_Rect layer = { 0,0,(int)screenWidht, (int)screenHeight};

    for(size_t i = 0; i < sprites_.size(); i++) {
        SDL_Texture* layerTexture = sprites_[i]->getTexture();
        int step = layersPositions_[i]->getXPosition();
        step += layersSpeeds_[i]->getXSpeed();
        if (step >= screenWidht) {
            layersPositions_[i]->setXPosition(0);
            step = 0;
        }
        layersPositions_[i]->setXPosition(step);
            
        SDL_Rect auxParallax = { step, 0, (int)screenWidht, (int)screenHeight};
    
        SDL_RenderCopy(renderer, layerTexture, &auxParallax, &layer );
    }

    GameProvider::setRenderer(renderer);
}