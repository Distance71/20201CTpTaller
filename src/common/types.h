#ifndef _TYPES_H_
#define _TYPES_H_

#include <string>
#include <vector>

using namespace std;

typedef enum level {
    LEVEL_ONE = 0,
    LEVEL_TWO = 1,
    LEVEL_THREE = 2,
    LEVEL_FOUR = 3,
} level_t;

typedef enum stage {
    STAGE_ONE = 0,
    STAGE_TWO = 1,
} stage_t;

typedef enum {
    FRONT,
    BACK,
    UP,
    DOWN,
    FRONT_UP,
    FRONT_DOWN,
    BACK_DOWN,
    BACK_UP
} orientation_t;

typedef struct {
    unsigned int type;
    unsigned int quantity;
    int size_x;
    int size_y;
    string sprite;
} enemy_t;

typedef struct {
    int size_x;
    int size_y;
    string sprite;
} player_t;

typedef struct {
    unsigned int cotaInferior;
    unsigned int cotaSuperior;
} cotasCantEnemigos_t;

typedef struct {
    unsigned int width;
    unsigned int height;
} screen_t;

typedef struct {
    int axis_x;
    int axis_y;
    orientation_t orientation;
} position_t;

typedef struct {
    string layer1;
    string layer2;
    string layer3;
    string layer4;
    string layer5;
    string layer6;
    string layer7;
} stageSource_t;

typedef struct {
    stage_t stage;
    vector<enemy_t> enemies;
} stepContent_t;

typedef enum {
    PLAYER,
    ENEMY,
//    ENEMY_2,
    BACKGROUND
} elementType_t;

typedef size_t IdElement;

typedef struct {
    level_t level;
    stage_t stage;
    size_t step;
} currentStep_t;

typedef struct {
    vector<enemy_t> enemies;
    //size_t quantEnemiesType1; //Refactor this later
    //size_t quantEnemiesType2;
} stepParams_t;

typedef struct {
    stageSource_t backgroundSources;
    vector<stepParams_t> stepsParams;
    vector<enemy_t> totalEnemies;
} stageParams_t;

typedef struct {
    vector<stageParams_t> stagesParams;
} levelParams_t;

typedef struct {
    vector<levelParams_t> levelParams;
    player_t playerParams;
} gameParams_t;

typedef struct {
    string username;
    string password;
} user_t;

#endif