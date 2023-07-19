#ifndef ENGINE_H
#define ENGINE_H
#include <string>
#include <ncurses.h>
#include <fstream>
#include "Player.h"

using namespace std;

class Engine
{
    private:
        char** maze;
        Player MPoteridis,LMalfoys;
    public:
        Engine(ifstream& file);
        void start_game(); 
};

#endif