#ifndef _MAP_ELEMENT_H_
#define _MAP_ELEMENT_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../../common/models/State.h"
#include "../../common/models/Action.h"
#include "../../common/models/Orientation.h"
#include "../../common/models/Position.h"
#include <stdexcept>
#include "Speed.h"
#include "../../common/types.h"
#include "PlayerController.h"
#include "EnemyIA.h"
#include "ProjectileIA.h"
#include "BossIA.h"
#include "CollisionRectangle.h"

// Al Config?
#define DAMAGE_ENEMY_1 15
#define DAMAGE_ENEMY_2 25
#define DAMAGE_ENEMY_BOSS 35
#define DAMAGE_PLAYER 50

#define SCORE_KILLED_ENEMY_1 500
#define SCORE_KILLED_ENEMY_2 1000
#define SCORE_KILLED_ENEMY_BOSS 2000
#define SCORE_KILLED_PLAYER 0 // No influiria este valor

using namespace std;

class MapElement {

    private:
        Id id_;
        elementType_t type;
        unordered_map<string, State *> states_;
        unordered_map<string, Action *> actions_;
        unordered_map<Id,MapElement*> projectiles_; 
        Id projectileKey_;
        int size_x_;
        int size_y_;

        int lives_;
        int maxHealth_;
        int health_;
        int damage_;
        int scoreWhenKilled_;

        int scoreCurrent_;
        int scoreAcc_;

        bool isTemporaryImmune_;
        int countImmune_;

        gameMode_t gameMode_;

        vector<Action *> getActions();
        vector<State *> getStates();

        void shootNormal(projectile_t projectileData);
        void shootBoss(projectile_t projectileData);
        
        bool isImmune();
        void setTemporaryImmunity();
        void quitTemporaryImmunity();
        void setTypeDead();

    public:
        MapElement(elementType_t type, position_t position_, int x_speed, int y_speed, int size_x, int size_y, int health, int lives=1);
        ~MapElement(); 
       
        template<typename T> void addState(const string name, T *t);
        template<typename T> void addAction(const string name, T *t);
        template<typename T> T* getState(const string name);
        template<typename T> T* getAction(const string name);
        
        void update();
        void setTarget(MapElement* target);
        position_t getActualPosition();
        string getImageSource();
        
        int getHealth();
        bool reduceHealth(int damage);
        int getLives();
        void quitLives();
        int getSizeX();
        int getSizeY();
        bool isDead();
        bool isDisconnected();
        bool shouldGraphed();

        int getDamage();
        int getScoreWhenKilled();

        void addScore(int score);
        int getScoreAcc();
        int getCurrentScore();
        void cleanCurrentScore();

        elementType_t getType();
        void setType(elementType_t type);

        void moveTo(orientation_t oneOrientation); 
        void changeGameMode();
        void setGameMode(gameMode_t newGameMode);
        gameMode_t getGameMode();

        unordered_map<Id,MapElement*> getShoots();   
        void shoot();
        void cleanShoots();

        void setIdElement(Id oneIdElement);
        Id getIdElement();
        bool leftScreen();
        bool checkCollision(MapElement* mapElement);
        void attackTo(MapElement* mapElement);
        /*void checkPlayerProyectileToEnemiesCollisions(unordered_map<Id, MapElement*> mapElements, MapElement* projectile);
        void checkEnemyToPlayersCollisions(unordered_map<string, MapElement*> players);
        void checkEnemyProyectileToPlayersCollisions(unordered_map<string, MapElement*> players, MapElement* projectile);
        bool checkPlayerToEnemyCollision(MapElement* mapElement);*/
        CollisionRectangle* getCollisionRectangle();
        void eraseProjectile(Id id);
};

template<typename T>
void MapElement::addState(const string name, T *state) {
    states_[name] = (State *) state;
}

template<typename T>
T* MapElement::getState(const string name) {
    return (T *) states_[name];
}

template<typename T>
void MapElement::addAction(const string name, T *action) {
    actions_[name] = (Action *) action;
}

template<typename T>
T* MapElement::getAction(const string name) {
    return (T *) actions_[name];
}

#endif