#pragma once

#include <array>
#include <map>

class G1MoveGen {

private:
    std::array<std::array<unsigned short, 18>, 2187> corner_moves;
    std::array<std::array<unsigned short, 18>, 2048> edges_moves;
    std::array<std::array<unsigned short, 18>, 495> ud_moves;

    G1MoveGen();

public:
    static G1MoveGen& get();

    unsigned short move_corners(unsigned short corner, Move move);
    unsigned short move_edges(unsigned short edge, Move move);
    unsigned short move_ud(unsigned short ud, Move move);

    void generate_moves();
};
