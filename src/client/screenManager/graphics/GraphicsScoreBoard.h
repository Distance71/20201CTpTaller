#ifndef _GRAPHICS_SCORE_BOARD_
#define _GRAPHICS_SCORE_BOARD_

#include "../../../common/providers/GameProvider.h"
#include "graphicElements/Image.h"
#include "graphicElements/TextBox.h"
#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>

class GraphicsScoreBoard {
    private:     
        Image* bar_;
        unordered_map <elementType_t,Image*>* playerImages_;
        unordered_map <int,Image*>* hearts_;
        unordered_map <int,Image*>* energy_;
        unordered_map <elementType_t,TextBox*>* scores_;
    
    public:  
        GraphicsScoreBoard();
        void setScore(elementType_t player, int score);
        void update();
        //void setScore(elementType_t player, int score);
};

#endif