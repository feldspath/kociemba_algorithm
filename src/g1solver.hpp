#pragma once

#include <vector>
#include "move.hpp"
#include "g1coord.hpp"
#include "phase2coord.hpp"
#include "position.hpp"

struct G1Solve {
    Maneuver solving_moves;
    Phase2Coord phase2_coord;
};

struct G1Move {
    Maneuver current_moves;
    G1 g1_coords;

    G1Move(Maneuver maneuver, G1 coords);

    G1Move move(Move move) const;
};

void g1_solver(G1 initial_position, std::vector<G1Solve>& g1_solutions);