#ifndef MAP_H
#define MAP_H

#include "Node.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

/* Map.h
 * 
 * Map contains a dynamically-allocated matrix of Nodes.
 * Class contains functions to print and solve the map.
 * 
 * Node ** map: A 2D array of Nodes
 * Node * start: Points to a Node in map
 * Node * end: Points to a Node in map
 * int width: Width of map
 * int height: Height of map
 * 
 * Author: Nolan Hornby
 * Date: Tuesday, August 11th 2020
 * University of Michigan
 * Class of 2023
 */ 

class Map {
public:
    Map(std::string inputfile) : start(nullptr), end(nullptr) {
        std::ifstream is(inputfile);
        is >> width >> height;

        map = new Node*[height];
        for(int i = 0; i < height; ++i) 
        {
            map[i] = new Node[width];
            for(int j = 0; j < width; ++j) 
            {
                char x;
                is >> x;

                Node n;
                n.row = i;
                n.col = j;

                if(x == '1') {n.type = 1;}
                else {n.type = 0;}
                if(x == 'S') {start = &map[i][j];}
                if(x == 'E') {end = &map[i][j];}

                map[i][j] = n;
            }
        }
    }
    ~Map() {
        for(int i = 0; i < height; ++i) {delete [] map[i];}
        delete [] map;
    }
    //REQUIRES: debug is T/F, Diag is T/F
    //MODIFIES: node ** map, sets all nodes along the optimal path to type "2"
    //EFFECTS: solves the map according to input arguments
    void solve_map(bool debug, bool diag)
    {
        if(start == nullptr || end == nullptr) {return;}

        std::vector<Node *> open = {start};
        std::vector<Node *> closed;
        
        int count = 0;

        while(open.size() > 0)
        {
            count++;
            if(debug) {print_map_debug(open);}

            sort(open.begin(), open.end(), [](const Node * a, const Node * b) {return a->f < b->f;});
            Node * current = open[0];
            open.erase(open.begin());
            closed.push_back(current);

            if(current == end)
            {
                if(debug) {std::cout << count << " calculation cycles to solve." << std::endl;}

                int length = 1;
                Node * temp = end->parent;
                while(temp != start)
                {
                    length++;
                    temp->type = 2;
                    temp = temp->parent;
                }

                if(debug) {std::cout << "Length: " << length << " steps." << std::endl;}

                return;
            }

            for(int rr = -1; rr <= 1; rr++)
            {
                for(int cc = -1; cc <= 1; cc++)
                {
                    if(rr == 0 && cc == 0) {continue;}
                    if((rr + cc) % 2 == 0 && !diag) {continue;}
                    if(current->row + rr >= height || current->row + rr < 0) {continue;}
                    if(current->col + cc >= width || current->col + cc < 0) {continue;}
                    if(map[current->row + rr][current->col + cc].type != 0) {continue;}

                    Node * child = &map[current->row + rr][current->col + cc];

                    if(child->is_in(closed)) {continue;}
                    if(child->is_in(open))
                    {
                        if(current->g+1 > child->g) {continue;}
                        if(current->g+1 < child->g) {
                            for(int j = 0; j < open.size(); j++)
                            {
                                if(child == open[j]) {open.erase(open.begin() + j);}
                            }
                        }
                    }
                    child->parent = current;
                    child->g = current->g + child->distance_from(current);
                    child->f = child->g + child->distance_from(end);
                    open.push_back(child);
                }
            }
        }
    }
    //REQUIRES: none
    //MODIFIES: none
    //EFFECTS: prints the map in a user-friendly way
    void print_map() const
    {
        for(int j = 0; j < width; j++) {std::cout << "==";}
        std::cout << std::endl;
        for(int i = 0; i < height; i++) 
        {
            for(int j = 0; j < width; j++) 
            {
                if(&map[i][j] == start) {std::cout << "S ";} 
                else if(&map[i][j] == end) {std::cout << "E ";} 
                else if(map[i][j].type == 1) {std::cout << "# ";} 
                else if(map[i][j].type == 2) {std::cout << ". ";} 
                else {std::cout << "  ";}
            }
            std::cout << std::endl;
        }
        for(int j = 0; j < width; j++) {std::cout << "==";}
        std::cout << std::endl;
    }
    
private:
    //REQUIRES: none
    //MODIFIES: none
    //EFFECTS: prints the map in a user-friendly way, marking any nodes belonging to "container" with a symbol.
    void print_map_debug(const std::vector<Node *> & container) const
    {
        for(int j = 0; j < width; j++) {std::cout << "==";}
        std::cout << std::endl;
        for(int i = 0; i < height; i++) 
        {
            for(int j = 0; j < width; j++) 
            {
                if(&map[i][j] == start) {std::cout << "S ";}
                else if(&map[i][j] == end) {std::cout << "E ";}
                else if(map[i][j].type == 1) {std::cout << "# ";}
                else if(map[i][j].is_in(container)) {std::cout << "? ";}
                else {std::cout << "  ";}
            }
            std::cout << std::endl;
        }
        for(int j = 0; j < width; j++) {std::cout << "==";}
        std::cout << std::endl;
    }

    Node ** map;
    Node * start;
    Node * end;
    int width, height;
};

#endif