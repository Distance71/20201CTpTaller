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

    unsigned int screenHeight = GameProvider::getHeight();
 
    int xp = position->getX();
    int yp = position->getY();
    int xs = speed->getX();
    int ys = speed->getY();
    
    int new_xp;
    int new_yp;

    // Si todavia no aparece completo en pantalla, se setea nueva posicion en X, si no no hace nada en el eje X
    if (xp > (GameProvider::getWidth() - this->owner_->getSizeX() - 40)){
        new_xp = xp - xs;
        position->setX(new_xp);
    }

    new_yp = doMovement(yp, ys);
    
    if (new_yp < this->owner_->getSizeY()/2) new_yp = this->owner_->getSizeY()/2;
    if (new_yp > (screenHeight - this->owner_->getSizeY())) new_yp = screenHeight - this->owner_->getSizeY();

    position->setY(new_yp);
 
    randomShoot();
}

void BossIA::addTarget(MapElement* target){
    this->targets_.push_back(target);
}

void BossIA::setGame(Game *game){
    this->game_ = game;
}

void BossIA::randomShoot(){
    this->timeShoot++;
    
    if (this->timeShoot > this->timeLimitShoot)
    {
       this->owner_->shoot();
       this->timeShoot = 0;
       this->timeLimitShoot = 50 + RandomGenerate::generate(FRECUENCIA);
       this->game_->sendEvent(new EventMusicUpdate(BOSS_SHOT));
    }
}

int BossIA::doMovement(int yp, int ys){

    //if (RandomGenerate::generate(10) < 5)
        return this->searchPlayers(yp, ys);

    //return this->randomMovement(yp, ys);
}

int BossIA::searchPlayers(int yp, int ys){
    //tal vez no deberia pasar nunca este caso
    if (this->targets_.size() == 0) return yp;
    
    int sumPosY = 0,
        nTargets = 0,
        avgPosY = GameProvider::getWidth() / 2,
        randomMovement = RandomGenerate::generate(5);

    for (auto onePlayer : this->targets_){
        if (onePlayer->getLives() != 0) {
            position_t position = onePlayer->getActualPosition();
            sumPosY += position.axis_y;
            nTargets++;
        }
    }

    if (sumPosY)
        avgPosY = (sumPosY / nTargets) - (this->owner_->getSizeY()/2) ;

    if (yp == avgPosY) return yp; //si ya esta centrado q no le agarre epilepsia
    if (yp < avgPosY)
        return yp + ys;

    return yp - ys;
}


//NO USAR
int BossIA::randomMovement(int yp, int ys){
    
    unsigned int screenHeight = GameProvider::getHeight();
    int randomMovement = RandomGenerate::generate(5);

    switch (RandomGenerate::generate(100)) {
        case 1 ... 20:
            return yp + randomMovement * ys;
            break;
        case 80 ... 100:
            return yp - randomMovement * ys;
            break;
        
        default:

            if (yp < 0.25 * screenHeight)
                return yp + randomMovement * ys;

            if (yp > 0.75 * screenHeight)
                return yp - randomMovement * ys;

            return yp;
            break;
    }


}