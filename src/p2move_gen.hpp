#pragma once

#include <array>
#include <map>

#include "move.hpp"

#define N_MOVES_P2 10

class P2MoveGen {

private:
    std::array<std::array<unsigned short, N_MOVES_P2+1>, 40320> corner_moves;
    std::array<std::array<unsigned short, N_MOVES_P2+1>, 40320> edge_moves;
    std::array<std::array<unsigned short, N_MOVES_P2+1>, 24> ud_moves;

    P2MoveGen();

public:
    static P2MoveGen& get();

    unsigned short move_corners(unsigned short corner, Move move) const;
    unsigned short move_edges(unsigned short edge, Move move) const;
    unsigned short move_ud(unsigned short ud, Move move) const;

    unsigned short corner_distance(unsigned short coord) const;
    unsigned short edge_distance(unsigned short coord) const;
    unsigned short ud_distance(unsigned short coord) const;

    void generate_moves();
    void generate_moves_and_distances();
};
