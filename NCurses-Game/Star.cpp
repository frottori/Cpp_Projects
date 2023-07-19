#include "Star.h"
#include "Player.h"
#include <random>

using namespace std;

Star :: Star(char Name,int color,int rows,int cols)
{
    this->rows = rows;
    this->cols = cols;
    this->Name = Name; 
    this->dx = -1;
    this->dy = -1;
    this->color = color; 
}

bool Star :: move(char** maze,WINDOW* win,const Player &p)
{
    int old_dx = this->dx;
    int old_dy = this->dy;
    bool move;
    this->random_position(maze,p,p,rows,cols);
    wmove(win,old_dy,old_dx);
    wprintw(win,".");
    wmove(win,this->dy,this->dx); 
    print_position(win);
    return true;
}