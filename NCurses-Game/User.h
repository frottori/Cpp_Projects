#ifndef USER_H
#define USER_H
#include "Player.h"

class User : public Player
{
    private:
        int direction;
    public:
        User(char Name,int colour);
        bool move(char** maze,WINDOW*,const Player&);
        void setDirection(int direction);
};
#endif