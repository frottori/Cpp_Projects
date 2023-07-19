#ifndef PLAYER_H
#define PLAYER_H
#include <ncurses.h>

class Player
{
    protected:
        char Name;
        int dx;  //col
        int dy;  //row
        int color;
    public:
        Player();
        Player(char Name,int color);
        void random_position(char** maze,const Player&,const Player&,int rows,int cols);
        virtual bool move(char** maze ,WINDOW*,const Player&) = 0;
        void print_position(WINDOW*);
        // getters and setters
        int getName();
        void setName(int Name);
        int getDx() const;
        void setDx(int dx);
        int getDy() const;
        void setDy(int dy);
        int getColor();
        void setColor(int color);
};
#endif