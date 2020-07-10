#include "EventInitStage.h"

Message* EventInitStage::serialize() {
    return (Message *) new MessageInitStage(this->layerPaths_);
}

void EventInitStage::update() {
  if (!this->context_){
    Logger::getInstance()->log(DEBUG, "No hay contexto para el evento EventInitStage");
  }
  
  else{
    stageSource_t background;
    
    background.layer1 = this->layerPaths_[0];
    background.layer2 = this->layerPaths_[1];
    background.layer3 = this->layerPaths_[2];
    background.layer4 = this->layerPaths_[3];
    background.layer5 = this->layerPaths_[4];
    background.layer6 = this->layerPaths_[5];
    background.layer7 = this->layerPaths_[6];

    Client* client = (Client *) Event::context_;
    
    client->setBackground(background);

    Logger::getInstance()->log(DEBUG, "Se ejecutó el evento EventInitStage");
  }
}