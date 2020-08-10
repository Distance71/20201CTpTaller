#include "GraphicsScoreBoard.h"

GraphicsScoreBoard::GraphicsScoreBoard(){
    this->bar_ = new Image(GameProvider::getWidth(),200,"assets/scoreBoard/bar.png");

    this-> playerImages_ = new unordered_map < elementType_t, Image*> ();
    int playerImagesW = 140;
    int playerImagesH = 80;
    this-> playerImages_->emplace(PLAYER_1,new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player1.jpg"));
    this-> playerImages_->emplace(PLAYER_1_OUT,new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player1_D.jpg"));
    this-> playerImages_->emplace(PLAYER_1_G, new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player1_G.jpg"));
    this-> playerImages_->emplace(PLAYER_2, new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player2.jpg"));
    this-> playerImages_->emplace(PLAYER_2_OUT, new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player2_D.jpg"));
    this-> playerImages_->emplace(PLAYER_2_G, new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player2_G.jpg"));
    this-> playerImages_->emplace(PLAYER_3, new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player3.jpg"));
    this-> playerImages_->emplace(PLAYER_3_OUT, new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player3_D.jpg"));
    this-> playerImages_->emplace(PLAYER_3_G, new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player3_G.jpg"));
    this-> playerImages_->emplace(PLAYER_4,new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player4.jpg"));
    this-> playerImages_->emplace(PLAYER_4_OUT,new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player4_D.jpg"));
    this-> playerImages_->emplace(PLAYER_4_G,new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player4_G.jpg"));
    
    this-> lives_ = new unordered_map <int, Image*>();
    int heartsW = 100;
    int heartsH = 30;
    this->lives_->emplace(0,new Image(heartsW, heartsH ,"assets/scoreBoard/hearts/hearts0.png"));
    this->lives_->emplace(1,new Image(heartsW, heartsH ,"assets/scoreBoard/hearts/hearts1.png"));
    this->lives_->emplace(2,new Image(heartsW, heartsH ,"assets/scoreBoard/hearts/hearts2.png"));
    this->lives_->emplace(3,new Image(heartsW, heartsH,"assets/scoreBoard/hearts/hearts3.png"));

    this->health_ = new unordered_map <int, Image*>();
    int energyW = 400;
    int energyH = 30;
    this->health_->emplace(0,new Image(energyW,energyH,"assets/scoreBoard/energy/energy0.png"));
    this->health_->emplace(1,new Image(energyW,energyH,"assets/scoreBoard/energy/energy1.png"));
    this->health_->emplace(2,new Image(energyW,energyH,"assets/scoreBoard/energy/energy2.png"));
    this->health_->emplace(3,new Image(energyW,energyH,"assets/scoreBoard/energy/energy3.png"));
    this->health_->emplace(4,new Image(energyW,energyH,"assets/scoreBoard/energy/energy4.png"));
    this->health_->emplace(5,new Image(energyW,energyH,"assets/scoreBoard/energy/energy5.png"));
    this->health_->emplace(6,new Image(energyW,energyH,"assets/scoreBoard/energy/energy6.png"));
    this->health_->emplace(7,new Image(energyW,energyH,"assets/scoreBoard/energy/energy7.png"));
    this->health_->emplace(8,new Image(energyW,energyH,"assets/scoreBoard/energy/energy8.png"));
    this->health_->emplace(9,new Image(energyW,energyH,"assets/scoreBoard/energy/energy9.png"));
    this->health_->emplace(10,new Image(energyW,energyH,"assets/scoreBoard/energy/energy10.png"));
    this->health_->emplace(11,new Image(energyW,energyH,"assets/scoreBoard/energy/energyBar.png"));

    this->scores_ = new unordered_map <elementType_t,TextBox*>();
    string path = "assets/scoreBoard/scoreButton.png";
    this->scores_->emplace(PLAYER_1, new TextBox(300,10,300,50,path.c_str(),path.c_str()));
    this->scores_->emplace(PLAYER_2, new TextBox(300,110,300,50,path.c_str(),path.c_str()));
    this->scores_->emplace(PLAYER_3, new TextBox(910,10,300,50,path.c_str(),path.c_str()));
    this->scores_->emplace(PLAYER_4, new TextBox(910,110,300,50,path.c_str(),path.c_str()));

    this->scores_->at(PLAYER_1)->setCenteringParameters(50,10,5,5);
    this->scores_->at(PLAYER_2)->setCenteringParameters(50,10,5,5);
    this->scores_->at(PLAYER_3)->setCenteringParameters(50,10,5,5);
    this->scores_->at(PLAYER_4)->setCenteringParameters(50,10,5,5);

    this->scores_->at(PLAYER_1)->setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
    this->scores_->at(PLAYER_2)->setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
    this->scores_->at(PLAYER_3)->setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
    this->scores_->at(PLAYER_4)->setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);

    this->players_ = new unordered_map <elementType_t,playerState_t>();
    
    this->scoreTable_ = new Image(GameProvider::getWidth(),GameProvider::getHeight(),"assets/scoreBoard/scoreTable.png");
    
    //precargo todo en gris

    playerState_t player1;
    player1.playerImage = PLAYER_1_G;
    player1.lives = 3;
    player1.health = 100;
    player1.score = 0;
    this->players_->emplace(PLAYER_1,player1);

    playerState_t player2;
    player2.playerImage = PLAYER_2_G;
    player2.lives = 3;
    player2.health = 100;
    player2.score = 0;
    this->players_->emplace(PLAYER_2,player2);

    playerState_t player3;
    player3.playerImage = PLAYER_3_G;
    player3.lives = 3;
    player3.health = 100;
    player3.score = 0;
    this->players_->emplace(PLAYER_3,player3);

    playerState_t player4;
    player4.playerImage = PLAYER_4_G;
    player4.lives = 3;
    player4.health = 100;
    player4.score = 0;
    this->players_->emplace(PLAYER_4,player4);

}


void GraphicsScoreBoard::setScore(elementType_t player, int score){
    std::string cadena = "";
    cadena = static_cast<std::ostringstream*>(&(std::ostringstream() << score))->str();
    scores_->at(player)->setText(cadena);
}

void GraphicsScoreBoard::updateScore(elementType_t playerImage,unsigned int lives,int health,int score){
    playerState_t player;
    player.playerImage = playerImage;
    player.lives= lives;
    player.health = health;
    player.score = score;
    
    if (playerImage == PLAYER_1 || playerImage == PLAYER_1_OUT){
        this->players_->erase(PLAYER_1);
        this->players_->emplace(PLAYER_1,player);
    }

    else if (playerImage== PLAYER_2 || playerImage== PLAYER_2_OUT){
        this->players_->erase(PLAYER_2);
        this->players_->emplace(PLAYER_2,player);
    }

    else if (playerImage== PLAYER_3 || playerImage == PLAYER_3_OUT){
        this->players_->erase(PLAYER_3);
        this->players_->emplace(PLAYER_3,player);
    }

    else{
         this->players_->erase(PLAYER_4);
        this->players_->emplace(PLAYER_4,player);
    }
}


int GraphicsScoreBoard::getHealthImageNumber(int health){
    cout<<health<<endl;
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
    this->bar_->renderCopy(0,0);

    //********Actualizo el jugador 1**********
    playerState_t player1 = this->players_->at(PLAYER_1);
    //imagen 
    this->playerImages_->at(player1.playerImage)->renderCopy(35,20);
    //vida
    this->lives_->at(player1.lives)->renderCopy(190,20);
   //puntaje
    this->setScore(PLAYER_1,player1.score);
    this->scores_->at(PLAYER_1)->update(0,0,false);
    //salud
    int healthImage1 = this->getHealthImageNumber(player1.health);
    cout <<healthImage1<< endl;
    this-> health_->at(healthImage1)->renderCopy(190,60);

    //********Actualizo el jugador 2**********
    playerState_t player2 = this->players_->at(PLAYER_2);
    //imagen 
    this->playerImages_->at(player2.playerImage)->renderCopy(35,110);
    //vida
    this->lives_->at(player2.lives)->renderCopy(190,110);
    //puntaje
    this->setScore(PLAYER_2,player2.score);
    this->scores_->at(PLAYER_2)->update(0,0,false);
    //salud
    int healthImage2 = this->getHealthImageNumber(player2.health);
    this-> health_->at(healthImage2)->renderCopy(190,160);

    //********Actualizo el jugador 3**********
    playerState_t player3 = this->players_->at(PLAYER_3);
    //imagen 
    this->playerImages_->at(player3.playerImage)->renderCopy(650,20);
    //vida
    this->lives_->at(player3.lives)->renderCopy(800,20);
    //puntaje
    this->setScore(PLAYER_3,player3.score);
    this->scores_->at(PLAYER_3)->update(0,0,false);
    //salud
    int healthImage3 = this->getHealthImageNumber(player3.health);
    this-> health_->at(healthImage3)->renderCopy(800,60);
    
    //********Actualizo el jugador 4**********
    playerState_t player4 = this->players_->at(PLAYER_4);
    //imagen 
    this->playerImages_->at(player4.playerImage)->renderCopy(650,110);
    //vida
    this->lives_->at(player4.lives)->renderCopy(800,110);
    //puntaje
    this->setScore(PLAYER_4,player4.score);
    this->scores_->at(PLAYER_4)->update(0,0,false);
    //salud
    int healthImage4 = this->getHealthImageNumber(player4.health);
    this->health_->at(healthImage4)->renderCopy(800,160);

}

void GraphicsScoreBoard::showScores(){
    cout << "entro"<<endl;
    
    string path = "assets/scoreBoard/scoreButton.png";
    
    this->scoreTable_->renderCopy(0,0);

    TextBox score1 = TextBox(550,300,400,80,path.c_str(),path.c_str());
    TextBox score2 = TextBox(550,400,400,80,path.c_str(),path.c_str());
    TextBox score3 = TextBox(550,500,400,80,path.c_str(),path.c_str());
    TextBox score4 = TextBox(550,600,400,80,path.c_str(),path.c_str());

    score1.setCenteringParameters(50,10,5,5);
    score2.setCenteringParameters(50,10,5,5);
    score3.setCenteringParameters(50,10,5,5);
    score4.setCenteringParameters(50,10,5,5);
    
    score1.setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
    score2.setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
    score3.setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);
    score4.setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",40);


    //Player1
    playerState_t player1 = this->players_->at(PLAYER_1);
    this->playerImages_->at(player1.playerImage)->renderCopy(350,300);
    score1.setText(static_cast<std::ostringstream*>(&(std::ostringstream() << player1.score))->str());
    score1.update(0,0,false);
    
    //player2
    playerState_t player2 = this->players_->at(PLAYER_2);
    this->playerImages_->at(player2.playerImage)->renderCopy(350,400);
    score2.setText(static_cast<std::ostringstream*>(&(std::ostringstream() << player2.score))->str());
    score2.update(0,0,false);
    
    
    //player3
    playerState_t player3 = this->players_->at(PLAYER_3);
    this->playerImages_->at(player3.playerImage)->renderCopy(350,500);
    score3.setText(static_cast<std::ostringstream*>(&(std::ostringstream() << player3.score))->str());
    score3.update(0,0,false);

    //player4
    playerState_t player4 = this->players_->at(PLAYER_4);
    this->playerImages_->at(player4.playerImage)->renderCopy(350,600);
    score4.setText(static_cast<std::ostringstream*>(&(std::ostringstream() << player4.score))->str());
    score4.update(0,0,false);

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

