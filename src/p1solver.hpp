#pragma once

#pragma once

#include "move.hpp"
#include "p1coord.hpp"

struct G1Move {
    Maneuver current_moves;
    P1Coord g1_coords;

    G1Move(Maneuver maneuver, P1Coord coords);
    
    G1Move move(Move move) const;
};

inline bool operator<(const G1Move& lhs, const G1Move& rhs) {
    return lhs.current_moves.moves.size() + lhs.g1_coords.solving_distance() > rhs.current_moves.moves.size() + rhs.g1_coords.solving_distance();
}

void g1_solver(P1Coord initial_position);
void g1_ida(P1Coord initial_position);