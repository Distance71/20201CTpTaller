#include "BossIA.h"

BossIA::BossIA(MapElement* owner){
    this->owner_ = owner;
    timeShoot = 0;
    timeLimitShoot = 70 + RandomGenerate::generate(FRECUENCIA);
}

void BossIA::update(unordered_map<string, State *> states_){
    Logger::getInstance()->log(DEBUG, "Entro al update de Boss IA");
    State* position = states_.at("Position");
    State* speed = states_.at("Speed");
    State* orientation = states_.at("Orientation");

    //TODO implementar IA
 
    int xp = position->getX();
    int yp = position->getY();
    int xs = speed->getX();
    int ys = speed->getY();
    
    int new_xp;
    int new_yp;

    // Si todavia no aparece completo en pantalla, se setea nueva posicion en X, si no no hace nada en el eje X
    if (xp > (GameProvider::getWidth() - this->owner_->getSizeX())){
        new_xp = xp - xs;
        position->setX(new_xp);
    }

    // int randomMovement = rand()%(10);
    // int randomOrientacion = rand()%(2);

    // if (randomOrientacion == 1){
    //     randomMovement = randomMovement;
    // } else {
    //     randomMovement = - randomMovement;
    // }

    // new_yp = yp + randomMovement * ys;
    
    // if (new_yp < 0) new_yp = 0;
    // if (new_yp > (GameProvider::getHeight() - this->owner_->getSizeY())) new_yp = GameProvider::getHeight() - this->owner_->getSizeY();

    // position->setY(new_yp);
    randomShoot();
}

void BossIA::randomShoot(){
    this->timeShoot++;
    //cout<<"contador "<<this->timeShoot<< endl;
    if (this->timeShoot > this->timeLimitShoot)
    {
       this->owner_->shoot();
       this->timeShoot = 0;
       this->timeLimitShoot = 70 + RandomGenerate::generate(FRECUENCIA);
    }
}