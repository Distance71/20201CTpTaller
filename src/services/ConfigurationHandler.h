#ifndef _CONFIGURATIONHANDLER_H_
#define _CONFIGURATIONHANDLER_H_

#include "ParserJson.h"
#include "../game/types.h"
#include <vector>
#include <stdlib.h>

#define PATH_LOG_LEVEL "/configuracion/log/level"
#define PATH_LEVEL "/configuracion/level"
#define PATH_BASE_STAGE "/configuracion/level/"

#define DEFAULT_ENEMY_QUANTITY 25
#define DEFAULT_ENEMY_TYPE 0

#define STEP_FOR_STAGE 6
#define MIN_ENEMY_STEP 2
#define MAX_ENEMY_STEP 7

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

        vector<stepParams_t> getStep(vector<enemy_t> &totalEnemies);

    public:
        ConfigurationHandler();
        ~ConfigurationHandler();

        bool loadFileConfiguration(const string &pathFileConfiguration);
        void initializeData();
        void setLogLevel();

        stageSource_t getSourcesForStage(int oneLevel, int oneStage);
};


#endif