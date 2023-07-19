#include "Computer.h"
#include "Player.h"
#include <random>

using namespace std;

Computer :: Computer(char Name,int color,int rows,int cols)
{
    this->rows = rows;
    this->cols = cols;
    this->Name = Name; 
    this->dx = -1;
    this->dy = -1;
    this->color = color;
    // Array that says if computer can go there
    grid = new bool*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        grid[i] = new bool[this->cols];
    }
    //all positions true at the start
    for(int i = 0; i < this->rows; i++)
        for(int j = 0; j < this->cols; j++)
            grid[i][j] = true;
}

bool Computer :: isValid(const Player &p,char** maze,int y,int x){
    if(x < 0 || x >= cols || y < 0 || y >= rows) 
        return false; //if its out of bounds
    if(maze[y][x] == '*')
        return false;
    if(x == p.getDx() && y==p.getDy())
        return false;
  return grid[y][x];  //else it can move if the space is true
}

bool Computer :: move(char** maze,WINDOW* win,const Player &p)
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
        if(isValid(p,maze,newY,newX))
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
        return true;  //option to move
    }
    else {
        return false; //no option to move
    }
}