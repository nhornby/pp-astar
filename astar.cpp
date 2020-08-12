#include "Map.h"

using namespace std;

/* astar.cpp
 * 
 * Runs a program that:
 * 1. Prints the input file in a user-friendly way
 * 2. Solve the input file according to any arguments passed in
 * 3. Prints the solved map in a user-friendly way
 * 
 * Examples:
 * Usage: ./astar.exe map.txt
 *        ./astar.exe map.txt --diag
 *        ./astar.exe map.txt --debug
 *        ./astar.exe map.txt --diag --debug
 * 
 * Author: Nolan Hornby
 * Date: Tuesday, August 11th 2020
 * University of Michigan
 * Class of 2023
 */

bool valid_file(string file)
{
    ifstream is(file);
    return is.is_open();
}

int main(int argc, char* argv[])
{
    bool debug = false;
    bool diag = false;
    
    try {
        //Map file argument
        if(argc < 2) {throw invalid_argument("Map file '' cannot be opened.");}
        if(!valid_file(argv[1])) {throw invalid_argument("Map file '" + string(argv[1]) + "' cannot be opened.");}

        //Additional "--" arguments
        for(int a = 2; a < argc; a++)
        {
            if(string(argv[a]) == "--debug") {debug = true;}
            else if(string(argv[a]) == "--diag") {diag = true;}
            else {throw invalid_argument("Argument " + string(argv[a]) + " is invalid.");}
        }
    } catch(const invalid_argument &e) {
        cout << e.what() << endl;
        cout << "usage: ./astar.exe map.txt [arg1] [arg2] [...]" << endl;
        return 1;
    }

    Map m(argv[1]);
    m.print_map();
    m.solve_map(debug, diag);
    m.print_map();

    return 0;
}