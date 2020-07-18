#include "ConfigurationHandler.h"

ConfigurationHandler::ConfigurationHandler(bool isServer){
    this->isServer_ = isServer;
    this->parserJson = new ParserJson(isServer);
}

ConfigurationHandler::~ConfigurationHandler(){
    delete this->parserJson;
    //delete this->levelData;
}

string ConfigurationHandler::getPathUser(int numberUser, string paramUser){

    string pathUserParam = PATH_BASE_USER + to_string(numberUser) + "/" + paramUser;

    return pathUserParam;
}

string ConfigurationHandler::getPathLevel(int numberLevel){
    string pathLevel = PATH_BASE_STAGE;

    return pathLevel;
}

string ConfigurationHandler::getPathStage(int numberLevel, int numberStage){
    string pathStage = PATH_BASE_STAGE + to_string(numberStage);

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

string ConfigurationHandler::getPathPlayer(int numberPlayer, string paramPlayer){
    string pathPlayer = PATH_BASE_PLAYERS + to_string(numberPlayer) + "/" + paramPlayer;

    return pathPlayer;
}

player_t ConfigurationHandler::getPlayerParams(int numberPlayer){
    player_t playerParam;

    string pathSizeX = getPathPlayer(numberPlayer, "sizeX");
    int sizeX = this->parserJson->getUnsignedInt(pathSizeX);
    if (sizeX >= 0){
        playerParam.size_x = sizeX;
    } else {
        playerParam.size_x = DEFAULT_SIZE_X;
    }    

    string pathSizeY = getPathPlayer(numberPlayer, "sizeY");
    int sizeY = this->parserJson->getUnsignedInt(pathSizeY);
    if (sizeX >= 0){
        playerParam.size_y = sizeY;
    } else {
        playerParam.size_y = DEFAULT_SIZE_Y;
    }    
    
    unsigned int sizeScreenX = GameProvider::getWidth();
    unsigned int sizeScreenY = GameProvider::getHeight();

    if (sizeX > sizeScreenX){
        Logger::getInstance()->log(ERROR, "El largo del jugador " + to_string(numberPlayer) + " supera el largo de la pantalla. Se settea este ultimo como su largo");
        playerParam.size_x = sizeScreenX;
    }
    
    if (sizeX > sizeScreenY){
        Logger::getInstance()->log(ERROR, "El ancho del jugador " + to_string(numberPlayer) + " supera el ancho de la pantalla. Se settea este ultimo como su ancho");
        playerParam.size_y = sizeScreenY;
    }    

    if (!this->isServer_){
        string pathSprite = getPathPlayer(numberPlayer, "sprite");
        playerParam.sprite = this->parserJson->getString(pathSprite);
    }

    return playerParam;
}

vector<user_t> ConfigurationHandler::getUsersParams(){

    size_t quantityPlayers = this->parserJson->getSizeArray(PATH_USER);

    if (quantityPlayers > MAX_QUANTITY_PLAYERS){
        Logger::getInstance()->log(ERROR, "La cantidad de usuarios supera la máxima permitida (4 jugadores). Se settea con esta cantidad.");
        quantityPlayers = MAX_QUANTITY_PLAYERS;
    }

    GameProvider::setQuantityPlayers(quantityPlayers);
    
    vector<user_t> users (quantityPlayers);

    for (size_t oneUser = 0; oneUser < quantityPlayers; oneUser++){
        user_t newUser;

        string pathUsername = this->getPathUser(oneUser, "username");
        string pathPassword = this->getPathUser(oneUser, "password");

        newUser.username = this->parserJson->getString(pathUsername);
        newUser.password = this->parserJson->getString(pathPassword);

        newUser.playerParams = this->getPlayerParams(oneUser);

        users.push_back(newUser);
    }

    return users;
}

bool ConfigurationHandler::loadFileConfiguration(const string &pathFileConfiguration){
    return this->parserJson->loadConfiguration(pathFileConfiguration);
}

cotasCantEnemigos_t ConfigurationHandler::getCotasEnemigos(unsigned int cantTotalEnemigos, unsigned int cantSteps){
    cotasCantEnemigos_t cotasEnemigos;

    unsigned int promPorStep = cantTotalEnemigos / cantSteps;
    unsigned int delta = promPorStep * 20 / 100;
    cotasEnemigos.cotaInferior = promPorStep - delta;
    cotasEnemigos.cotaSuperior = promPorStep + delta;

    if (promPorStep == 0){
        cotasEnemigos.cotaSuperior = cantTotalEnemigos;
    }

    return cotasEnemigos;
}

vector<stepParams_t> ConfigurationHandler::getStep(vector<enemy_t> &totalEnemies){
    vector<stepParams_t> stepsParams;

    unsigned int cantEnemies = totalEnemies.size();
    unsigned int quantityEnemies = 0;
    unsigned int cantStepsAJugar = 1;
    vector<unsigned int> cantPuesta (cantEnemies); 
    vector<unsigned int> cantTotal (cantEnemies);
    vector<cotasCantEnemigos_t> cotasEnemigos (cantEnemies);
    srand(time(NULL)); 

    // Guardamos el Total de Enemigos que debemos poner en todo el Stage
    for(int posEnemy = 0; posEnemy < cantEnemies; posEnemy++){
        unsigned int enemiesTotales = totalEnemies[posEnemy].quantity;
        cantTotal[posEnemy] = enemiesTotales;
        quantityEnemies += enemiesTotales;
        //cotasEnemigos[posEnemy] = getCotasEnemigos(enemiesTotales);
    }

    cantStepsAJugar += (quantityEnemies / 40);

    if (cantStepsAJugar > MAX_STEPS){
        cantStepsAJugar = MAX_STEPS;
    }

    for(int posEnemy = 0; posEnemy < cantEnemies; posEnemy++){
        cotasEnemigos[posEnemy] = getCotasEnemigos(cantTotal[posEnemy], cantStepsAJugar);
    }

    for(int step = 0; step < cantStepsAJugar; step++){
        stepParams_t oneStepParam;

        for(int i = 0; i < cantEnemies; i++){
            enemy_t oneEnemy;
            oneEnemy.type = totalEnemies[i].type;
            oneEnemy.size_x = totalEnemies[i].size_x;
            oneEnemy.size_y = totalEnemies[i].size_y;
            oneEnemy.sprite = totalEnemies[i].sprite;

            if (step == cantStepsAJugar - 1){
                // Si es el ultimo Step debo poner todos los enemigos restantes para completar
                oneEnemy.quantity = cantTotal[i] - cantPuesta[i];
            } else {
                unsigned int cantAPoner = 0;
                unsigned int cotaSup = min(cotasEnemigos[i].cotaSuperior, (cantTotal[i] - cantPuesta[i]));
                unsigned int cotaInf = min(cotasEnemigos[i].cotaInferior, (cantTotal[i] - cantPuesta[i]));

                //unsigned int cotaSup = min((unsigned int)MAX_ENEMY_STEP, (cantTotal[i] - cantPuesta[i]));
                //unsigned int cotaInf = min((unsigned int)MIN_ENEMY_STEP, (cantTotal[i] - cantPuesta[i]));

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

    this->setSizeScreen();

    if (this->isServer_){
        this->initializeDataServer();
    } else {
        this->initializeDataClient();
    }

}

string ConfigurationHandler::getPathScreen(string paramScreen){
    string pathScreen = PATH_SCREEN + paramScreen;

    return pathScreen;
}

void ConfigurationHandler::setSizeScreen(){

    string pathScreenWidth = getPathScreen("width");
    string pathScreenHeight = getPathScreen("height");

    size_t screenWidth = this->parserJson->getUnsignedInt(pathScreenWidth);
    if (screenWidth < MIN_SCREEN_WIDTH){
        screenWidth = MIN_SCREEN_WIDTH;
        Logger::getInstance()->log(ERROR, "El ancho de la ventana es menor al mínimo permitido. Se settea como valor el mínimo.");
    } 

    size_t screenHeight = this->parserJson->getUnsignedInt(pathScreenHeight);
    if (screenHeight < MIN_SCREEN_HEIGHT){
        screenHeight = MIN_SCREEN_HEIGHT;
        Logger::getInstance()->log(ERROR, "El alto de la ventana es menor al mínimo permitido. Se settea como valor el mínimo.");
    } 
    
    GameProvider::setWidth(screenWidth);
    GameProvider::setHeight(screenHeight);
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

transitionScreen_t ConfigurationHandler::getTransitionScreenForLevel(int oneLevel){

    transitionScreen_t transitionScreen;

    if (oneLevel >= this->gameData.levelParams.size()){
        Logger::getInstance()->log(ERROR, "Se quiere acceder al transitionScreen de un nivel invalido. Level: " + to_string(oneLevel));
        return transitionScreen;
    }

    Logger::getInstance()->log(DEBUG, "Se devuelve el transitionScreen del nivel " + to_string(oneLevel));

    return this->gameData.levelParams[oneLevel].pathTransitionScreen; 
}

gameParams_t ConfigurationHandler::getGameParams(){

    return this->gameData;
}

void ConfigurationHandler::setConfigDefault(){
    this->parserJson->setConfigDefault();
};

void ConfigurationHandler::initializeDataServer(){

    size_t quantityPlayers = this->parserJson->getSizeArray(PATH_USER);

    if (quantityPlayers > MAX_QUANTITY_PLAYERS){
        Logger::getInstance()->log(ERROR, "La cantidad de usuarios supera la máxima permitida (4 jugadores). Se settea con esta cantidad.");
        quantityPlayers = MAX_QUANTITY_PLAYERS;
    }

    GameProvider::setQuantityPlayers(quantityPlayers);
    
    vector<user_t> users (quantityPlayers);

    for (size_t oneUser = 0; oneUser < quantityPlayers; oneUser++){
        user_t newUser;

        string pathUsername = this->getPathUser(oneUser, "username");
        string pathPassword = this->getPathUser(oneUser, "password");

        newUser.username = this->parserJson->getString(pathUsername);
        newUser.password = this->parserJson->getString(pathPassword);

        newUser.playerParams = this->getPlayerParams(oneUser);

        this->gameData.playersParams.push_back(newUser);
    }   

    int sizeLevel = 1;


    Logger::getInstance()->log(DEBUG, "Se comienza a analizar la configuracion de los distintos niveles.");
    
    for(int numberLevel = 0; numberLevel < sizeLevel; numberLevel++){
        Logger::getInstance()->log(DEBUG, "Se comienza a analizar la configuracion del nivel " + to_string(numberLevel));
        string pathLevel = getPathLevel(numberLevel);
        int sizeStages = this->parserJson->getSizeArray(PATH_LEVEL);
        levelParams_t oneLevelParams;

        for(int numberStage = 0; numberStage < sizeStages; numberStage++){
            Logger::getInstance()->log(DEBUG, "Se comienza a analizar la configuracion del stage " + to_string(numberStage) + " para el nivel " + to_string(numberLevel));
            stageParams_t oneStageParams;

            string pathStage = getPathStage(numberLevel, numberStage);        
            
            string pathEnemiesBase = getPathStageEnemy(pathStage, -1, "");
            int sizeEnemies = this->parserJson->getSizeArray(pathEnemiesBase);

            //cout << "params " << pathStage << endl;
            //cout << "params " << pathEnemiesBase << endl;
            //cout << "params " << sizeEnemies << endl;
            
            unsigned int cantTotalType1 = 0;
            unsigned int cantTotalType2 = 0;

            unsigned int sizeScreenX = GameProvider::getWidth();
            unsigned int sizeScreenY = GameProvider::getHeight();

            for(int numberEnemy = 0; numberEnemy < sizeEnemies; numberEnemy++){
                Logger::getInstance()->log(DEBUG, "Se comienza a analizar el enemigo " + to_string(numberEnemy) + " del stage " + to_string(numberStage) + " para el nivel " + to_string(numberLevel));
            
                enemy_t oneEnemy;

                string pathEnemyType = getPathStageEnemy(pathStage, numberEnemy, "type");

                elementType_t typeEnemy = ENEMY_1;

                if (numberEnemy > 0)
                    typeEnemy = ENEMY_2;

                oneEnemy.type = typeEnemy;

                string pathEnemyQuantity = getPathStageEnemy(pathStage, numberEnemy, "quantity");

                //cout << pathEnemyQuantity << endl;
                int cantEnemy = this->parserJson->getUnsignedInt(pathEnemyQuantity); 

                //cout << cantEnemy << endl;

                if (cantEnemy >= 0){
                    oneEnemy.quantity = cantEnemy;
                } else {
                    oneEnemy.quantity = DEFAULT_ENEMY_QUANTITY;
                }

                string pathEnemySizeX = getPathStageEnemy(pathStage, numberEnemy, "sizeX");
                int sizeX = this->parserJson->getUnsignedInt(pathEnemySizeX);
                
                //cout << "El size x " << sizeX << endl;
                if (sizeX >= 0){
                    oneEnemy.size_x = sizeX;
                } else {
                    oneEnemy.size_x = DEFAULT_SIZE_X;
                }

                if (sizeX > sizeScreenX){
                    Logger::getInstance()->log(ERROR, "El largo del enemigo " + to_string(numberEnemy) + " supera el largo de la pantalla. Se settea este ultimo como su largo");
                    oneEnemy.size_x = sizeScreenX;
                }

                string pathEnemySizeY = getPathStageEnemy(pathStage, numberEnemy, "sizeY");
                int sizeY = this->parserJson->getUnsignedInt(pathEnemySizeY);
                if (sizeY >= 0){
                    oneEnemy.size_y = sizeY;
                } else {
                    oneEnemy.size_y = DEFAULT_SIZE_Y;
                }

                //cout << "El size y " << sizeY << endl;
                //cout << "le bg " << sizeScreenX << endl;

                if (sizeY > sizeScreenY){
                    Logger::getInstance()->log(ERROR, "El ancho del enemigo " + to_string(numberEnemy) + " supera el ancho de la pantalla. Se settea este ultimo como su ancho");
                    oneEnemy.size_y = sizeScreenY;
                }

                oneStageParams.totalEnemies.push_back(oneEnemy);
            }

            oneStageParams.stepsParams = getStep(oneStageParams.totalEnemies);
            oneLevelParams.stagesParams.push_back(oneStageParams);
        }

        this->gameData.levelParams.push_back(oneLevelParams);
    }    
}

void ConfigurationHandler::initializeDataClient(){

    size_t quantityPlayers = this->parserJson->getSizeArray(PATH_PLAYERS);

    //cout << "quant " << quantityPlayers << endl;
    GameProvider::setQuantityPlayers(quantityPlayers);
    
    vector<user_t> users (quantityPlayers);

    for (size_t oneUser = 0; oneUser < quantityPlayers; oneUser++){
        user_t newUser;

        newUser.playerParams = this->getPlayerParams(oneUser);

        this->gameData.playersParams.push_back(newUser);
    }   

    this->gameData.loginScreen = this->readLoginScreen();

    int sizeLevel = 1;

    Logger::getInstance()->log(DEBUG, "Se comienza a analizar la configuracion de los distintos niveles.");
    
    for(int numberLevel = 0; numberLevel < sizeLevel; numberLevel++){
        Logger::getInstance()->log(DEBUG, "Se comienza a analizar la configuracion del nivel " + to_string(numberLevel));
        string pathLevel = getPathLevel(numberLevel);
        int sizeStage = this->parserJson->getSizeArray(PATH_LEVEL);
        levelParams_t oneLevelParams;

        //cout << "pathLevel " << pathLevel << endl;
        //cout << "quantStages " << sizeStage << endl;

        for(int numberStage = 0; numberStage < sizeStage; numberStage++){
            Logger::getInstance()->log(DEBUG, "Se comienza a analizar la configuracion del stage " + to_string(numberStage) + " para el nivel " + to_string(numberLevel));
            stageParams_t oneStageParams;

            string pathStage = getPathStage(numberLevel, numberStage);

            //cout << "pathStage " << pathStage << endl;

            string pathTransitionInit = pathStage + "/transitionInit";
            //cout << "pathTransitionInit " << pathTransitionInit << endl;
            oneLevelParams.pathTransitionScreen.initPath = this->parserJson->getString(pathTransitionInit);
            //cout << "Esto " << this->parserJson->getString("/configuracion/level/0/transitionInit") << endl;

            //cout << "pathTransitionInit " << pathTransitionInit << endl;
            string pathTransitionEnd = pathStage + "/transitionEnd";
            oneLevelParams.pathTransitionScreen.endPath = this->parserJson->getString(pathTransitionEnd);

            string pathLayer1 = getPathStageLayer(pathStage, 1);
            oneStageParams.backgroundSources.layer1 = this->parserJson->getString(pathLayer1);

            string pathLayer2 = getPathStageLayer(pathStage, 2);
            oneStageParams.backgroundSources.layer2 = this->parserJson->getString(pathLayer2);

            string pathLayer3 = getPathStageLayer(pathStage, 3);
            oneStageParams.backgroundSources.layer3 = this->parserJson->getString(pathLayer3);

            string pathLayer4 = getPathStageLayer(pathStage, 4);
            oneStageParams.backgroundSources.layer4 = this->parserJson->getString(pathLayer4);
            
            string pathLayer5 = getPathStageLayer(pathStage, 5);
            oneStageParams.backgroundSources.layer5 = this->parserJson->getString(pathLayer5);

            string pathLayer6 = getPathStageLayer(pathStage, 6);
            oneStageParams.backgroundSources.layer6 = this->parserJson->getString(pathLayer6);

            string pathLayer7 = getPathStageLayer(pathStage, 7);
            oneStageParams.backgroundSources.layer7 = this->parserJson->getString(pathLayer7);            
            
            string pathEnemiesBase = getPathStageEnemy(pathStage, -1, "");
            int sizeEnemies = this->parserJson->getSizeArray(pathEnemiesBase);

            unsigned int sizeScreenX = GameProvider::getWidth();
            unsigned int sizeScreenY = GameProvider::getHeight();

            for(int numberEnemy = 0; numberEnemy < sizeEnemies; numberEnemy++){
                Logger::getInstance()->log(DEBUG, "Se comienza a analizar el enemigo " + to_string(numberEnemy) + " del stage " + to_string(numberStage) + " para el nivel " + to_string(numberLevel));
            
                enemy_t oneEnemy;

                string pathEnemySizeX = getPathStageEnemy(pathStage, numberEnemy, "sizeX");
                int sizeX = this->parserJson->getUnsignedInt(pathEnemySizeX);
                if (sizeX >= 0){
                    oneEnemy.size_x = sizeX;
                } else {
                    oneEnemy.size_x = DEFAULT_SIZE_X;
                }

                if (sizeX > sizeScreenX){
                    Logger::getInstance()->log(ERROR, "El largo del enemigo " + to_string(numberEnemy) + " supera el largo de la pantalla. Se settea este ultimo como su largo");
                    oneEnemy.size_x = sizeScreenX;
                }

                if (sizeX > sizeScreenY){
                    Logger::getInstance()->log(ERROR, "El ancho del enemigo " + to_string(numberEnemy) + " supera el ancho de la pantalla. Se settea este ultimo como su ancho");
                    oneEnemy.size_y = sizeScreenY;
                }

                string pathEnemySizeY = getPathStageEnemy(pathStage, numberEnemy, "sizeY");
                int sizeY = this->parserJson->getUnsignedInt(pathEnemySizeY);
                if (sizeY >= 0){
                    oneEnemy.size_y = sizeY;
                } else {
                    oneEnemy.size_y = DEFAULT_SIZE_Y;
                }
                
                string pathEnemySprite = getPathStageEnemy(pathStage, numberEnemy, "sprite");
                oneEnemy.sprite = this->parserJson->getString(pathEnemySprite);

                oneStageParams.totalEnemies.push_back(oneEnemy);
            }

            oneStageParams.stepsParams = getStep(oneStageParams.totalEnemies);
            oneLevelParams.stagesParams.push_back(oneStageParams);
        }

        this->gameData.levelParams.push_back(oneLevelParams);
    }
}

string ConfigurationHandler::getPathLoginScreen(string paramLogin){
    string pathLoginScreenParam = PATH_BASE_LOGIN_SCREEN + paramLogin;

    return pathLoginScreenParam;
}

loginScreen_t ConfigurationHandler::readLoginScreen(){

    loginScreen_t loginScreen;

    Logger::getInstance()->log(DEBUG, "Se comienzan a analizar los fondos para la pantalla de login.");

    string pathBackground = getPathLoginScreen("background");
    loginScreen.background = this->parserJson->getString(pathBackground);
    
    string pathNormalBox = getPathLoginScreen("normalBox");
    loginScreen.normalBox = this->parserJson->getString(pathNormalBox);

    string pathInvalidCredentialsBox = getPathLoginScreen("invalidCredentialsBox");
    loginScreen.invalidCredentialsBox = this->parserJson->getString(pathInvalidCredentialsBox);

    string pathFullGameBox = getPathLoginScreen("fullGameBox");
    loginScreen.fullGameBox = this->parserJson->getString(pathFullGameBox);

    string pathAlreadyLoggedIn = getPathLoginScreen("alreadyLoggedIn");
    loginScreen.alreadyLoggedIn = this->parserJson->getString(pathAlreadyLoggedIn);

    string pathUsername1 = getPathLoginScreen("username1");
    loginScreen.username1 = this->parserJson->getString(pathUsername1);

    string pathUsername2 = getPathLoginScreen("username2");
    loginScreen.username2 = this->parserJson->getString(pathUsername2);

    string pathPassword1 = getPathLoginScreen("password1");
    loginScreen.password1 = this->parserJson->getString(pathPassword1);

    string pathPassword2 = getPathLoginScreen("password2");
    loginScreen.password2 = this->parserJson->getString(pathPassword2);

    string pathLogin = getPathLoginScreen("login");
    loginScreen.login = this->parserJson->getString(pathLogin);

    return loginScreen;
}
