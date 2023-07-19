#include <iostream>
#include <fstream>
#include <string>
#include <ncurses.h>
#include <string.h>
#include "Player.h"
#define COLS 13
#define ROWS 23

using namespace std;

int main(int argc,char** argv)
{
    //Check arguments
    if (argc != 2)
    {
        cerr << "too many or none arguments" << endl;
        return 1;
    }

    //Open File
    ifstream mapFile(argv[1]);  
    if (!mapFile.is_open()) {
        cerr << "Error opening the file." << endl;
        return 1;
    }

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

    //Players
    Player MPoteridis('M',1);
    Player LMalfoys('L',2);

    // Dynamic Allocation for maze
    char** maze = new char*[ROWS];
    for (int i = 0; i < ROWS; i++) {
        maze[i] = new char[COLS];
    }

    //Read maze from file
    string line;
    int i = 0;
    while(getline(mapFile,line))
    {
        strcat(maze[i], line.c_str());
        i++;
    }

    //Initialise positions of players
    MPoteridis.initial_position(maze,MPoteridis);
    LMalfoys.initial_position(maze,MPoteridis);
    
    //Print Maze with Players in postions
    for(int i=0; i < ROWS ; i++)
    {
       for(int j=0; j < COLS; j++)
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
        MPoteridis.movePlayer(getch(),maze,stdscr,LMalfoys);
        LMalfoys.moveComputer();
        refresh();
    }
   
    mapFile.close();
    getch();
    endwin();
    return 0;
}