#pragma once

#include <vector>

#include "move.hpp"
#include "g1coord.hpp"

struct G1Move {
    Maneuver current_moves;
    G1 g1_coords;

    G1Move(Maneuver maneuver, G1 coords);
    
    G1Move move(Move move) const;
};

void g1_solver(G1 initial_position);
void g1_ida(G1 initial_position);