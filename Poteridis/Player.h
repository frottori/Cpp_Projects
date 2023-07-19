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
        Player(char,int);
        void initial_position(char**,const Player&);
        void movePlayer(int,char**,WINDOW*,const Player&);
        void moveComputer();
        void print_position(WINDOW*);

        // getters and setters
        int getName();
        void setName(int);
        int getDx();
        void setDx(int);
        int getDy();
        void setDy(int);
        int getColor();
        void setColor(int);
};
#endif