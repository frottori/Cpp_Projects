#include "Engine.h"
#include <fstream>
#include <string>
#include <ncurses.h>

using namespace std;

Engine :: Engine(ifstream& file,int rows,int cols)  : LMalfoys('L',2,rows, cols), MPoteridis('M',1), MagStar('&',4,rows,cols)
{

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
}

void Engine :: start_game()
{
    //NCurses Window Settings
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
    init_pair(4, COLOR_CYAN, COLOR_BLACK);     // Player 3 : Cyan on Black

    //Initialise positions of players
    MPoteridis.initial_position(maze,MPoteridis,MPoteridis,rows,cols);
    LMalfoys.initial_position(maze,MPoteridis,MPoteridis,rows,cols);
    MagStar.initial_position(maze,MPoteridis,LMalfoys,rows,cols);

    //Print Maze with Players in positions
    this->print_maze();
    
    // Move cursor in position of MPoteridis
    wmove(stdscr,MPoteridis.getDy(),MPoteridis.getDx());
    int ch;
    bool u_won, c_won;
    while( (ch = getch()) != 27)  // ASCII code for esc
    {
        MPoteridis.setDirection(ch);
        bool move = MPoteridis.move(maze,stdscr,LMalfoys);
        if(move) //if move is acceptable then computer will move
            LMalfoys.move(maze,stdscr,MPoteridis);
        refresh();
        u_won = player_won(MPoteridis,MagStar);
        c_won = player_won(LMalfoys,MagStar);
        if(u_won)
            end_screen(true);  //user won
        else if(c_won)
            end_screen(false); // computer won
    }

    endwin();
    exit(0);
}

void Engine :: print_maze()
{
    for(int i=0; i < rows ; i++)
    {
       for(int j=0; j < cols; j++)
        {
            if(i == MPoteridis.getDy() && j == MPoteridis.getDx())
                MPoteridis.print_position(stdscr);
            else if(i == LMalfoys.getDy() && j == LMalfoys.getDx())
               LMalfoys.print_position(stdscr);
            else if(i == MagStar.getDy() && j == MagStar.getDx())
                MagStar.print_position(stdscr);
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
}

bool Engine :: player_won(const Player &p1,const Player &p2)
{
    if(p1.getDx() == p2.getDx() && p1.getDy() == p2.getDy())  
        return true;
    else 
        return false;
}

void Engine :: end_screen(bool flag)
{
    clear();
    move(0,0);
    
    if(flag)  //user won
        printw("YOU WIN!\nPress any key to exit...");
    else 
        printw("YOU LOST!\nPress any key to exit...");
    refresh();
    getch();
    endwin();
    exit(0);
}

bool Engine :: start_screen()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    
    //get screen size
    int yMax, xMax;
    getmaxyx(stdscr,yMax,xMax);

    WINDOW* menuwin = newwin(4,15,0,0);
    box(menuwin,0,0);
    mvwprintw(menuwin,0,3,"Poteridis");
    refresh();
    wrefresh(menuwin);
    keypad(menuwin,true);

    string choices[2] = {"start","exit"};
    int choice, highlight = 0;

    while(1)
    {
        for(int i=0;i<2;i++)
        {
            if(i==highlight)
                wattron(menuwin,A_REVERSE);
                mvwprintw(menuwin,i+1,4,choices[i].c_str());
                wattroff(menuwin,A_REVERSE);
        }
        choice = wgetch(menuwin);
        switch(choice)
        {
            case KEY_UP: 
                highlight--;
                if (highlight==-1) 
                    highlight=0;
                break;
            case KEY_DOWN: 
                highlight++;
                if (highlight==3) 
                    highlight=2;
                break;
            default: break;
        }
        if(choice==10 && highlight==0) //ENTER and start
        {
            clear();
            endwin();
            return true;
        }
        if(choice==10 && highlight==1) //ENTER and exit
        {
            endwin();
            exit(0);
        }
    }
}