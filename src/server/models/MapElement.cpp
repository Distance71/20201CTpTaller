#include "MapElement.h"

MapElement::MapElement(elementType_t type, position_t position_, int x_speed, int y_speed, int size_x, int size_y, int health, int lives){
    Position* position =new Position(position_.axis_x, position_.axis_y);
    Speed* speed = new Speed(x_speed,y_speed);
    Orientation* orientation = new Orientation(position_.orientation, 0);
    addState("Position", position);
    addState("Speed", speed);
    addState("Orientation", orientation);
    
    this->size_x_ = size_x;
    this->size_y_ = size_y;
    this->type = type; 
    this->maxHealth_ = health;
    this->health_ = health; 
    this->lives_ = lives;
    this->gameMode_ = MODE_NORMAL_GAME;

    if(type == ENEMY_1){
        EnemyIA* enemyia = new EnemyIA(this);
        addAction("EnemyIA", enemyia);
        this->damage_ = DAMAGE_ENEMY_1;
        this->scoreWhenKilled_ = SCORE_KILLED_ENEMY_1;

    } else if(type == ENEMY_2){
        EnemyIA* enemyia = new EnemyIA(this);
        addAction("EnemyIA", enemyia);
        this->damage_ = DAMAGE_ENEMY_2;
        this->scoreWhenKilled_ = SCORE_KILLED_ENEMY_2;

    } else if(type == PROJECTILE || type == PROJECTILE_BOSS){
        ProjectileIA* proyectileIA = new ProjectileIA();
        addAction("ProjectileIA", proyectileIA);
        this->damage_ = 0;
        this->scoreWhenKilled_ = 0;

    } else if(type == BOSS_ENEMY){
        BossIA* bossIA = new BossIA(this);
        addAction("BossIA", bossIA);
        this->damage_ = DAMAGE_ENEMY_BOSS;
        this->scoreWhenKilled_ = SCORE_KILLED_ENEMY_BOSS;
    
    } else {
        // Es Player
        this->damage_ = DAMAGE_PLAYER;
        this->scoreWhenKilled_ = SCORE_KILLED_PLAYER;
    }
    
    this->scoreCurrent_ = 0;
    this->scoreAcc_ = 0;

    this->projectileKey_ = 0;

    this->countImmune_ = 0;
    this->isTemporaryImmune_ = false;
}

void MapElement::setTarget(MapElement* target) {
    if(type == ENEMY_1 || type == ENEMY_2){
        EnemyIA* enemyia = this->getAction<EnemyIA>("EnemyIA");
        enemyia->setTarget(target);
    }

    if (type == BOSS_ENEMY && target->getLives() != 0) 
        this->getAction<BossIA>("BossIA")->addTarget(target);


    if (type == PROJECTILE || type == PROJECTILE_BOSS)
        this->getAction<ProjectileIA>("ProjectileIA")->setOwn(target);

}

MapElement::~MapElement() {
    
    for (auto oneState : this->states_){
        delete oneState.second;
    }

    for (auto oneAction : this->actions_){
        delete oneAction.second;
    }
}

int MapElement::getSizeX(){
    return this->size_x_;
}

int MapElement::getSizeY(){
    return this->size_y_;
}

vector<Action *> MapElement::getActions() {
    vector<Action *> actions(actions_.size());
    auto action_selector = [](auto pair) { return pair.second; };
    transform(actions_.begin(), actions_.end(), actions.begin(), action_selector);
    return actions;
}

elementType_t MapElement::getType() {
    return this->type;
}

int MapElement::getHealth() {
    return this->health_;
}

bool MapElement::reduceHealth(int damage){
    
    this->health_ -= damage;

    if (this->health_ <= 0)
        this->quitLives();

    return this->isDead();
}

bool MapElement::isDead(){
    return ((this->lives_ <= 0) && (this->health_ <= 0));
}

bool MapElement::isDisconnected(){
    
    switch (this->type) {
        case PLAYER_1_OUT:
            return true;

        case PLAYER_2_OUT:
            return true;

        case PLAYER_3_OUT:
            return true;

        case PLAYER_4_OUT:
            return true;
        
    }

    return false;
}

int MapElement::getLives() {
    return this->lives_;
}

void MapElement::quitLives(){

    if (this->isImmune())
        return;

    this->lives_--;

    if (this->lives_ <= 0) {
        this->lives_ = 0;
        this->health_ = 0;
    } else {
        this->health_ = maxHealth_;
    }

    if ((this->type == PLAYER_1) || (this->type == PLAYER_2) || (this->type == PLAYER_3) || (this->type == PLAYER_4)){
        this->setTemporaryImmunity();
    }
}

void  MapElement::setTypeDead(){

    switch (this->type){
        case PLAYER_1:
            this->setType(PLAYER_1_DEAD);
            break;
        case PLAYER_2:
            this->setType(PLAYER_2_DEAD);
            break;
        case PLAYER_3:
            this->setType(PLAYER_3_DEAD);
            break;
        case PLAYER_4:
            this->setType(PLAYER_4_DEAD);
            break;
    }
}

