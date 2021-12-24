#pragma once

#include <vector>
#include "move.hpp"
#include "g1coord.hpp"

/*
 * EDGE INDEXING
 *
 * TOP
 * % 2 %
 * 1 % 3
 * % 0 %
 * 
 * BOTTOM
 * % 6 %
 * 5 % 7
 * % 4 %
 * 
 * UD SLICE
 * 10 % 11
 *  % % %
 *  9 % 8
 * 
 */

class Position {
private:
    unsigned long edge_position;
    unsigned int corner_position;
    unsigned short edge_orientation;
    unsigned short corner_orientation;
    
public:
    Position(unsigned long edge_pos, unsigned int corner_pos, unsigned short edge_or, unsigned short corner_or);

    G1 g1_coord() const;
};