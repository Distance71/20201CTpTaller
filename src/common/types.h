#ifndef _TYPES_H_
#define _TYPES_H_

#include <string>
#include <vector>


using namespace std;

typedef struct status {
    bool normalStatus = true;
    string errorLog;
} status_t;

typedef enum layer {
    LAYER_1 = 0, 
    LAYER_2 = 1, 
    LAYER_3 = 2, 
    LAYER_4 = 3,    
    LAYER_5 = 4, 
    LAYER_6 = 5, 
    LAYER_7 = 6
} layer_t ;

typedef enum character {
    CHARACTER_1 = 0,
    CHARACTER_2 = 1,
    CHARACTER_3 = 2,
    CHARACTER_4 = 3,
} character_t;

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

typedef enum message {
    ANIMATION_INIT_STAGE = 0,
    END_GAME = 1,
    END_STAGE = 2,
    GAME_INIT = 3,
    INIT_STAGE = 4,
    LOG = 5,
    MAP_ELEMENT_CREATE = 6,
    MAP_ELEMENT_DELETE = 7,
    MAP_ELEMENT_UPDATE = 8,
    PLAYER_DISCONNECT = 9,
    PLAYER_RECONNECT = 10,
    REQUEST_LOGIN_PLAYER = 11,
    RESPONSE_LOGIN_PLAYER = 12,
    USER_MOVEMENT = 13,
} message_t;

typedef enum {
    FRONT = 0,
    BACK = 1,
    UP = 2,
    DOWN = 3,
    FRONT_UP = 4,
    FRONT_DOWN = 5,
    BACK_DOWN = 6,
    BACK_UP = 7,
    NOT_MOVEMENT = 8,
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
    unsigned int width;
    unsigned int height;
} spriteSize_t;

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
typedef size_t IdUser;

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

//Exported to a class -> se deja por el momento
typedef struct {
    string username;
    string password;
    player_t playerParams;
} user_t;

typedef struct {
    vector<levelParams_t> levelParams;
    vector<user_t> playersParams;
} gameParams_t;

typedef struct argsThreadUser {
    void* params;
    void* handler;
} argsThread_t;

typedef enum {
    SELECTED,
    NOT_SELECTED,
}buttonstate_t;

typedef enum responseStatus {
    OK,
    ERROR_CONNECTION,
    ERROR_MESSAGE,
    ERROR_FULL_GAME,
    ERROR_WRONG_CREDENTIALS,
    NOT_RESPONSE,
} responseStatus_t;

typedef struct {
    bool ok;
    responseStatus_t status;
} response_t;

#endif
