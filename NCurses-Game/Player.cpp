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

bool Player :: movePlayer(int direction,char** maze,WINDOW* win,const Player &p)
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
    if(this->dx==p.dx && this->dy==p.dy || maze[this->dy][this->dx]=='*')
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

bool Player :: isValid(const Player &p,bool** grid,char** maze,int y,int x,int rows,int cols){
    if(x < 0 || x >= cols || y < 0 || y >= rows) 
        return false; //if its out of bounds
    if(maze[y][x] == '*')
        return false;
    if(x == p.dx && y==p.dy)
        return false;
  return grid[y][x];  //else it can move if the space is true
}

void Player :: moveComputer(char** maze,bool** grid,WINDOW* win,const Player &p,int rows,int cols)
{
    int old_dx = this->dx;
    int old_dy = this->dy;
    //current position false (it can't move there)
    grid[this->dy][this->dx] = false; 

    //All possible Options of moving
    vector<pair<int,int> > allOptions; //first = dy, second = dx;
    allOptions.push_back(make_pair(1,0));   // down
    allOptions.push_back(make_pair(-1,0));  // up
    allOptions.push_back(make_pair(0,1));   // right
    allOptions.push_back(make_pair(0,-1));  // left

    //options after conditions met
    vector<pair<int, int> > options;  //dy,dx
    for (int i = 0; i < allOptions.size(); i++) {
        int newY = this->dy + allOptions[i].first;
        int newX = this->dx + allOptions[i].second;
        if(isValid(p,grid,maze,newY,newX,rows,cols))
            options.push_back(make_pair(newY, newX));
    }

    if (!options.empty()) {
        // Generate a random index to select a random option
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, options.size() - 1);
        int randomIndex = dis(gen);

        // Get the randomly selected option
        pair<int, int> option = options[randomIndex];
        this->dy = option.first;
        this->dx = option.second;
        wmove(win,old_dy,old_dx);
        wprintw(win,".");
        wmove(win,this->dy,this->dx); 
        print_position(win);
        grid[this->dy][this->dx] = false;
    }
    else {
        return;
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

int Player :: getColor()
{
    return this->color;
}

void Player :: setColor(int color)
{
    this->color = color;
}