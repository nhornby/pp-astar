#ifndef NODE_H
#define NODE_H

#include <vector>
#include <cmath>

/* Node.h
 * 
 * Each Node is represented by a Row/Col pair, and contains POD
 * as well as a pointer to a parent node, which represents the previous node
 * in the current shortest possible path from start to this node.
 *
 * Author: Nolan Hornby
 * Date: Tuesday, August 11th 2020
 * University of Michigan
 * Class of 2023
 */ 

class Node {
public:
    Node ()
    {
        row = 0;
        col = 0;
        type = 0;
        f = 0;
        g = 0;
        parent = nullptr;
    }
    //REQUIRES: other is a valid node
    //MODIFIES: none
    //EFFECTS: returns distance between this and other.
    float distance_from(const Node * other) const
    {
        return sqrt(pow(other->row - row, 2) + pow(other->col - col, 2));
    }
    //REQUIRES: other is a valid node
    //MODIFIES: none
    //EFFECTS: returns true if this and other are at the same location
    bool operator==(const Node * other) const
    {
        return (row == other->row && col == other->col);
    }
    //REQUIRES: container is a valid vector of Node pointers
    //MODIFIES: none
    //EFFECTS: returns true if a node of this's location is in container
    bool is_in(const std::vector<Node *> container) const
    {
        for(int i = 0; i < container.size(); i++)
        {
            if(this == container[i]) {return true;}
        }
        return false;
    }
    
    int row, col;
    int type;
    float f, g;
    Node * parent = nullptr;
};

#endif