int MapElement::getDamage(){
    return this->damage_;
}

int MapElement::getScoreWhenKilled(){
    return this->scoreWhenKilled_;
}

void MapElement::addScore(int score){

    this->scoreCurrent_ += score;
    this->scoreAcc_ += score;
}

int MapElement::getScoreAcc(){
    return this->scoreAcc_;
}

void MapElement::cleanCurrentScore(){
    this->scoreCurrent_ = 0;
}

int MapElement::getCurrentScore(){
    return this->scoreCurrent_;
}

void MapElement::setType(elementType_t type) {
    this->type = type;
}

void MapElement::changeGameMode(){

    if (this->gameMode_ == MODE_NORMAL_GAME)
        this->gameMode_ = MODE_TEST_GAME;
    else
        this->gameMode_ = MODE_NORMAL_GAME;
    
}

void MapElement::setGameMode(gameMode_t newGameMode){
    this->gameMode_ = newGameMode;
};

gameMode_t MapElement::getGameMode(){
    return this->gameMode_;
}

vector<State *> MapElement::getStates() {
    vector<State *> states(states_.size());
    auto state_selector = [](auto pair) { return pair.second; };
    transform(states_.begin(), states_.end(), states.begin(), state_selector);
    return states;
}

void MapElement::setIdElement(Id oneIdElement){
    this->id_ = oneIdElement;
}

Id MapElement::getIdElement(){
    return this->id_;
}

void MapElement::update(){

    for(auto projectile : projectiles_){
        projectile.second->update();
    }

    for(auto action : actions_){
        action.second->update(states_); 
    }

}

position_t MapElement::getActualPosition(){
    position_t actualPosition;

    try {
        State* position = states_.at("Position");
        State* orientation = states_.at("Orientation");

        actualPosition.axis_x = position->getX();
        actualPosition.axis_y = position->getY();
        actualPosition.orientation = (orientation_t) orientation->getX();
    }
    catch(const std::out_of_range& oor) {
        std::cerr << "Out of Range error in MapElement getActualPosition: " << oor.what() << '\n'; 
    }
    return actualPosition;
}

void MapElement::moveTo(orientation_t oneOrientation){
    
    State* position = states_.at("Position");
    State* speed = states_.at("Speed");
    State* orientation = states_.at("Orientation");
    int xp = position->getX();
    int yp = position->getY();
    int xs = speed->getX();
    int ys = speed-> getY();

    int new_xp;
    int new_yp;

    gameZone_t zone = GameProvider::getGameZone();

    switch (oneOrientation){
        case FRONT:        
            new_xp = xp + xs;
            orientation->setX(FRONT);
            if(new_xp <= (zone.xEnd - this->size_x_)){
                position->setX(new_xp);
            }
            break;

        case BACK:
            new_xp = xp - xs;
            orientation->setX(BACK);
            if(new_xp >= zone.xInit){
                position->setX(new_xp);
            }        
            break;

        case UP:
            new_yp = yp-ys;
            if (new_yp >= zone.yInit){
                position->setY(new_yp);
            }
            break;

        case DOWN:
            new_yp = yp + ys;
            if(new_yp <= (zone.yEnd - this->size_y_)){
                position->setY(new_yp);
            } 
            break;

        case FRONT_UP:
            new_xp = xp + xs;
            new_yp = yp - ys;
            orientation->setX(FRONT);

            if (new_xp <= zone.xEnd - this->size_x_){
                position->setX(new_xp);
            }

            if (new_yp > zone.yInit){
                position->setY(new_yp);
            }        
            break;

        case FRONT_DOWN:
            new_xp = xp + xs;
            new_yp = yp + ys;
            orientation->setX(FRONT);

            if (new_xp <= (zone.xEnd - this->size_x_)){
                position->setX(new_xp);
            }

            if (new_yp <= (zone.yEnd - this->size_y_)){
                position->setY(new_yp);
            }        
            break;

        case BACK_DOWN:
            new_xp = xp - xs;
            new_yp = yp + ys;
            orientation->setX(BACK);
            if (new_xp >= zone.xInit){
                position->setX(new_xp);
            }

            if (new_yp <= (zone.yEnd - this->size_y_)){
                position->setY(new_yp);
            }        
            break;

        case BACK_UP:
            new_xp = xp - xs;
            new_yp = yp - ys;
            orientation->setX(BACK);

            if (new_xp >= zone.xInit ){
                position->setX(new_xp);
            }

            if (new_yp >= zone.yInit){
                position->setY(new_yp);
            }        
            break;
    }
}

CollisionRectangle* MapElement::getCollisionRectangle(){
    position_t position = this->getActualPosition();
    CollisionRectangle* rectangle = new CollisionRectangle(position.axis_x, position.axis_y,position.axis_x + this->getSizeX(), position.axis_y + this->getSizeY());
    return rectangle;
}

