#ifndef _TYPES_H_
#define _TYPES_H_

#include <string>
#include <vector>

using namespace std;

typedef struct {
    string type;
    unsigned int quantity;
    string sprite;
} enemy_t;

typedef struct {
    string layer1;
    string layer2;
    string layer3;
} stage_t;

typedef struct {
    stage_t stage_;
    vector<enemy_t> enemies_;
} levelContent_t;

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

typedef enum LEVEL_NUMBER {
    LEVEL_ONE = 0
} level_t;

#endif