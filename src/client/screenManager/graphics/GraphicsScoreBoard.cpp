#include "GraphicsScoreBoard.h"

GraphicsScoreBoard::GraphicsScoreBoard(int n){
    GameProvider::setQuantityPlayers(n);

    this-> playersNumber_ = n;
    
    this->bar_ = new Image("assets/scoreBoard/bar.png");

    this-> playerImages_ = new unordered_map < elementType_t, Image*> ();

    this-> playerImages_->emplace(PLAYER_1,new Image("assets/scoreBoard/players/player1.jpg"));
    this-> playerImages_->emplace(PLAYER_1_OUT,new Image("assets/scoreBoard/players/player1_D.jpg"));
    this-> playerImages_->emplace(PLAYER_1_DEAD,new Image("assets/scoreBoard/players/player1_R.png"));
    this-> playerImages_->emplace(PLAYER_2, new Image("assets/scoreBoard/players/player2.jpg"));
    this-> playerImages_->emplace(PLAYER_2_OUT, new Image("assets/scoreBoard/players/player2_D.jpg"));
    this-> playerImages_->emplace(PLAYER_2_DEAD,new Image("assets/scoreBoard/players/player2_R.png"));
    this-> playerImages_->emplace(PLAYER_3, new Image("assets/scoreBoard/players/player3.jpg"));
    this-> playerImages_->emplace(PLAYER_3_OUT, new Image("assets/scoreBoard/players/player3_D.jpg"));
    this-> playerImages_->emplace(PLAYER_3_DEAD,new Image("assets/scoreBoard/players/player3_R.png"));
    this-> playerImages_->emplace(PLAYER_4,new Image("assets/scoreBoard/players/player4.jpg"));
    this-> playerImages_->emplace(PLAYER_4_OUT,new Image("assets/scoreBoard/players/player4_D.jpg"));
    this-> playerImages_->emplace(PLAYER_4_DEAD,new Image("assets/scoreBoard/players/player4_R.png"));
    
    this-> lives_ = new unordered_map <int, Image*>();

    this->lives_->emplace(0,new Image("assets/scoreBoard/hearts/hearts0.png"));
    this->lives_->emplace(1,new Image("assets/scoreBoard/hearts/hearts1.png"));
    this->lives_->emplace(2,new Image("assets/scoreBoard/hearts/hearts2.png"));
    this->lives_->emplace(3,new Image("assets/scoreBoard/hearts/hearts3.png"));
    this->lives_->emplace(-1,new Image("assets/scoreBoard/hearts/hearts1G.png"));
    this->lives_->emplace(-2,new Image("assets/scoreBoard/hearts/hearts2G.png"));
    this->lives_->emplace(-3,new Image("assets/scoreBoard/hearts/hearts3G.png"));

    this->health_ = new unordered_map <int, Image*>();

    this->health_->emplace(0,new Image("assets/scoreBoard/energy/energy0.png"));
    this->health_->emplace(1,new Image("assets/scoreBoard/energy/energy1.png"));
    this->health_->emplace(2,new Image("assets/scoreBoard/energy/energy2.png"));
    this->health_->emplace(3,new Image("assets/scoreBoard/energy/energy3.png"));
    this->health_->emplace(4,new Image("assets/scoreBoard/energy/energy4.png"));
    this->health_->emplace(5,new Image("assets/scoreBoard/energy/energy5.png"));
    this->health_->emplace(6,new Image("assets/scoreBoard/energy/energy6.png"));
    this->health_->emplace(7,new Image("assets/scoreBoard/energy/energy7.png"));
    this->health_->emplace(8,new Image("assets/scoreBoard/energy/energy8.png"));
    this->health_->emplace(9,new Image("assets/scoreBoard/energy/energy9.png"));
    this->health_->emplace(10,new Image("assets/scoreBoard/energy/energy10.png"));

    this->health_->emplace(-1,new Image("assets/scoreBoard/energy/energy1G.png"));
    this->health_->emplace(-2,new Image("assets/scoreBoard/energy/energy2G.png"));
    this->health_->emplace(-3,new Image("assets/scoreBoard/energy/energy3G.png"));
    this->health_->emplace(-4,new Image("assets/scoreBoard/energy/energy4G.png"));
    this->health_->emplace(-5,new Image("assets/scoreBoard/energy/energy5G.png"));
    this->health_->emplace(-6,new Image("assets/scoreBoard/energy/energy6G.png"));
    this->health_->emplace(-7,new Image("assets/scoreBoard/energy/energy7G.png"));
    this->health_->emplace(-8,new Image("assets/scoreBoard/energy/energy8G.png"));
    this->health_->emplace(-9,new Image("assets/scoreBoard/energy/energy9G.png"));
    this->health_->emplace(-10,new Image("assets/scoreBoard/energy/energy10G.png"));

    string path = "assets/scoreBoard/scoreButton.png";
    this->scores_ = new unordered_map <elementType_t,TextBox*>();
    
    switch(this-> playersNumber_ ){
        
        case 1:

            this->scores_->emplace(PLAYER_1, new TextBox(300,20,300,50,path.c_str(),path.c_str()));

            this->scores_->at(PLAYER_1)->setCenteringParameters(50,10,5,5);
        
            this->scores_->at(PLAYER_1)->setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
            break;
            

        case 2:

            this->scores_->emplace(PLAYER_1, new TextBox(300,20,300,50,path.c_str(),path.c_str()));
            this->scores_->emplace(PLAYER_2, new TextBox(910,20,300,50,path.c_str(),path.c_str()));

            this->scores_->at(PLAYER_1)->setCenteringParameters(50,10,5,5);
            this->scores_->at(PLAYER_2)->setCenteringParameters(50,10,5,5);
        
            this->scores_->at(PLAYER_1)->setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
            this->scores_->at(PLAYER_2)->setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
            break;
        
        case 3:

            this->scores_->emplace(PLAYER_1, new TextBox(300,20,300,50,path.c_str(),path.c_str()));
            this->scores_->emplace(PLAYER_2, new TextBox(300,105,300,50,path.c_str(),path.c_str()));
            this->scores_->emplace(PLAYER_3, new TextBox(910,20,300,50,path.c_str(),path.c_str()));

            this->scores_->at(PLAYER_1)->setCenteringParameters(50,10,5,5);
            this->scores_->at(PLAYER_2)->setCenteringParameters(50,10,5,5);
            this->scores_->at(PLAYER_3)->setCenteringParameters(50,10,5,5);
        
            this->scores_->at(PLAYER_1)->setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
            this->scores_->at(PLAYER_2)->setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
            this->scores_->at(PLAYER_3)->setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
            break;
        
        case 4:
            this->scores_->emplace(PLAYER_1, new TextBox(300,20,300,50,path.c_str(),path.c_str()));
            this->scores_->emplace(PLAYER_2, new TextBox(300,105,300,50,path.c_str(),path.c_str()));
            this->scores_->emplace(PLAYER_3, new TextBox(910,20,300,50,path.c_str(),path.c_str()));
            this->scores_->emplace(PLAYER_4, new TextBox(910,105,300,50,path.c_str(),path.c_str()));

            this->scores_->at(PLAYER_1)->setCenteringParameters(50,10,5,5);
            this->scores_->at(PLAYER_2)->setCenteringParameters(50,10,5,5);
            this->scores_->at(PLAYER_3)->setCenteringParameters(50,10,5,5);
            this->scores_->at(PLAYER_4)->setCenteringParameters(50,10,5,5);

            this->scores_->at(PLAYER_1)->setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
            this->scores_->at(PLAYER_2)->setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
            this->scores_->at(PLAYER_3)->setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
            this->scores_->at(PLAYER_4)->setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
            break;
    }
    
    this->scoreTable_ = new Image("assets/scoreBoard/scoreTable.png");
    
    this->players_ = new unordered_map <elementType_t,playerState_t>();
    
    //precarga
    playerState_t player1;
    
    player1.playerImage = PLAYER_1;
    player1.lives = 3;
    player1.health = 100;
    player1.levelScore = 0;
    player1.totalScore = 0;
    this->players_->emplace(PLAYER_1,player1);

    if (this-> playersNumber_ >=2){
        playerState_t player2;
        player2.playerImage = PLAYER_2;
        player2.lives = 3;
        player2.health = 100;
        player2.levelScore = 0;
        player2.totalScore = 0;
        this->players_->emplace(PLAYER_2,player2);
    }

    if (this-> playersNumber_ >=3){
        playerState_t player3;
        player3.playerImage = PLAYER_3;
        player3.lives = 3;
        player3.health = 100;
        player3.levelScore = 0;
        player3.totalScore = 0;
        this->players_->emplace(PLAYER_3,player3);
    }

    if (this-> playersNumber_ == 4){
        playerState_t player4;
        player4.playerImage = PLAYER_4;
        player4.lives = 3;
        player4.health = 100;
        player4.levelScore = 0;
        player4.totalScore = 0;
        this->players_->emplace(PLAYER_4,player4);
    }
}


