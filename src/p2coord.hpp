#pragma once

#include <vector>

#include "move.hpp"
#include "utility.hpp"

using P2Corners = std::array<int, N_CORNERS>;
using P2Edges = std::array<int, N_EDGES-N_SLICE>;
using P2Slice = std::array<int, N_SLICE>;

class P2Coord {

private:
    unsigned short corners;
    unsigned short edges;
    unsigned short ud_slice;

public:
    P2Coord();
    P2Coord(unsigned short corners, unsigned short edges, unsigned short ud);

    static unsigned short corners_coord(P2Corners corners);
    static unsigned short edges_coord(P2Edges edges);
    static unsigned short ud_coord(P2Slice ud);

    static P2Corners corners_from_coord(unsigned short coord);
    static P2Edges edges_from_coord(unsigned short coord);
    static P2Slice ud_from_coord(unsigned short coord);

    unsigned short corners_coord() const;
    unsigned short edges_coord() const;
    unsigned short ud_coord() const;
    unsigned short solving_distance() const;

    P2Coord move(const Move move) const;
    void moved(const Move move);
    void moved(const Maneuver& maneuver);

    bool is_solved() const;

    void print() const;
};