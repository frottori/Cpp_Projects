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
    switch(direction)
    {
        case KEY_UP: this->dy -= 1; break;
        case KEY_DOWN: this->dy += 1; break;
        case KEY_LEFT: this->dx -= 1; break;
        case KEY_RIGHT: this->dx += 1; break;
    }
    if(this->dx==p.getDx() && this->dy==p.getDy() || maze[this->dy][this->dx]=='*')
    {
       this->dx = old_dx;
       this->dy = old_dy;
       return false;    //no acceptable move
    } 
    else
    {
        wmove(win,old_dy,old_dx);
        wprintw(win,".");
        wmove(win,this->dy,this->dx); 
        print_position(win);
        return true; //acceptable move
    }
}

void User :: setDirection(int direction)
{
    this->direction = direction;
}