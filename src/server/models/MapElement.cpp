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
    this->health_ = health; 
    this->lives_ = lives;

    if((type == ENEMY_1) || (type == ENEMY_2)){
        EnemyIA* enemyia = new EnemyIA(this);
        addAction("EnemyIA", enemyia);
    }
    
    if(type == PROJECTILE){
        ProjectileIA* proyectileIA = new ProjectileIA();
        addAction("ProjectileIA", proyectileIA);
    }

    if(type == BOSS_ENEMY){
        BossIA* bossIA = new BossIA(this);
        addAction("BossIA", bossIA);
    }
    
    this->projectileKey_ = 0;
}

void MapElement::setTarget(MapElement* target) {
    if(type == ENEMY_1 || type == ENEMY_2){
        EnemyIA* enemyia = this->getAction<EnemyIA>("EnemyIA");
        enemyia->setTarget(target);
    }

    if (type == BOSS_ENEMY)
        this->getAction<BossIA>("BossIA")->addTarget(target);
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

int MapElement::reduceHealth(int damage){
    //TODO check < 0 aca? o el q lo invova?
    return this->health_ - damage;
}

int MapElement::getLives() {
    return this->lives_;
}

int MapElement::quitLives(){
    //TODO check < 0 aca? o el q lo invova?
    return this->lives_--;
}

void MapElement::setType(elementType_t type) {
    this->type = type;
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

    State* position = states_.at("Position");
    State* orientation = states_.at("Orientation");

    actualPosition.axis_x = position->getX();
    actualPosition.axis_y = position->getY();
    actualPosition.orientation = (orientation_t) orientation->getX();

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

    int screen_widht = GameProvider::getWidth();
    int screen_height = GameProvider::getHeight();

    switch (oneOrientation){
        case FRONT:        
            new_xp = xp + xs;
            orientation->setX(FRONT);
            if(new_xp <= (screen_widht - this->size_x_)){
                position->setX(new_xp);
            }
            break;

        case BACK:
            new_xp = xp - xs;
            orientation->setX(BACK);
            if(new_xp >= 0){
                position->setX(new_xp);
            }        
            break;

        case UP:
            new_yp = yp-ys;
            if (new_yp >= 0){
                position->setY(new_yp);
            }
            break;

        case DOWN:
            new_yp = yp + ys;
            if(new_yp <= (screen_height - this->size_y_)){
                position->setY(new_yp);
            } 
            break;

        case FRONT_UP:
            new_xp = xp + xs;
            new_yp = yp - ys;
            orientation->setX(FRONT);

            if (new_xp <= screen_widht - this->size_x_){
                position->setX(new_xp);
            }

            if (new_yp > 0){
                position->setY(new_yp);
            }        
            break;

        case FRONT_DOWN:
            new_xp = xp + xs;
            new_yp = yp + ys;
            orientation->setX(FRONT);

            if (new_xp <= (screen_widht - this->size_x_)){
                position->setX(new_xp);
            }

            if (new_yp <= (screen_height - this->size_y_)){
                position->setY(new_yp);
            }        
            break;

        case BACK_DOWN:
            new_xp = xp - xs;
            new_yp = yp + ys;
            orientation->setX(BACK);
            if (new_xp >= 0){
                position->setX(new_xp);
            }

            if (new_yp <= (screen_height - this->size_y_)){
                position->setY(new_yp);
            }        
            break;

        case BACK_UP:
            new_xp = xp - xs;
            new_yp = yp - ys;
            orientation->setX(BACK);

            if (new_xp >= 0 ){
                position->setX(new_xp);
            }

            if (new_yp >= 0){
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


bool MapElement::leftScreen(){

    if (this->getState<Orientation>("Orientation")->getX() == BACK){
        return (this->getState<Position>("Position")->getX() + this->size_x_ <= 0);
    }
    
    return (this->getState<Position>("Position")->getX() - this->size_x_ >= (int)GameProvider::getWidth());
}

unordered_map<Id,MapElement*> MapElement::getShoots(){
    return this->projectiles_;
};

void MapElement::eraseProjectile(Id id){
    MapElement* deadProjectile = this->projectiles_.at(id);
    delete deadProjectile;
    this->projectiles_.erase(id);
}


void MapElement::shoot(){

    projectile_t projectileData = GameProvider::getConfig()->getProjectileData();

    if (this->type == BOSS_ENEMY){
        this->shootBoss(projectileData);
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
}

void MapElement::shootBoss(projectile_t projectileData){
    position_t position = this->getActualPosition();

    int sizeY = this->size_y_;
    int positionXProjectil = position.axis_x + (this->size_x_ / 2);

    position_t middlePosition = position;
    middlePosition.axis_x = positionXProjectil;
    middlePosition.axis_y = position.axis_y + (this->size_y_ / 4); 
    MapElement *middleProjetil = new MapElement(PROJECTILE, middlePosition, 6, 6, projectileData.size_x, projectileData.size_y, 10, 1);
    this->projectiles_.emplace(this->projectileKey_ ,middleProjetil);
    this->projectileKey_++;

    position_t topPosition = position;
    topPosition.axis_x = positionXProjectil;
    topPosition.axis_y = position.axis_y + (this->size_y_ / 2); 
    MapElement *topProjetil = new MapElement(PROJECTILE, topPosition, 6, 6, projectileData.size_x, projectileData.size_y, 10, 1);
    this->projectiles_.emplace(this->projectileKey_ ,topProjetil);
    this->projectileKey_++;

    position_t bottomPosition = position;
    bottomPosition.axis_x = positionXProjectil;
    bottomPosition.axis_y = position.axis_y + 3 * (this->size_y_ / 4); 
    MapElement *bottomProjetil = new MapElement(PROJECTILE, bottomPosition, 6, 6, projectileData.size_x, projectileData.size_y, 10, 1);
    this->projectiles_.emplace(this->projectileKey_ ,bottomProjetil);
    this->projectileKey_++;
}
