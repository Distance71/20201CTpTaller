#include "EnemyIA.h"

EnemyIA::EnemyIA(MapElement* owner){
    owner_ = owner;
    timeShoot = 0;
    timeLimitShoot = 70 + RandomGenerate::generate(FRECUENCIA);
    timeLimitRandomMovement = 40 + RandomGenerate::generate(FRECUENCIA);
    lastMovement = 2;
}

void EnemyIA::setTarget(MapElement* target){
    target_ = target;
}

void EnemyIA::setGame(Game *game){
    this->game_ = game;
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
    gameZone_t zone = GameProvider::getGameZone();
    
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

        if (zone.xEnd > xp && xp > this->owner_->getSizeX()) randomShoot();        
        return;
    }

    //si tiene objetivo:
    position_t ubicacion = this->target_->getActualPosition();

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

    // Si no esta en la pantalla q no dispare y no persiga 
    if (xp < this->owner_->getSizeX() || zone.xEnd < xp) return;    

    //eje y persigue al target hasta sobrepasarlo
/*     if (!abort) {
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
    }     */    

    randomShoot();
    new_yp = randomMovement(yp, ys, ubicacion);
    
    // si no hubo cambios en el eje Y o se quiere salir de la pantalla evita actualizar el eje Y
    if ((abort && new_yp == yp) || new_yp < zone.yInit || new_yp > zone.yEnd - this->owner_->getSizeY()) { return;}  
    position->setY(new_yp);
    
}

void EnemyIA::randomShoot(){
    this->timeShoot++;
    
    if (this->timeShoot > this->timeLimitShoot)
    {
       this->owner_->shoot();
       this->timeShoot = 0;
       this->timeLimitShoot = 70 + RandomGenerate::generate(FRECUENCIA);
       this->game_->sendEvent(new EventMusicUpdate(ENEMY_SHOT));
    }
}

int EnemyIA::randomMovement(int yp, int ys, position_t ubicacion){

    int opcion = this->lastMovement;

    this->timeRandomMovement++;
    
    if (this->timeRandomMovement > this->timeLimitRandomMovement)
    {
        switch (RandomGenerate::generate(100))
        {
        case 1 ... 25:
            opcion = 0;
            break;
        case 75 ... 100:
            opcion = 1;
            break;
        
        default:
            opcion = 2;
            break;
        }
        this->lastMovement = opcion;
        this->timeRandomMovement = 0;
        this->timeLimitRandomMovement = 40 + RandomGenerate::generate(FRECUENCIA);
    }

    switch(opcion)
    {
    case 0:
        return yp + ys;
        break;
    case 1:
        return yp - ys;
        break;
    case 2:
        if (yp < ubicacion.axis_y){
            return yp + ys;
        } else {
            if (yp > ubicacion.axis_y){
                return yp - ys;
            }
        }
        break;
    
    default:
        return yp;
        break;
    }
}