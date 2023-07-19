#include <iostream>
#include <fstream>
#include "Engine.h"

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

    Engine e(mapFile);
    e.start_game();
  
    mapFile.close();
    return 0;
}