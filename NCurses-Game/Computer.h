#ifndef COMPUTER_H
#define COMPUTER_H
#include "Player.h"

class Computer : public Player
{
    private:
        bool** grid;
        int rows,cols;
    public:
        Computer(char Name,int color,int rows,int cols);
        bool move(char** maze,WINDOW*,const Player&);
        bool isValid(const Player &p,char** maze,int y,int x);
};
#endif