#ifndef _GRAPHICS_SCORE_BOARD_
#define _GRAPHICS_SCORE_BOARD_

#include "../../../common/providers/GameProvider.h"
#include "graphicElements/Image.h"
#include "graphicElements/TextBox.h"
#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class GraphicsScoreBoard {
    private:     
        Image* bar_;
        unordered_map <elementType_t,Image*>* playerImages_;
        unordered_map <int,Image*>* lives_;
        unordered_map <int,Image*>* health_;
        unordered_map <elementType_t,TextBox*>* scores_;
        void setScore(elementType_t player, int score);
        unordered_map <elementType_t,playerState_t> * players_;
        int getHealthImageNumber(int health);
        Image* scoreTable_;
    public:  
        GraphicsScoreBoard();
        ~GraphicsScoreBoard();
        void updateScore(elementType_t playerImage,unsigned int lives,int health,int levelScore,int totalScore);
        void update();
        void showScores();
};

#endif