#include "GraphicsScenario.h"

GraphicsScenario::GraphicsScenario(stageSource_t background){
    /*Creo las variables donde se cargaran  las rutas de las imagenes dependiendo el nivel*/
    /*Leo las imagenes segun el nivel*/
    string layer1Path = background.layer1;
    string layer2Path = background.layer2;
    string layer3Path = background.layer3;
    string layer4Path = background.layer4;
    string layer5Path = background.layer5;
    string layer6Path = background.layer6;
    string layer7Path = background.layer7;

    if (layer1Path != "")
        sprites_.push_back(new Sprite(layer1Path));
        
    if (layer2Path != "")
        sprites_.push_back(new Sprite(layer2Path));

    if (layer3Path != "")
        sprites_.push_back(new Sprite(layer3Path));

    if (layer4Path != "")
        sprites_.push_back(new Sprite(layer4Path));

    if (layer5Path != "")
        sprites_.push_back(new Sprite(layer5Path));

    if (layer6Path != "")
        sprites_.push_back(new Sprite(layer6Path));

    if (layer7Path != "")
        sprites_.push_back(new Sprite(layer7Path));

    /* velocidad con que se mueven las capas*/
    unordered_map<layer_t, size_t> layersSpeeds = GameProvider::getLayersSpeeds();
    layersSpeeds_.push_back(new Speed(layersSpeeds[LAYER_1], 0));
    layersSpeeds_.push_back(new Speed(layersSpeeds[LAYER_2], 0));
    layersSpeeds_.push_back(new Speed(layersSpeeds[LAYER_3], 0));
    layersSpeeds_.push_back(new Speed(layersSpeeds[LAYER_4], 0));
    layersSpeeds_.push_back(new Speed(layersSpeeds[LAYER_5], 0));
    layersSpeeds_.push_back(new Speed(layersSpeeds[LAYER_6], 0));
    layersSpeeds_.push_back(new Speed(layersSpeeds[LAYER_7], 0));

    layersPositions_.push_back(new Position(0, 0));
    layersPositions_.push_back(new Position(0, 0));
    layersPositions_.push_back(new Position(0, 0));
    layersPositions_.push_back(new Position(0, 0));
    layersPositions_.push_back(new Position(0, 0));
    layersPositions_.push_back(new Position(0, 0));
    layersPositions_.push_back(new Position(0, 0));

}

void GraphicsScenario::update(){
    size_t screenWidht = GameProvider::getWidth();
    size_t screenHeight = GameProvider::getHeight();

    SDL_Renderer *renderer = GameProvider::getRenderer();

    SDL_Rect layer = { 0,0,(int)screenWidht, (int)screenHeight};

    for(size_t i = 0; i < sprites_.size(); i++) {
        SDL_Texture* layerTexture = sprites_[i]->getTexture();
        int step = layersPositions_[i]->getX();
        step += layersSpeeds_[i]->getX();
        if (step >= screenWidht) {
            layersPositions_[i]->setX(0);
            step = 0;
        }
        layersPositions_[i]->setX(step);
            
        SDL_Rect auxParallax = { step, 0, (int)screenWidht, (int)screenHeight};
    
        renderElement_t renderElement;
        renderElement.spriteTexture = layerTexture;
        renderElement.srcRect = auxParallax;
        renderElement.dstRect = layer;
        renderElement.orientation = FRONT;
        renderElement.isMap = true;

        SDL_RenderCopy(renderer, layerTexture, &auxParallax, NULL);
    }
}

GraphicsScenario::~GraphicsScenario(){
    for(auto sprite: this->sprites_)
        delete sprite;
    
    for(auto layerSpeed: this->layersSpeeds_)
        delete layerSpeed;
    
    for(auto layersPosition: this->layersPositions_)
        delete layersPosition;
}