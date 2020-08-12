Personal Project
=======================
A* Pathfinding

Author: Nolan Hornby <nhornby@umich.edu> 
Date: Tuesday, August 11th, 2020

# Purpose
This program uses the A* search algorithm to solve mazes/find the optimal path from start to finish given a map including free space and barriers.

# Quick start
```console
$ g++ astar.cpp -o astar.exe
./astar.exe inputexample.txt
```
Extra arguments such as --diag and --debug can be added.
--diag allows diagonal steps to be made.
--debug shows each step, with ? symbols representing the Nodes in the open set.

# Example Input File ("inputexample.txt")
```console
6 7
0 0 0 0 0 0
0 1 0 0 1 0
0 1 0 S 1 0
0 1 0 0 1 0
0 1 1 1 1 0
0 0 0 E 0 0
0 0 0 0 0 0
```

# Example Output
```console
============
            
  #     #   
  #   S #   
  #     #   
  # # # #   
      E     
            
============
============
        .   
  #   . # . 
  #   S # . 
  #     # . 
  # # # # . 
      E .   
            
============
```
