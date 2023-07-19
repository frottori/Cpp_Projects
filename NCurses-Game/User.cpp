#include "User.h"
#include "Player.h"

User :: User(char Name,int color) 
{
    this->Name = Name; 
    this->dx = -1;
    this->dy = -1;
    this->color = color;
}

bool User :: move(char** maze,WINDOW* win,const Player &p)
{
    int old_dx = this->dx;
    int old_dy = this->dy;
    bool move;
    switch(direction)
    {
        case KEY_UP: this->dy -= 1; break;
        case KEY_DOWN: this->dy += 1; break;
        case KEY_LEFT: this->dx -= 1; break;
        case KEY_RIGHT: this->dx += 1; break;
        case ' ' : move = true; break;
    }
    if(this->dx==p.getDx() && this->dy==p.getDy() || maze[this->dy][this->dx]=='*')
    {
       this->dx = old_dx;
       this->dy = old_dy;
       move = false;
    } 
    else
    {
        wmove(win,old_dy,old_dx);
        wprintw(win,".");
        wmove(win,this->dy,this->dx); 
        print_position(win);
        move = true;     
    }
    return move;
}

void User :: setDirection(int direction)
{
    this->direction = direction;
}