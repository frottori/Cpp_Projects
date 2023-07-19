#ifndef STAR_H
#define STAR_H
#include "Player.h"

class Star : public Player
{
    private:
        int rows,cols;
    public:
        Star(char Name,int color,int rows,int cols);
        bool move(char** maze,WINDOW*,const Player&);
};
#endif