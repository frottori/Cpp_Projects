#include "Engine.h"
#include <fstream>
#include <string>
#include <ncurses.h>

using namespace std;

Engine :: Engine(ifstream& file,int rows,int cols)
{
    //Players
    MPoteridis.setName('M');
    MPoteridis.setColor(1);
    LMalfoys.setName('L');
    LMalfoys.setColor(2);

    this->rows = rows;
    this->cols = cols;
    
    // Dynamic Allocation for maze
    maze = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        maze[i] = new char[this->cols];
    }

    //Read maze from file
    string line;
    int i = 0;
    while(getline(file,line))
    {
        strcat(maze[i], line.c_str());
        i++;
    }

    // Array that says if computer can go there
    grid = new bool*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        grid[i] = new bool[this->cols];
    }
    //all other positions true
    for(int i = 0; i < this->rows; i++)
        for(int j = 0; j < this->cols; j++)
            grid[i][j] = true;
}

void Engine :: start_game()
{
    //NCurses Window
    initscr();
    start_color(); 
    noecho();
    cbreak();
    curs_set(0);  // Show the cursor (0: invisible, 1: normal, 2: very visible)
    keypad(stdscr,true); //enable arrow keys

    // Define custom color pairs
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);    // Player 1 colour: Yellow on Black
    init_pair(2, COLOR_GREEN, COLOR_BLACK);     // Player 2 colour: Green on Black
    init_pair(3, COLOR_BLUE, COLOR_BLACK);     // Wall colour: Red on Black

    //Initialise positions of players
    MPoteridis.initial_position(maze,MPoteridis,rows,cols);
    LMalfoys.initial_position(maze,MPoteridis,rows,cols);
    
    //Print Maze with Players in postions
    for(int i=0; i < rows ; i++)
    {
       for(int j=0; j < cols; j++)
        {
            if(i == MPoteridis.getDy() && j == MPoteridis.getDx())
                MPoteridis.print_position(stdscr);
            else if(i == LMalfoys.getDy() && j == LMalfoys.getDx())
               LMalfoys.print_position(stdscr);
            else 
            {
                if(maze[i][j]=='*')
                {
                    attron(COLOR_PAIR(3));
                    printw("%c",maze[i][j]);
                    attroff(COLOR_PAIR(3));
                } 
                else 
                {
                    printw("%c",maze[i][j]);
                }     
            }     
        } 
        printw("\n");
    }
    // Move cursor in position of MPoteridis
    wmove(stdscr,MPoteridis.getDy(),MPoteridis.getDx());
    while(1)
    {
        bool move = MPoteridis.movePlayer(getch(),maze,stdscr,LMalfoys);
        if(move) //if move is acceptable then computer will move
            LMalfoys.moveComputer(maze,grid,stdscr,MPoteridis,rows,cols);
        refresh();
    }

    getch();
    endwin();
}