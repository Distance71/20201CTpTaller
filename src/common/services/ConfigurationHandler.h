#ifndef _CONFIGURATIONHANDLER_H_
#define _CONFIGURATIONHANDLER_H_

#include "ParserJson.h"
#include "../types.h"
#include "../providers/GameProvider.h"
#include <vector>
#include <stdlib.h>

#define PATH_LOG_LEVEL "/configuracion/log/level"
#define PATH_LEVEL "/configuracion/level"
#define PATH_BASE_STAGE "/configuracion/level/"
#define PATH_PLAYERS "/configuracion/players"
#define PATH_BASE_PLAYERS "/configuracion/players/"
#define PATH_SCREEN "/configuracion/screen/"
#define PATH_USER "/configuracion/users"
#define PATH_BASE_USER "/configuracion/users/"
#define PATH_BASE_LOGIN_SCREEN "/configuracion/loginScreen/"
#define PATH_INFORMATION_SCREEN "/configuracion/informationScreen/"
#define PATH_QUANTITY_PLAYERS "/configuracion/quantityPlayers"
#define PATH_ROJECTILE "/configuracion/projectiles/"
#define PATH_FINAL_BOSS "/configuracion/finalBoss/"

#define DEFAULT_SIZE_X 110
#define DEFAULT_SIZE_Y 90
#define DEFAULT_ENEMY_QUANTITY 25
#define DEFAULT_ENEMY_HEALTH 100
#define DEFAULT_ENEMY_TYPE 0
#define DEFAULT_BOSS_HEALTH 1000

#define STEP_FOR_STAGE 1
#define MAX_STEPS 20
//#define MIN_ENEMY_STEP 8
//#define MAX_ENEMY_STEP 20

#define MAX_QUANTITY_PLAYERS 4

#define MIN_SCREEN_WIDTH 800
#define MIN_SCREEN_HEIGHT 600

using namespace std;

class ParserJson;

//Encargado de manejar la configuracion inicial del programa

class ConfigurationHandler {

    private: 
        gameParams_t gameData;
        informationScreen_t informationScreen_;
        bool isServer_;
        ParserJson *parserJson;

        string getPathUser(int numberUser, string paramUser);
        string getPathLevel(int numberLevel);
        string getPathStage(int numberLevel, int numberStage);
        string getPathStageLayer(string pathStage, int numberLayer);
        string getPathStageEnemy(string pathStage, int numberEnemy, string paramEnemy);
        
        string getPathPlayer(int numberPlayer, string paramPlayer);
        player_t getPlayerParams(int numberPlayer);
        vector<user_t> getUsersParams();
        cotasCantEnemigos_t getCotasEnemigos(unsigned int cantTotalEnemigos, unsigned int cantSteps);

        vector<stepParams_t> getStep(vector<enemy_t> &totalEnemies);

        string getPathScreen(string paramScreen);
        void setSizeScreen();

        string getPathInformationScreen(string paramScreen);
        void setInformationScreen();

        string getPathLoginScreen(string paramLogin);
        loginScreen_t readLoginScreen();
        
        string getPathCommonProjectile(string paramProjectile);
        projectile_t getCommonProjectile();

        string getPathFinalBoss(string paramBossEnemy);
        enemy_t getBoss();

        void initializeDataServer();
        void initializeDataClient();

    public:
        ConfigurationHandler(bool isServer);
        ~ConfigurationHandler();

        bool loadFileConfiguration(const string &pathFileConfiguration);
        void initializeData();
        void setLogLevel();
        void setConfigDefault();

        stageSource_t getSourcesForStage(int oneStage);
        transitionScreen_t getTransitionScreenForLevel(int oneLevel);
        informationScreen_t getinformationScreen();
        gameParams_t getGameParams();
        player_t getPlayerParam(int numberPlayer);
        enemy_t getEnemyData(int numberTypeEnemy);
        transitionScreen_t getTransitionScreenForStage(int oneStage);
        enemy_t getFinalBoss();
        projectile_t getProjectileData();

};


#endif