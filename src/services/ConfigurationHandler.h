#ifndef _CONFIGURATIONHANDLER_H_
#define _CONFIGURATIONHANDLER_H_

#include "ParserJson.h"
#include "../game/types.h"
#include <vector>
#include <stdlib.h>

#define PATH_LOG_LEVEL "/configuracion/log/level"
#define PATH_LEVEL "/configuracion/level"
#define PATH_BASE_STAGE "/configuracion/level/"
#define PATH_PLAYER "/configuracion/player/"
#define PATH_SCREEN "/configuracion/screen/"

#define DEFAULT_SIZE_X 110
#define DEFAULT_SIZE_Y 90
#define DEFAULT_ENEMY_QUANTITY 25
#define DEFAULT_ENEMY_TYPE 0

#define STEP_FOR_STAGE 6
#define MIN_ENEMY_STEP 8
#define MAX_ENEMY_STEP 20

#define MIN_SCREEN_WIDTH 800
#define MIN_SCREEN_HEIGHT 600

using namespace std;

class ParserJson;

//Encargado de manejar la configuracion inicial del programa

class ConfigurationHandler {

    private: 
        gameParams_t gameData;
        ParserJson *parserJson;

        string getPathLevel(int numberLevel);
        string getPathStage(int numberLevel, int numberStage);
        string getPathStageLayer(string pathStage, int numberLayer);
        string getPathStageEnemy(string pathStage, int numberEnemy, string paramEnemy);

        string getPathPlayer(string paramPlayer);
        player_t getPlayerParams();

        vector<stepParams_t> getStep(vector<enemy_t> &totalEnemies);

        string getPathScreen(string paramScreen);
        void setSizeScreen();

    public:
        ConfigurationHandler();
        ~ConfigurationHandler();

        bool loadFileConfiguration(const string &pathFileConfiguration);
        void initializeData();
        void setLogLevel();

        stageSource_t getSourcesForStage(int oneLevel, int oneStage);
        gameParams_t getGameParams();
};


#endif