#ifndef _TYPES_H_
#define _TYPES_H_

#include <string>
#include <vector>

using namespace std;

typedef enum level {
    LEVEL_ONE = 0,
    LEVEL_TWO = 1,
} level_t;

typedef enum stage {
    STAGE_ONE = 0,
    STAGE_TWO = 1,
} stage_t;

typedef struct {
    unsigned int type;
    unsigned int quantity;
    string sprite;
} enemy_t;

typedef struct {
    string layer1;
    string layer2;
    string layer3;
} stageSource_t;

typedef struct {
    stage_t stage;
    vector<enemy_t> enemies;
} stepContent_t;

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

typedef enum {
    PLAYER,
    ENEMY,
    BACKGROUND
} elementType_t;

typedef size_t IdElement;

typedef struct {
    level_t level;
    stage_t stage;
    size_t step;
} currentStep_t;

typedef struct {
    size_t quantEnemiesType1; //Refactor this later
    size_t quantEnemiesType2;
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
} gameParams_t;

#endif