bool MapElement::checkCollision(MapElement* mapElement){
    CollisionRectangle* myRectangle = this->getCollisionRectangle();
    CollisionRectangle* otherRectangle = mapElement->getCollisionRectangle();
    bool result = myRectangle->isCollision(otherRectangle);
    delete myRectangle;
    delete otherRectangle;
    return result;
}

void MapElement::attackTo(MapElement* mapElementAttacked){

    if (mapElementAttacked->isImmune())
        return;

    int damageProduced = this->getDamage();
    bool kill = mapElementAttacked->reduceHealth(damageProduced);

    if (kill){
        int scoreFinal = mapElementAttacked->getScoreWhenKilled();
        this->addScore(scoreFinal);
    }

}

bool MapElement::leftScreen(){

    gameZone_t zone = GameProvider::getGameZone();

    if (this->getState<Orientation>("Orientation")->getX() == BACK){
        return (this->getState<Position>("Position")->getX() + this->size_x_ <= 0);
    }
    
    return (this->getState<Position>("Position")->getX() - this->size_x_ >= zone.xEnd);
}

unordered_map<Id,MapElement*> MapElement::getShoots(){
    return this->projectiles_;

};

void MapElement::eraseProjectile(Id id){
    
    try {
        MapElement* deadProjectile = this->projectiles_.at(id);
        this->projectiles_.erase(id);
        delete deadProjectile;
    }
    
    catch (const std::out_of_range& oor){
        std::cerr << "Out of Range error in MapElement eraseProjectile: " << oor.what() << '\n';
    }
}

bool MapElement::isImmune(){
    return ((this->gameMode_ == MODE_TEST_GAME) || (this->isTemporaryImmune_));
}

void MapElement::setTemporaryImmunity(){
    this->countImmune_ = 120;
    this->isTemporaryImmune_ = true;
}

void MapElement::quitTemporaryImmunity(){
    this->isTemporaryImmune_ = false;
    this->countImmune_ = 0;
}

bool MapElement::shouldGraphed(){

    if (this->isTemporaryImmune_){

        this->countImmune_--;

        if (this->countImmune_ < 0)
            this->quitTemporaryImmunity();
    
    }    

    return ((this->countImmune_ % 2) == 0);
}

void MapElement::shoot(){

    projectile_t projectileData = GameProvider::getConfig()->getProjectileData();

    if (this->type == BOSS_ENEMY){
        projectile_t projectileBossData = GameProvider::getConfig()->getProjectileBossData();
        this->shootBoss(projectileBossData);
        return;
    }

    this->shootNormal(projectileData);

};

void MapElement::cleanShoots(){
    
    for (auto oneProjectile : this->projectiles_)
        delete oneProjectile.second;
    
    this->projectiles_.clear();
}


void MapElement::shootNormal(projectile_t projectileData){
    position_t position = this->getActualPosition();
    position.axis_x = position.axis_x + (this->size_x_ / 2);
    position.axis_y = position.axis_y + (this->size_y_ / 2); 

    MapElement *oneProjetil = new MapElement(PROJECTILE, position, 6, 6, projectileData.size_x, projectileData.size_y, 10, 1);
    this->projectiles_.emplace(this->projectileKey_ ,oneProjetil);
    this->projectileKey_ ++;

    oneProjetil->setTarget(this);
}

void MapElement::shootBoss(projectile_t projectileData){
    position_t position = this->getActualPosition();

    int sizeY = this->size_y_;
    int positionXProjectil = position.axis_x + (this->size_x_ / 2);

    position_t middlePosition = position;
    middlePosition.axis_x = positionXProjectil;
    middlePosition.axis_y = position.axis_y + (this->size_y_ / 4); 
    MapElement *middleProjetil = new MapElement(PROJECTILE_BOSS, middlePosition, 6, 6, projectileData.size_x, projectileData.size_y, 10, 1);
    this->projectiles_.emplace(this->projectileKey_ ,middleProjetil);
    this->projectileKey_++;
    middleProjetil->setTarget(this);

    position_t topPosition = position;
    topPosition.axis_x = positionXProjectil;
    topPosition.axis_y = position.axis_y + (this->size_y_ / 2); 
    MapElement *topProjetil = new MapElement(PROJECTILE_BOSS, topPosition, 6, 6, projectileData.size_x, projectileData.size_y, 10, 1);
    this->projectiles_.emplace(this->projectileKey_ ,topProjetil);
    this->projectileKey_++;
    topProjetil->setTarget(this);

    position_t bottomPosition = position;
    bottomPosition.axis_x = positionXProjectil;
    bottomPosition.axis_y = position.axis_y + 3 * (this->size_y_ / 4); 
    MapElement *bottomProjetil = new MapElement(PROJECTILE_BOSS, bottomPosition, 6, 6, projectileData.size_x, projectileData.size_y, 10, 1);
    this->projectiles_.emplace(this->projectileKey_ ,bottomProjetil);
    this->projectileKey_++;
    bottomProjetil->setTarget(this);
}
