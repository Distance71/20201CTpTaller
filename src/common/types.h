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
    SCENE_ANIMATION = 0,
    END_GAME = 1,
    GAME_INIT = 2,
    LOG = 3,
    MAP_ELEMENT_UPDATE = 4,
    REQUEST_LOGIN_PLAYER = 5,
    RESPONSE_LOGIN_PLAYER = 6,
    USER_MOVEMENT = 7,
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

typedef enum {
    INIT_LEVEL_ONE = 0,
    END_LEVEL_ONE = 1,
    INIT_LEVEL_TWO = 2,
    END_LEVEL_TWO = 3,
    INIT_LEVEL_THREE = 4,
    END_LEVEL_THREE = 5,
    INIT_LEVEL_FOUR = 6,
    END_LEVEL_FOUR = 7,
} transition_t;

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
    PLAYER_1,
    PLAYER_2,
    PLAYER_3,
    PLAYER_4,
    ENEMY_1,
    ENEMY_2,
    PLAYER,
    ENEMY,
} elementType_t;

typedef enum {
    INIT_STAGE_1,
    END_STAGE_1,
    INIT_STAGE_2,
    END_STAGE_2,
    INIT_STAGE_3,
    END_STAGE_3,
    END_GAME_ANIMATION,
    WAITING_PLAYERS,
} sceneScreen_t;

typedef size_t Id;

typedef struct {
    level_t level;
    stage_t stage;
    size_t step;
} currentStep_t;

typedef struct {
    string initPath;
    string endPath;
} transitionScreen_t;

typedef struct {
    vector<enemy_t> enemies;
} stepParams_t;

typedef struct {
    stageSource_t backgroundSources;
    vector<stepParams_t> stepsParams;
    vector<enemy_t> totalEnemies;
} stageParams_t;

typedef struct {
    vector<stageParams_t> stagesParams;
    transitionScreen_t pathTransitionScreen;
} levelParams_t;

//Exported to a class -> se deja por el momento
typedef struct {
    Id id;
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
} buttonstate_t;

typedef enum responseStatus {
    OK,
    ERROR_CONNECTION,
    NOT_MESSAGE,
    ERROR_MESSAGE,
    ERROR_FULL_GAME,
    ERROR_WRONG_CREDENTIALS,
    NOT_RESPONSE,
    DISCONNECTION,
    ERROR_ALREADY_LOGGED_IN,
} responseStatus_t;

typedef struct {
    bool ok;
    responseStatus_t status;
} response_t;

#endif
