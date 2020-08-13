#ifndef _TYPES_H_
#define _TYPES_H_

#include <string>
#include <vector>
#include "SDL2/SDL.h"


using namespace std;

typedef struct status {
    bool normalStatus = true;
    string errorLog;
} status_t;

typedef enum {
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
    STAGE_THREE = 2,
    STAGE_FOUR = 3,
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
    BACKGROUND_UPDATE = 8,
    USER_SHOOT = 9,
    USER_CHANGE_MODE = 10,
    MUSIC_UPDATE = 11,
    SCORE_UPDATE = 12,
    GAME_OVER = 13,
    QUANTITY_PLAYERS = 14,
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
    SDL_Texture *spriteTexture;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    orientation_t orientation;
    bool isMap;
} renderElement_t;

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
    int size_x;
    int size_y;
    string sprite;
    string spriteDisconnected;
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

typedef enum {
    PLAYER_1 = 0,
    PLAYER_2 = 1,
    PLAYER_3 = 2,
    PLAYER_4 = 3,
    ENEMY_1_A = 4,
    ENEMY_2_A = 5,
    ENEMY_1_B = 6,
    ENEMY_2_B = 7,
    ENEMY_1_C = 8,
    ENEMY_2_C = 9,
    ENEMY_1_D = 10,
    ENEMY_2_D = 11,
    PLAYER = 12,
    ENEMY = 13,
    PLAYER_1_OUT = 14,
    PLAYER_2_OUT = 15,
    PLAYER_3_OUT = 16,
    PLAYER_4_OUT = 17,
    END_GRAPHIC = 18,
    BACKGROUND = 19,
    BOSS_ENEMY = 20,
    PROJECTILE = 21,
    EXPLOSION_ANIMATION_1 = 22,
    EXPLOSION_ANIMATION_2 = 23,
    EXPLOSION_ANIMATION_3 = 24,
    EXPLOSION_ANIMATION_4 = 25,
    EXPLOSION_ANIMATION_5 = 26,
    EXPLOSION_ANIMATION_6 = 27,
    EXPLOSION_ANIMATION_7 = 28,
    EXPLOSION_ANIMATION_8 = 29,
    EXPLOSION_ANIMATION_9 = 30,
    EXPLOSION_ANIMATION_10 = 31,
    EXPLOSION_ANIMATION_11 = 32,
    PLAYER_1_G = 33,
    PLAYER_2_G = 34,
    PLAYER_3_G = 35,
    PLAYER_4_G = 36,
    PROJECTILE_BOSS = 37,
    PLAYER_1_DEAD = 38,
    PLAYER_2_DEAD = 39,
    PLAYER_3_DEAD = 40,
    PLAYER_4_DEAD = 41,
    EXPLOSION_ANIMATION_BOSS_1 = 42,
    EXPLOSION_ANIMATION_BOSS_2 = 43,
    EXPLOSION_ANIMATION_BOSS_3 = 44,
    EXPLOSION_ANIMATION_BOSS_4 = 45,
    EXPLOSION_ANIMATION_BOSS_5 = 46,
    EXPLOSION_ANIMATION_BOSS_6 = 47,
    EXPLOSION_ANIMATION_BOSS_7 = 48,
    EXPLOSION_ANIMATION_BOSS_8 = 49,
    EXPLOSION_ANIMATION_BOSS_9 = 50,
    EXPLOSION_ANIMATION_BOSS_10 = 51,
    EXPLOSION_ANIMATION_BOSS_11 = 52,
} elementType_t;

typedef enum {
    MUSIC_STAGE_ONE = 0,
    MUSIC_STAGE_TWO = 1,
    MUSIC_STAGE_THREE = 2,
    MUSIC_STAGE_FOUR = 3,

    EXPLOSION_ENEMY = 4,
    EXPLOSION_PLAYER = 5,
    EXPLOSION_BOSS = 6,
    PLAYER_SHOT = 7,
    ENEMY_SHOT = 8,
    BOSS_SHOT = 9,
    SHOT_IMPACTS = 10,
    SHOT_IMPACTS_PLAYER = 11,
    SHOT_IMPACTS_BOSS = 12,
    RECONEXION_PLAYER = 13,
} musicType_t;

typedef enum {
    MODE_NORMAL_GAME = 0,
    MODE_TEST_GAME = 1
} gameMode_t;

typedef struct {
    elementType_t type;
    unsigned int quantity;
    int size_x;
    int size_y;
    string sprite;
    int health;
} enemy_t;

typedef struct {
    int size_x;
    int size_y;
    string sprite;
} projectile_t;

typedef struct {
    stage_t stage;
    vector<enemy_t> enemies;
} stepContent_t;

typedef struct {
    elementType_t type;
    position_t position;
    layer_t layer;
    stage_t stage;
    int step;
} elementToGraphic_t;

typedef enum {
    INIT_STAGE_1 = 0,
    END_STAGE_1 = 1,
    INIT_STAGE_2 = 2,
    END_STAGE_2 = 3,
    INIT_STAGE_3 = 4,
    END_STAGE_3 = 5,
    INIT_STAGE_4 = 6,
    END_STAGE_4 = 7,
    INIT_STAGE_DEFAULT = 8,
    END_STAGE_DEFAULT = 9,
    END_GAME_ANIMATION = 10,
    WAITING_PLAYERS = 11,
    SERVER_DISCONNECTION = 12,
    GAME_OVER_ANIMATION = 13,
    SCORE_TABLE = 14,
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
    transitionScreen_t pathTransitionScreen;
} stageParams_t;

typedef struct {
    vector<stageParams_t> stagesParams;
} levelParams_t;

//Exported to a class -> se deja por el momento
typedef struct {
    Id id;
    string username;
    string password;
    player_t playerParams;
} user_t;

typedef struct {
    string background;
    string normalBox;
    string invalidCredentialsBox;
    string fullGameBox;
    string alreadyLoggedIn;
    string username1;
    string username2;
    string password1;
    string password2;
    string login;
} loginScreen_t;

typedef struct {
    string endGame;
    string waitingPlayers;
    string disconnection;
    string gameOver;
} informationScreen_t;

typedef struct {
    vector<levelParams_t> levelParams;
    vector<user_t> playersParams;
    loginScreen_t loginScreen;
    projectile_t commonProjectile;
    projectile_t bossProjectile;
    enemy_t finalBoss;
} gameParams_t;

typedef struct argsThreadUser {
    void* params;
    void* handler;
} argsThread_t;

typedef enum {
    SELECTED,
    NOT_SELECTED,
} buttonstate_t;

typedef enum {
    OK = 0,
    ERROR_CONNECTION = 1,
    NOT_MESSAGE = 2,
    ERROR_MESSAGE = 3,
    ERROR_FULL_GAME = 4,
    ERROR_WRONG_CREDENTIALS = 5,
    NOT_RESPONSE = 6,
    DISCONNECTION = 7,
    ERROR_ALREADY_LOGGED_IN = 8,
} responseStatus_t;

typedef struct {
    bool ok;
    responseStatus_t status;
} response_t;

typedef struct {
    int xInit;
    int xEnd;
    int yInit;
    int yEnd;
}gameZone_t;

typedef struct{
    elementType_t playerImage;
    unsigned int lives;
    int health;
    int levelScore;
    int totalScore;
} playerState_t;

#endif
