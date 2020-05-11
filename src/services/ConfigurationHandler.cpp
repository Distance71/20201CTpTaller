#include "ConfigurationHandler.h"

ConfigurationHandler::ConfigurationHandler(){
    this->parserJson = new ParserJson();
}

ConfigurationHandler::~ConfigurationHandler(){
    delete this->parserJson;
    //delete this->levelData;
}

string ConfigurationHandler::getPathLevel(int numberLevel){
    string pathLevel = PATH_BASE_STAGE + to_string(numberLevel);

    return pathLevel;
}

string ConfigurationHandler::getPathStage(int numberLevel, int numberStage){
    string pathStage = PATH_BASE_STAGE + to_string(numberLevel) + "/" + to_string(numberStage);

    return pathStage;
}

string ConfigurationHandler::getPathStageLayer(string pathStage, int numberLayer){

    string pathStageLayer = pathStage + "/layer" + to_string(numberLayer);

    return pathStageLayer;
}

string ConfigurationHandler::getPathStageEnemy(string pathStage, int numberEnemy, string paramEnemy){

    string pathStageEnemy = pathStage + "/enemies";

    if (numberEnemy >= 0){
        pathStageEnemy += "/" + to_string(numberEnemy) + "/" + paramEnemy;
    }

    return pathStageEnemy;
}

vector<stepParams_t> ConfigurationHandler::getStep(unsigned int cantTotalType1, unsigned int cantTotalType2){
    vector<stepParams_t> stepsParams;

    unsigned int cantPuestaType1 = 0;
    unsigned int cantPuestaType2 = 0;

    srand(time(NULL)); 

    for(int step = 0; step < STEP_FOR_STAGE; step++){
        stepParams_t oneStepParam;

        if (step == STEP_FOR_STAGE - 1){
            oneStepParam.quantEnemiesType1 = cantTotalType1 - cantPuestaType1;
            oneStepParam.quantEnemiesType2 = cantTotalType2 - cantPuestaType2; 
        } else {
            unsigned int cantType1 = 0;
            unsigned int cantType2 = 0;

            unsigned int cotaSupType1 = min((unsigned int)MAX_ENEMY_STEP, (cantTotalType1 - cantPuestaType1));
            unsigned int cotaMinType1 = min((unsigned int)MIN_ENEMY_STEP, (cantTotalType1 - cantPuestaType1));

            unsigned int cotaSupType2 = min((unsigned int)MAX_ENEMY_STEP, (cantTotalType2 - cantPuestaType2));
            unsigned int cotaMinType2 = min((unsigned int)MIN_ENEMY_STEP, (cantTotalType2 - cantPuestaType2));

            while ((cantType1 + cantType2 == 0) && ((cotaSupType1 != 0) || (cotaSupType2 != 0))){
                if (cotaSupType1 != 0){
                    cantType1 = cotaMinType1 + rand()%(cotaSupType1 + 1 - cotaMinType1);
                }

                if (cotaSupType2 != 0){
                    cantType2 = cotaMinType2 + rand()%(cotaSupType2 + 1 - cotaMinType2);
                }
            }


            oneStepParam.quantEnemiesType1 = cantType1;
            oneStepParam.quantEnemiesType2 = cantType2; 

            cantPuestaType1 += cantType1;
            cantPuestaType2 += cantType2;
        }

        stepsParams.push_back(oneStepParam);

    }

    return stepsParams;
}

bool ConfigurationHandler::loadFileConfiguration(const string &pathFileConfiguration){
    return this->parserJson->loadConfiguration(pathFileConfiguration);
}

void ConfigurationHandler::initializeData(){

    int sizeLevel = this->parserJson->getSizeArray(PATH_LEVEL);

    Logger::getInstance()->log(DEBUG, "Se comienza a analizar la configuracion de los distintos niveles.");
    
    for(int numberLevel = 0; numberLevel < sizeLevel; numberLevel++){
        Logger::getInstance()->log(DEBUG, "Se comienza a analizar la configuracion del nivel " + to_string(numberLevel));
        string pathLevel = getPathLevel(numberLevel);
        int sizeStage = this->parserJson->getSizeArray(pathLevel);
        levelParams_t oneLevelParams;

        for(int numberStage = 0; numberStage < sizeStage; numberStage++){
            Logger::getInstance()->log(DEBUG, "Se comienza a analizar la configuracion del stage " + to_string(numberStage) + " para el nivel " + to_string(numberLevel));
            stageParams_t oneStageParams;

            string pathStage = getPathStage(numberLevel, numberStage);

            string pathLayer1 = getPathStageLayer(pathStage, 1);
            oneStageParams.backgroundSources.layer1 = this->parserJson->getString(pathLayer1);

            string pathLayer2 = getPathStageLayer(pathStage, 2);
            oneStageParams.backgroundSources.layer2 = this->parserJson->getString(pathLayer2);

            string pathLayer3 = getPathStageLayer(pathStage, 3);
            oneStageParams.backgroundSources.layer3 = this->parserJson->getString(pathLayer3);

            string pathEnemiesBase = getPathStageEnemy(pathStage, -1, "");
            int sizeEnemies = this->parserJson->getSizeArray(pathEnemiesBase);
            
            unsigned int cantTotalType1 = 0;
            unsigned int cantTotalType2 = 0;

            for(int numberEnemy = 0; numberEnemy < sizeEnemies; numberEnemy++){
                Logger::getInstance()->log(DEBUG, "Se comienza a analizar el enemigo " + to_string(numberEnemy) + " del stage " + to_string(numberStage) + " para el nivel " + to_string(numberLevel));
            
                enemy_t oneEnemy;

                string pathEnemyType = getPathStageEnemy(pathStage, numberEnemy, "type");
                int typeEnemy = this->parserJson->getUnsignedInt(pathEnemyType);
                if (typeEnemy >= 0){
                    oneEnemy.type = typeEnemy;
                } else {
                    oneEnemy.type = DEFAULT_ENEMY_TYPE;
                }

                string pathEnemyQuantity = getPathStageEnemy(pathStage, numberEnemy, "quantity");

                int cantEnemy = this->parserJson->getUnsignedInt(pathEnemyQuantity); 

                if (cantEnemy >= 0){
                    oneEnemy.quantity = cantEnemy;
                } else {
                    oneEnemy.quantity = DEFAULT_ENEMY_QUANTITY;
                }

                if (oneEnemy.type == 0){
                    cantTotalType1 += oneEnemy.quantity;
                } else {
                    cantTotalType2 += oneEnemy.quantity;
                }

                string pathEnemySprite = getPathStageEnemy(pathStage, numberEnemy, "sprite");
                oneEnemy.sprite = this->parserJson->getString(pathEnemySprite);

                oneStageParams.totalEnemies.push_back(oneEnemy);
            }

            oneStageParams.stepsParams = getStep(cantTotalType1, cantTotalType2);

            oneLevelParams.stagesParams.push_back(oneStageParams);
        }

        this->gameData.levelParams.push_back(oneLevelParams);
    }

}

void ConfigurationHandler::setLogLevel(){
    string logLevel = this->parserJson->getString(PATH_LOG_LEVEL);

    Logger::getInstance()->setLevel(logLevel);
    
    Logger::getInstance()->log(INFO, "Se settea nivel del Logger desde el archivo de configuracion.");
}

stageSource_t ConfigurationHandler::getStageData(int oneLevel){
    //return this->levelData->at(oneLevel).stage;
}
