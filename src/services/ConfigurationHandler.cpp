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

bool ConfigurationHandler::loadFileConfiguration(const string &pathFileConfiguration){
    return this->parserJson->loadConfiguration(pathFileConfiguration);
}

vector<stepParams_t> ConfigurationHandler::getStep(vector<enemy_t> &totalEnemies){
    vector<stepParams_t> stepsParams;

    unsigned int cantEnemies = totalEnemies.size();
    vector<unsigned int> cantPuesta (cantEnemies); 
    vector<unsigned int> cantTotal (cantEnemies); 
    srand(time(NULL)); 

    // Guardamos el Total de Enemigos que debemos poner en todo el Stage
    for(int posEnemy = 0; posEnemy < cantEnemies; posEnemy++){
        cantTotal[posEnemy] = totalEnemies[posEnemy].quantity;
    }

    for(int step = 0; step < 6; step++){
        stepParams_t oneStepParam;

        for(int i = 0; i < cantEnemies; i++){
            enemy_t oneEnemy;
            oneEnemy.type = totalEnemies[i].type;
            oneEnemy.sprite = totalEnemies[i].sprite;

            if (step == STEP_FOR_STAGE - 1){
                // Si es el ultimo Step debo poner todos los enemigos restantes para completar
                oneEnemy.quantity = cantTotal[i] - cantPuesta[i];
            } else {
                unsigned int cantAPoner = 0;
                unsigned int cotaSup = min((unsigned int)MAX_ENEMY_STEP, (cantTotal[i] - cantPuesta[i]));
                unsigned int cotaInf = min((unsigned int)MIN_ENEMY_STEP, (cantTotal[i] - cantPuesta[i]));

                /* Si la cota Superior no es cero y la cantAPoner es cero. Quiere decir que tenemos enemigos para
                   poner, entonces ejecutamos hasta que la funcion rand() nos de un numero mayor a cero.
                */
                while ((cotaSup != 0) && (cantAPoner == 0)){
                    cantAPoner = cotaInf + rand()%(cotaSup + 1 - cotaInf);
                }

                oneEnemy.quantity = cantAPoner;
                cantPuesta[i] += cantAPoner;
            }
            
            oneStepParam.enemies.push_back(oneEnemy);
        }

        stepsParams.push_back(oneStepParam);
    }

    return stepsParams;    
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

                /*
                if (oneEnemy.type == 0){
                    cantTotalType1 += oneEnemy.quantity;
                } else {
                    cantTotalType2 += oneEnemy.quantity;
                }*/

                string pathEnemySprite = getPathStageEnemy(pathStage, numberEnemy, "sprite");
                oneEnemy.sprite = this->parserJson->getString(pathEnemySprite);

                oneStageParams.totalEnemies.push_back(oneEnemy);
            }

            //oneStageParams.stepsParams = getStep(cantTotalType1, cantTotalType2);
            oneStageParams.stepsParams = getStep(oneStageParams.totalEnemies);
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

stageSource_t ConfigurationHandler::getSourcesForStage(int oneLevel, int oneStage){

    stageSource_t stageSource;

    if (oneLevel >= this->gameData.levelParams.size()){
        Logger::getInstance()->log(ERROR, "Se quiere acceder al stageSource de un nivel invalido. Level: " + to_string(oneLevel));
        return stageSource;
    }
    
    if (oneStage >= this->gameData.levelParams[oneLevel].stagesParams.size()){
        Logger::getInstance()->log(ERROR, "Se quiere acceder al stageSource de un stage invalido. Level: " + to_string(oneLevel) + " - Stage: " + to_string(oneStage));
        return stageSource;
    }

    Logger::getInstance()->log(DEBUG, "Se devuelve el stageSource del stage "  + to_string(oneStage) + " del nivel " + to_string(oneLevel));

    return this->gameData.levelParams[oneLevel].stagesParams[oneStage].backgroundSources;
}

gameParams_t ConfigurationHandler::getGameParams(){
    return this->gameData;
}
