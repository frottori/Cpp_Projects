#include "Star.h"
#include "Player.h"

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
    return true;
}