void GraphicsScoreBoard::setScore(elementType_t player, int score){
    std::string cadena = "";
    cadena = static_cast<std::ostringstream*>(&(std::ostringstream() << score))->str();
    scores_->at(player)->setText(cadena);
}


void GraphicsScoreBoard::updateScore(elementType_t playerImage,unsigned int lives,int health,int levelScore,int totalScore){

    playerState_t player;
    player.playerImage = playerImage;
    player.lives= lives;
    player.health = health;
    player.levelScore = levelScore;
    player.totalScore = totalScore;
    
    if (playerImage == PLAYER_1 || playerImage == PLAYER_1_OUT || playerImage==PLAYER_1_DEAD){
        this->players_->erase(PLAYER_1);
        this->players_->emplace(PLAYER_1,player);
    }

    else if (playerImage== PLAYER_2 || playerImage== PLAYER_2_OUT || playerImage==PLAYER_2_DEAD){
        this->players_->erase(PLAYER_2);
        this->players_->emplace(PLAYER_2,player);
    }

    else if (playerImage== PLAYER_3 || playerImage == PLAYER_3_OUT|| playerImage == PLAYER_3_DEAD){
        this->players_->erase(PLAYER_3);
        this->players_->emplace(PLAYER_3,player);
    }
    
    else if (playerImage== PLAYER_4 || playerImage == PLAYER_4_OUT|| playerImage == PLAYER_4_DEAD){
        this->players_->erase(PLAYER_4);
        this->players_->emplace(PLAYER_4,player);
    }
}


