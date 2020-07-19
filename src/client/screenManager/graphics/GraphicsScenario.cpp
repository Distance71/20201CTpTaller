#include "GraphicsScenario.h"

GraphicsScenario::GraphicsScenario(stageSource_t background){
    string layer1Path = background.layer1;
    string layer2Path = background.layer2;
    string layer3Path = background.layer3;
    string layer4Path = background.layer4;
    string layer5Path = background.layer5;
    string layer6Path = background.layer6;
    string layer7Path = background.layer7;

    if (layer1Path != "")
        sprites_[LAYER_1] = new Sprite(layer1Path);
        
    if (layer2Path != "")
        sprites_[LAYER_2] = new Sprite(layer2Path);

    if (layer3Path != "")
        sprites_[LAYER_3] = new Sprite(layer3Path);

    if (layer4Path != "")
        sprites_[LAYER_4] = new Sprite(layer4Path);

    if (layer5Path != "")
        sprites_[LAYER_5] = new Sprite(layer5Path);

    if (layer6Path != "")
        sprites_[LAYER_6] = new Sprite(layer6Path);

    if (layer7Path != "")
        sprites_[LAYER_7] = new Sprite(layer7Path);
}

void GraphicsScenario::update(layer_t layer, int step){
    size_t screenWidht = GameProvider::getWidth();
    size_t screenHeight = GameProvider::getHeight();

    cout << "acceso" << layer << endl;

    SDL_Renderer *renderer = GameProvider::getRenderer();

    //SDL_Texture* layerTexture = this->sprites_[LAYER_4]->getTexture();
    if(sprites_[layer] != NULL) {
        SDL_Texture* layerTexture = sprites_[layer]->getTexture();
        SDL_Rect auxParallax = { step, 0, (int)screenWidht, (int)screenHeight};

        SDL_RenderCopy(renderer, layerTexture, &auxParallax, NULL);
    }
}

GraphicsScenario::~GraphicsScenario(){
    for(auto sprite: this->sprites_)
        delete sprite.second;
}