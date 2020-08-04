#include "EnemyIA.h"

EnemyIA::EnemyIA(MapElement* owner){
    owner_ = owner;
    timeShoot = 0;
    timeLimitShoot = 70 + RandomGenerate::generate(FRECUENCIA);
}

void EnemyIA::setTarget(MapElement* target){
    target_ = target;
}

void EnemyIA::update(unordered_map<string, State *> states_){
    Logger::getInstance()->log(DEBUG, "Entro al update de Enemy IA");
    State* position = states_.at("Position");
    State* speed = states_.at("Speed");
    State* orientation = states_.at("Orientation");

    int xp = position->getX();
    int yp = position->getY();
    int xs = speed->getX();
    int ys = speed->getY();
    
    int new_xp;
    int new_yp;
    bool abort = false;

    //TODO check si target esta muerto o se desconecto
    //si perdio el objetivo:
    if (this->target_ == nullptr) {
        if (orientation->getX() == FRONT){
            new_xp = xp + xs;
        } else {
            new_xp = xp - xs;
        }
        position->setX(new_xp);
        randomShoot();        
        return;
    }

    //si tiene objetivo:
    auto ubicacion = this->target_->getActualPosition();

    // eje x siempre constante
    if (orientation->getX() == FRONT){
        new_xp = xp + xs;
        if(xp >= ubicacion.axis_x){
            abort = true;
        }
    } else {
        new_xp = xp - xs;
        if(xp <= ubicacion.axis_x){
            abort = true;
        }
    }
    
    position->setX(new_xp);

    // Si no esta en la pantalla q no dispare y no persiga (80 es casi el largo del enemigo)
    int screen_width = GameProvider::getWidth();
    if (xp < 80 || screen_width < xp) return;    

    //eje y persigue al target hasta sobrepasarlo
    if (!abort) {
        if (yp < ubicacion.axis_y){
            new_yp = yp + ys;
        } else {
            if (yp > ubicacion.axis_y){
                new_yp = yp - ys;
            }
        }
    } else {
        // habria q agregarle el factor tiempo para mejorar el comportamiento (vale la pena?)
        //new_yp = randomMovement(yp, ys);
    }
        

    randomShoot();
    int screen_height = GameProvider::getHeight();
    if ((abort && new_yp == yp) || new_yp < 0 || new_yp > screen_height - this->owner_->getSizeY()) { return;}  
    position->setY(new_yp);
    
}

void EnemyIA::randomShoot(){
    this->timeShoot++;
    //cout<<"contador "<<this->timeShoot<< endl;
    if (this->timeShoot > this->timeLimitShoot)
    {
       this->owner_->shoot();
       this->timeShoot = 0;
       this->timeLimitShoot = 70 + RandomGenerate::generate(FRECUENCIA);
    }
}

int EnemyIA::randomMovement(int yp, int ys){

    switch (RandomGenerate::generate(100))
    {
    case 1 ... 20:
        return yp + ys;
        break;
    case 80 ... 100:
         return yp - ys;
        break;
    
    default:
        return yp;
        break;
    }


}