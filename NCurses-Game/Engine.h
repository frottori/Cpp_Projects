#ifndef ENGINE_H
#define ENGINE_H
#include <string>
#include <ncurses.h>
#include <fstream>
#include "User.h"
#include "Computer.h"

using namespace std;

class Engine
{
    private:
        char** maze;
        int rows, cols;
        User MPoteridis;
        Computer LMalfoys;
    public:
        Engine(ifstream& file,int rows,int cols);
        void start_game(); 
        void print_maze();
};

#endif