int GraphicsScoreBoard::getHealthImageNumber(int health){
    if (health == 0)
        return 0;
    else if (0 < health && health < 15)
        return 1;
    else if (15 <= health && health < 25)
        return 2;
    else if (25 <= health && health <35)
        return 3;
    else if (35 <= health && health < 45)
        return 4;
    else if  (45 <= health && health < 55)
        return 5;
    else if (55 <= health && health < 65)
        return 6;
    else if (65 <= health && health < 75)
        return 7;
    else if (75 <= health && health < 85)
        return 8;
    else if (85 <= health && health<  95)
        return 9;
    else 
        return 10;
}

void GraphicsScoreBoard::update(){

    playerState_t player1;
    playerState_t player2;
    playerState_t player3;
    playerState_t player4;

    int healthImage1;
    int healthImage2;
    int healthImage3;
    int healthImage4;


    switch (this-> playersNumber_ ){
        case 1:

            this->bar_->renderCopy(0,0,GameProvider::getWidth(),110);

            //********Actualizo el jugador 1**********
            player1 = this->players_->at(PLAYER_1);

            //imagen 
            this->playerImages_->at(player1.playerImage)->renderCopy(35,20,100,70);

            //vida
            if (player1.playerImage == PLAYER_1)
                this->lives_->at(player1.lives)->renderCopy(190,20,100,30);
            else
                this->lives_->at(player1.lives * -1)->renderCopy(190,20,100,30);

            //puntaje
            this->setScore(PLAYER_1,player1.totalScore);
            this->scores_->at(PLAYER_1)->update(0,0,false);

            //salud
            healthImage1 = this->getHealthImageNumber(player1.health);

            if (player1.playerImage == PLAYER_1)
                this->health_->at(healthImage1)->renderCopy(190,75,400,20);

            else
                this->health_->at(healthImage1*-1)->renderCopy(190,75,400,20);
            
            break;
        
        
        case 2:
            this->bar_->renderCopy(0,0,GameProvider::getWidth(),110);
            
            //********Actualizo el jugador 1**********
            player1 = this->players_->at(PLAYER_1);

            //imagen 
            this->playerImages_->at(player1.playerImage)->renderCopy(35,20,100,70);

            //vida
            if (player1.playerImage == PLAYER_1)
                this->lives_->at(player1.lives)->renderCopy(190,20,100,30);
            else
                this->lives_->at(player1.lives * -1)->renderCopy(190,20,100,30);

            //puntaje
            this->setScore(PLAYER_1,player1.totalScore);
            this->scores_->at(PLAYER_1)->update(0,0,false);

            //salud
            healthImage1 = this->getHealthImageNumber(player1.health);

            if (player1.playerImage == PLAYER_1)
                this->health_->at(healthImage1)->renderCopy(190,75,400,20);

            else
                this->health_->at(healthImage1*-1)->renderCopy(190,75,400,20);


            //********Actualizo el jugador 3**********
            player2 = this->players_->at(PLAYER_2);
            //imagen 
            this->playerImages_->at(player2.playerImage)->renderCopy(650,20,100,70);

            //vida
            if (player2.playerImage == PLAYER_2)
                this->lives_->at(player2.lives)->renderCopy(800,20,100,30);
            else
                this->lives_->at(player2.lives * -1)->renderCopy(800,20,100,30);

            //puntaje
            this->setScore(PLAYER_2,player2.totalScore);
            this->scores_->at(PLAYER_2)->update(0,0,false);
            //salud
            healthImage2 = this->getHealthImageNumber(player2.health);

            if (player2.playerImage == PLAYER_2)
                this-> health_->at(healthImage2)->renderCopy(800,75,400,20);
            else
                this-> health_->at(healthImage2 * -1)->renderCopy(800,75,400,20);
            
            break;
        
        case 3:
            this->bar_->renderCopy(0,0,GameProvider::getWidth(),200);

            //********Actualizo el jugador 1**********
            player1 = this->players_->at(PLAYER_1);

            //imagen 
            this->playerImages_->at(player1.playerImage)->renderCopy(35,20,100,70);

            //vida
            if (player1.playerImage == PLAYER_1)
                this->lives_->at(player1.lives)->renderCopy(190,20,100,30);
            else
                this->lives_->at(player1.lives * -1)->renderCopy(190,20,100,30);

            //puntaje
            this->setScore(PLAYER_1,player1.totalScore);
            this->scores_->at(PLAYER_1)->update(0,0,false);

            //salud
            healthImage1 = this->getHealthImageNumber(player1.health);

            if (player1.playerImage == PLAYER_1)
                this->health_->at(healthImage1)->renderCopy(190,75,400,20);

            else
                this->health_->at(healthImage1*-1)->renderCopy(190,75,400,20);


            //********Actualizo el jugador 2**********
           player2 = this->players_->at(PLAYER_2);

            //imagen 
            this->playerImages_->at(player2.playerImage)->renderCopy(35,105,100,70);

            //vida
            if ( player2.playerImage == PLAYER_2)
                this->lives_->at(player2.lives)->renderCopy(190,105,100,30);
            else
                this->lives_->at(player2.lives * -1)->renderCopy(190,105,100,30);

            //puntaje
            this->setScore(PLAYER_2,player2.totalScore);
            this->scores_->at(PLAYER_2)->update(0,0,false);

            //salud
            healthImage2 = this->getHealthImageNumber(player2.health);
            if ( player2.playerImage == PLAYER_2)
                this-> health_->at(healthImage2)->renderCopy(190,160,400,20);
            else 
                this-> health_->at(healthImage2 * -1)->renderCopy(190,160,400,20);

            //********Actualizo el jugador 3**********
            player3 = this->players_->at(PLAYER_3);
            //imagen 
            this->playerImages_->at(player3.playerImage)->renderCopy(650,20,100,70);

            //vida
            if (player3.playerImage == PLAYER_3)
                this->lives_->at(player3.lives)->renderCopy(800,20,100,30);
            else
                this->lives_->at(player3.lives * -1)->renderCopy(800,20,100,30);

            //puntaje
            this->setScore(PLAYER_3,player3.totalScore);
            this->scores_->at(PLAYER_3)->update(0,0,false);
            //salud
            healthImage3 = this->getHealthImageNumber(player3.health);

            if (player3.playerImage == PLAYER_3)
                this-> health_->at(healthImage3)->renderCopy(800,75,400,20);
            else
                this-> health_->at(healthImage3 * -1)->renderCopy(800,75,400,20);

            break;
        
        case 4:
            this->bar_->renderCopy(0,0,GameProvider::getWidth(),200);
            
            //********Actualizo el jugador 1**********
            player1 = this->players_->at(PLAYER_1);

            //imagen 
            this->playerImages_->at(player1.playerImage)->renderCopy(35,20,100,70);

            //vida
            if (player1.playerImage == PLAYER_1)
                this->lives_->at(player1.lives)->renderCopy(190,20,100,30);
            else
                this->lives_->at(player1.lives * -1)->renderCopy(190,20,100,30);

            //puntaje
            this->setScore(PLAYER_1,player1.totalScore);
            this->scores_->at(PLAYER_1)->update(0,0,false);

            //salud
            healthImage1 = this->getHealthImageNumber(player1.health);

            if (player1.playerImage == PLAYER_1)
                this->health_->at(healthImage1)->renderCopy(190,75,400,20);

            else
                this->health_->at(healthImage1*-1)->renderCopy(190,75,400,20);


            //********Actualizo el jugador 2**********
            player2 = this->players_->at(PLAYER_2);

            //imagen 
            this->playerImages_->at(player2.playerImage)->renderCopy(35,105,100,70);

            //vida
            if ( player2.playerImage == PLAYER_2)
                this->lives_->at(player2.lives)->renderCopy(190,105,100,30);
            else
                this->lives_->at(player2.lives * -1)->renderCopy(190,105,100,30);

            //puntaje
            this->setScore(PLAYER_2,player2.totalScore);
            this->scores_->at(PLAYER_2)->update(0,0,false);

            //salud
            healthImage2 = this->getHealthImageNumber(player2.health);
            if ( player2.playerImage == PLAYER_2)
                this-> health_->at(healthImage2)->renderCopy(190,160,400,20);
            else 
                this-> health_->at(healthImage2 * -1)->renderCopy(190,160,400,20);

            
            //********Actualizo el jugador 3**********
            player3 = this->players_->at(PLAYER_3);
            //imagen 
            this->playerImages_->at(player3.playerImage)->renderCopy(650,20,100,70);

            //vida
            if (player3.playerImage == PLAYER_3)
                this->lives_->at(player3.lives)->renderCopy(800,20,100,30);
            else
                this->lives_->at(player3.lives * -1)->renderCopy(800,20,100,30);

            //puntaje
            this->setScore(PLAYER_3,player3.totalScore);
            this->scores_->at(PLAYER_3)->update(0,0,false);
            //salud
            healthImage3 = this->getHealthImageNumber(player3.health);

            if (player3.playerImage == PLAYER_3)
                this-> health_->at(healthImage3)->renderCopy(800,75,400,20);
            else
                this-> health_->at(healthImage3 * -1)->renderCopy(800,75,400,20);


            //********Actualizo el jugador 4**********
            player4 = this->players_->at(PLAYER_4);
            //imagen 
            this->playerImages_->at(player4.playerImage)->renderCopy(650,105,100,70);

            //vida
            if (player4.playerImage == PLAYER_4)
                this->lives_->at(player4.lives)->renderCopy(800,110,100,30);
            else
                this->lives_->at(player4.lives *-1)->renderCopy(800,110,100,30);

            //puntaje
            this->setScore(PLAYER_4,player4.totalScore);
            this->scores_->at(PLAYER_4)->update(0,0,false);

            //salud
            healthImage4 = this->getHealthImageNumber(player4.health);

            if (player4.playerImage == PLAYER_4)
                this->health_->at(healthImage4)->renderCopy(800,160,400,20);
            else
                this->health_->at(healthImage4 * -1)->renderCopy(800,160,400,20);
            
            break;
    }
}
    

