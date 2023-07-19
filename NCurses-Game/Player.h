#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <ncurses.h>

class Player
{
    private:
        char Name;
        int dx;  //col
        int dy;  //row
        int color;
    public:
        Player();
        Player(char Name,int color);
        void initial_position(char** maze,const Player&,int rows,int cols);
        bool movePlayer(int direction,char** maze ,WINDOW*,const Player&);
        void moveComputer(char** maze,bool** grid,WINDOW*,const Player&,int rows,int cols);
        void moveStar();
        void print_position(WINDOW*);
        bool isValid(const Player &p,bool** grid,char** maze,int y,int x,int rows,int cols);

        // getters and setters
        int getName();
        void setName(int Name);
        int getDx();
        void setDx(int dx);
        int getDy();
        void setDy(int dy);
        int getColor();
        void setColor(int color);
};
#endif