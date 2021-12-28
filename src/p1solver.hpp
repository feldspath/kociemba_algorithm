#pragma once

#include <vector>

#include "move.hpp"
#include "p1coord.hpp"

struct G1Move {
    Maneuver current_moves;
    P1Coord g1_coords;

    G1Move(Maneuver maneuver, P1Coord coords);
    
    G1Move move(Move move) const;
};

void g1_solver(P1Coord initial_position);
void g1_ida(P1Coord initial_position);