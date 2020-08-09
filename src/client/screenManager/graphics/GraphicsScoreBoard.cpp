#include "GraphicsScoreBoard.h"

GraphicsScoreBoard::GraphicsScoreBoard(){
    this->bar_ = new Image(GameProvider::getWidth(),200,"assets/scoreBoard/bar.png");

    this-> playerImages_ = new unordered_map < elementType_t, Image*> ();
    int playerImagesW = 150;
    int playerImagesH = 80;
    this-> playerImages_->emplace(PLAYER_1,new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player1.jpg"));
    this-> playerImages_->emplace(PLAYER_1_OUT,new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player1_D.jpg"));
    this-> playerImages_->emplace(PLAYER_1_G, new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player1_G.jpg"));
    this-> playerImages_->emplace(PLAYER_2, new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player2.jpg"));
    this-> playerImages_->emplace(PLAYER_2_OUT, new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player2_D.jpg"));
    this-> playerImages_->emplace(PLAYER_1_G, new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player2_G.jpg"));
    this-> playerImages_->emplace(PLAYER_3, new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player3.jpg"));
    this-> playerImages_->emplace(PLAYER_3_OUT, new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player3_D.jpg"));
    this-> playerImages_->emplace(PLAYER_3_G, new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player3_G.jpg"));
    this-> playerImages_->emplace(PLAYER_4,new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player4.jpg"));
    this-> playerImages_->emplace(PLAYER_4_OUT,new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player4_D.jpg"));
    this-> playerImages_->emplace(PLAYER_4_G,new Image(playerImagesW,playerImagesH,"assets/scoreBoard/players/player4_G.jpg"));
    
    this-> hearts_ = new unordered_map <int, Image*>();
    int heartsW = 100;
    int heartsH = 30;
    this->hearts_->emplace(0,new Image(heartsW, heartsH ,"assets/scoreBoard/hearts/hearts0.png"));
    this->hearts_->emplace(1,new Image(heartsW, heartsH ,"assets/scoreBoard/hearts/hearts1.png"));
    this->hearts_->emplace(2,new Image(heartsW, heartsH ,"assets/scoreBoard/hearts/hearts2.png"));
    this->hearts_->emplace(3,new Image(heartsW, heartsH,"assets/scoreBoard/hearts/hearts3.png"));

    this->energy_ = new unordered_map <int, Image*>();
    int energyW = 400;
    int energyH = 30;
    this->energy_->emplace(0,new Image(energyW,energyH,"assets/scoreBoard/energy/energy0.png"));
    this->energy_->emplace(1,new Image(energyW,energyH,"assets/scoreBoard/energy/energy1.png"));
    this->energy_->emplace(2,new Image(energyW,energyH,"assets/scoreBoard/energy/energy2.png"));
    this->energy_->emplace(3,new Image(energyW,energyH,"assets/scoreBoard/energy/energy3.png"));
    this->energy_->emplace(4,new Image(energyW,energyH,"assets/scoreBoard/energy/energy4.png"));
    this->energy_->emplace(5,new Image(energyW,energyH,"assets/scoreBoard/energy/energy5.png"));
    this->energy_->emplace(6,new Image(energyW,energyH,"assets/scoreBoard/energy/energy6.png"));
    this->energy_->emplace(7,new Image(energyW,energyH,"assets/scoreBoard/energy/energy7.png"));
    this->energy_->emplace(8,new Image(energyW,energyH,"assets/scoreBoard/energy/energy8.png"));
    this->energy_->emplace(9,new Image(energyW,energyH,"assets/scoreBoard/energy/energy9.png"));
    this->energy_->emplace(10,new Image(energyW,energyH,"assets/scoreBoard/energy/energy10.png"));
    this->energy_->emplace(11,new Image(energyW,energyH,"assets/scoreBoard/energy/energyBar.png"));

    this->scores_ = new unordered_map <elementType_t,TextBox*>();
    string path = "assets/scoreBoard/scoreButton.png";
    this->scores_->emplace(PLAYER_1, new TextBox(300,10,300,40,path.c_str(),path.c_str()));
    this->scores_->emplace(PLAYER_2, new TextBox(300,110,300,40,path.c_str(),path.c_str()));
    this->scores_->emplace(PLAYER_3, new TextBox(960,10,300,40,path.c_str(),path.c_str()));
    this->scores_->emplace(PLAYER_4, new TextBox(960,110,300,40,path.c_str(),path.c_str()));

    this->scores_->at(PLAYER_1)->setCenteringParameters(50,10,15,10);
    this->scores_->at(PLAYER_2)->setCenteringParameters(50,10,15,10);
    this->scores_->at(PLAYER_3)->setCenteringParameters(50,10,15,10);
    this->scores_->at(PLAYER_4)->setCenteringParameters(50,10,15,10);

    setScore(PLAYER_1,0);
    setScore(PLAYER_2,0);
    setScore(PLAYER_3,0);
    setScore(PLAYER_4,0);
}


void GraphicsScoreBoard::setScore(elementType_t player, int score){
    std::string cadena = "";
    cadena = static_cast<std::ostringstream*>(&(std::ostringstream() << score))->str();
    scores_->at(player)->setText(cadena);
}


void GraphicsScoreBoard::update(){
    this->bar_->renderCopy(0,0);
    
    this->playerImages_->at(PLAYER_1_G)->renderCopy(20,10);
    this->hearts_->at(3)->renderCopy(190,20);
    this->energy_->at(10)->renderCopy(190,60);
    
    this->playerImages_->at(PLAYER_2)->renderCopy(20,110);
    this->hearts_->at(3)->renderCopy(190,110);
    this->energy_->at(10)->renderCopy(190,160);
    
    this->playerImages_->at(PLAYER_3_OUT)->renderCopy(690,10);
    this->hearts_->at(3)->renderCopy(850,20);
    this->energy_->at(10)->renderCopy(850,60);
    
    this->playerImages_->at(PLAYER_4)->renderCopy(690,110);
    this->hearts_->at(3)->renderCopy(850,110);
    this->energy_->at(10)->renderCopy(850,160);

    this->scores_->at(PLAYER_1)->update(0,0,false);
    this->scores_->at(PLAYER_2)->update(0,0,false);
    this->scores_->at(PLAYER_3)->update(0,0,false);
    this->scores_->at(PLAYER_4)->update(0,0,false);
}