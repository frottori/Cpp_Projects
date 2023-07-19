#include "Player.h"
#include <random>
#include <ncurses.h>
#include <vector>

using namespace std;

Player :: Player()
{
    this->dx = -1;
    this->dy = -1;
}

Player :: Player(char Name,int color)
{
    this->Name = Name; 
    this->dx = -1;
    this->dy = -1;
    this->color = color;
}

void Player :: initial_position(char** maze,const Player &p,int rows,int cols)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> rangedx(0, cols - 1); 
    uniform_int_distribution<int> rangedy(0, rows - 1); 

    int x = rangedx(gen); 
    int y = rangedy(gen);

    if(maze[y][x] == '*' || x == p.dx && y == p.dy)  //if it is wall or the same position as other player 
        initial_position(maze,p,rows,cols);
    else 
    {
        this->dx = x;
        this->dy = y;
    }    
}

void Player :: print_position(WINDOW* win)
{
    attron(COLOR_PAIR(color));
    wprintw(win,"%c",this->getName());
    attroff(COLOR_PAIR(color));
}

int Player :: getName()
{
    return this->Name;
}

void Player :: setName(int Name)
{
    this->Name = Name;
}

int Player :: getDx() const
{
    return this->dx;
}

void Player :: setDx(int dx) 
{
    this->dx = dx;
}

int Player :: getDy() const
{
    return this->dy;
}

void Player :: setDy(int dy)
{
    this->dy = dy;
}

int Player :: getColor()
{
    return this->color;
}

void Player :: setColor(int color)
{
    this->color = color;
}