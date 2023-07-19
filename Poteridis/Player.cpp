#include "Player.h"
#include <random>
#include <ncurses.h>
#define COLS 13
#define ROWS 23

using namespace std;

Player :: Player()
{
    
}

Player :: Player(char Name,int color)
{
    this->Name = Name; 
    this->dx = -1;
    this->dy = -1;
    this->color = color;
}

void Player :: initial_position(char** maze,const Player &p)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> rangedx(0, COLS - 1); 
    uniform_int_distribution<int> rangedy(0, ROWS - 1); 

    int x = rangedx(gen); 
    int y = rangedy(gen);

    if(maze[y][x] == '*' || x == p.dx && y == p.dy)  //if it is wall or the same position as other player 
        initial_position(maze,p);
    else 
    {
        this->dx = x;
        this->dy = y;
    }    
}

void Player :: movePlayer(int direction,char** maze,WINDOW* win,const Player &p)
{
    int old_dx = this->dx;
    int old_dy = this->dy;
    if(direction == KEY_UP && maze[this->dy-1][this->dx]!='*')
        this->dy = this->dy - 1;
    if(direction == KEY_DOWN && maze[this->dy+1][this->dx]!='*')
        this->dy = this->dy + 1;
    if(direction == KEY_LEFT && maze[this->dy][this->dx - 1]!='*')
        this->dx = this->dx - 1;
    if(direction == KEY_RIGHT && maze[this->dy][this->dx + 1]!='*')
        this->dx = this->dx + 1;
    if(this->dx==p.dx && this->dy==p.dy)
    {
       this->dx = old_dx;
       this->dy = old_dy;
    } 
    else
    {
        wmove(win,old_dy,old_dx);
        wprintw(win,".");
        wmove(win,this->dy,this->dx); 
        print_position(win);
    }
}

void Player :: moveComputer()
{

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

int Player :: getDx()
{
    return this->dx;
}

void Player :: setDx(int dx)
{
    this->dx = dx;
}

int Player :: getDy()
{
    return this->dy;
}

void Player :: setDy(int dy)
{
    this->dy = dy;
}