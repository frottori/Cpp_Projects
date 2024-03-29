#ifndef ENGINE_H
#define ENGINE_H
#include <ncurses.h>
#include <fstream>
#include <string>
#include "User.h"
#include "Computer.h"
#include "Star.h"

using namespace std;

class Engine
{
    private:
        char** maze;
        int rows, cols;
        User MPoteridis;
        Computer LMalfoys;
        Star MagStar;
    public:
        Engine(ifstream& file,int rows,int cols);
        void start_game(); 
        bool start_screen(string msg);
        void end_screen(bool flag);
        void print_maze();
        bool player_won(const Player &p1,const Player &p2);
};

#endif