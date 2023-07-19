#include <iostream>
#include <fstream>
#include "Engine.h"

using namespace std;

int main(int argc,char** argv)
{
    //Check arguments
    if (argc != 2)
    {
        cerr << "Too many or none arguments" << endl;
        return 1;
    }

    //Open File
    ifstream mapFile(argv[1]);  
    if (!mapFile.is_open()) {
        cerr << "Error opening the file." << endl;
        return 1;
    }
    // calculate rows and cols from file
    string line;
    int rows = 0;
    while(getline(mapFile,line))
    {
        rows++;
    }
    int cols = static_cast<int>(line.length());

    // resets the file pointer to the beginning of the file
    mapFile.clear();
    mapFile.seekg(0, ios::beg);

    Engine e(mapFile,rows,cols);
    bool start = e.start_screen("New Game");
    if(start)
        e.start_game();
  
    mapFile.close();
    return 0;
}