void GraphicsScoreBoard::showScores(){
    
    string path = "assets/scoreBoard/scoreButton.png";
    
    this->scoreTable_->renderCopy(0,0,GameProvider::getWidth(),GameProvider::getHeight());

    TextBox levelScore1 = TextBox(470,350,220,60,path.c_str(),path.c_str());
    TextBox levelScore2 = TextBox(470,430,220,60,path.c_str(),path.c_str());
    TextBox levelScore3 = TextBox(470,510,220,60,path.c_str(),path.c_str());
    TextBox levelScore4= TextBox (470,590,220,60,path.c_str(),path.c_str());

    levelScore1.setCenteringParameters(50,10,5,5);
    levelScore2.setCenteringParameters(50,10,5,5);
    levelScore3.setCenteringParameters(50,10,5,5);
    levelScore4.setCenteringParameters(50,10,5,5);
    
    levelScore1.setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
    levelScore2.setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
    levelScore3.setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
    levelScore4.setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);

    TextBox totalScore1 = TextBox(720,350,220,60,path.c_str(),path.c_str());
    TextBox totalScore2 = TextBox(720,430,220,60,path.c_str(),path.c_str());
    TextBox totalScore3 = TextBox(720,510,220,60,path.c_str(),path.c_str());
    TextBox totalScore4= TextBox(720,590,220,60,path.c_str(),path.c_str());

    totalScore1.setCenteringParameters(50,10,5,5);
    totalScore2.setCenteringParameters(50,10,5,5);
    totalScore3.setCenteringParameters(50,10,5,5);
    totalScore4.setCenteringParameters(50,10,5,5);
    
    totalScore1.setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
    totalScore2.setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
    totalScore3.setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
    totalScore4.setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);


    //Player1
    try{
        
        playerState_t player1 = this->players_->at(PLAYER_1);
        this->playerImages_->at(player1.playerImage)->renderCopy(350,350,100,70);
        levelScore1.setText(static_cast<std::ostringstream*>(&(std::ostringstream() << player1.levelScore))->str());
        levelScore1.update(0,0,false);
        totalScore1.setText(static_cast<std::ostringstream*>(&(std::ostringstream() << player1.totalScore))->str());
        totalScore1.update(0,0,false);
        
        //player2
        if(this->playersNumber_>=2){
            playerState_t player2 = this->players_->at(PLAYER_2);
            this->playerImages_->at(player2.playerImage)->renderCopy(350,430,100,70);
            levelScore2.setText(static_cast<std::ostringstream*>(&(std::ostringstream() << player2.levelScore))->str());
            levelScore2.update(0,0,false);
            totalScore2.setText(static_cast<std::ostringstream*>(&(std::ostringstream() << player2.totalScore))->str());
            totalScore2.update(0,0,false);
        }
        
        
        //player3
        if(this->playersNumber_>=3){
            playerState_t player3 = this->players_->at(PLAYER_3);
            this->playerImages_->at(player3.playerImage)->renderCopy(350,510,100,70);
            levelScore3.setText(static_cast<std::ostringstream*>(&(std::ostringstream() << player3.levelScore))->str());
            levelScore3.update(0,0,false);
            totalScore3.setText(static_cast<std::ostringstream*>(&(std::ostringstream() << player3.totalScore))->str());
            totalScore3.update(0,0,false);
        }

        //player4
        if(this->playersNumber_== 4){
            playerState_t player4 = this->players_->at(PLAYER_4);
            this->playerImages_->at(player4.playerImage)->renderCopy(350,590,100,70);
            levelScore4.setText(static_cast<std::ostringstream*>(&(std::ostringstream() << player4.levelScore))->str());
            levelScore4.update(0,0,false);
            totalScore4.setText(static_cast<std::ostringstream*>(&(std::ostringstream() << player4.totalScore))->str());
            totalScore4.update(0,0,false);
        }
    }
    
    catch (const std::out_of_range& oor){
        std::cerr << "Out of Range error in GraphicsScoreBoard showScores " << oor.what() << '\n';
    } 

}

GraphicsScoreBoard::~GraphicsScoreBoard(){
    delete this->bar_;
    this-> playerImages_ ->clear();
    delete this->playerImages_;
    this->lives_->clear();
    delete this->lives_;
    this->scores_->clear();
    delete this->scores_;
    this->players_->clear();
    delete this->players_;
    delete this->scoreTable_;
}

