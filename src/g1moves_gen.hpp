#pragma once

#include <array>
#include <map>

#include "move.hpp"

class G1MoveGen {

private:
    std::array<std::array<unsigned short, 19>, 2187> corner_moves;
    std::array<std::array<unsigned short, 19>, 2048> edge_moves;
    std::array<std::array<unsigned short, 19>, 495> ud_moves;

    G1MoveGen();

public:
    static G1MoveGen& get();

    unsigned short move_corners(unsigned short corner, Move move) const;
    unsigned short move_edges(unsigned short edge, Move move) const;
    unsigned short move_ud(unsigned short ud, Move move) const;

    unsigned short corner_distance(unsigned short coord) const;
    unsigned short edge_distance(unsigned short coord) const;
    unsigned short ud_distance(unsigned short coord) const;

    void generate_moves();
    void generate_moves_and_distances();
};
