#pragma once

#include "move.hpp"
#include "p2coord.hpp"

struct P2Solve {
    Maneuver current_moves;
    P2Coord p2_coords;

    P2Solve(Maneuver maneuver, P2Coord coords);
    
    P2Solve move(Move move) const;
};

void p2_ida(P2Coord initial_position);