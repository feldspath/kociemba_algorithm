#pragma once

#include "move.hpp"

class G1 {

private:
    unsigned short corners;
    unsigned short edges;
    unsigned short ud;

public:
    G1();
    G1(unsigned short corners, unsigned short edges, unsigned short ud);

    static unsigned short corners_coord(unsigned short corners);
    static unsigned short edges_coord(unsigned short edges);
    static unsigned short ud_coord(unsigned short ud);

    static unsigned short corners_from_coord(unsigned short coord);
    static unsigned short edges_from_coord(unsigned short coord);
    static unsigned short ud_from_coord(unsigned short coord);

    unsigned short corners_coord() const;
    unsigned short edges_coord() const;
    unsigned short ud_coord() const;
    unsigned short solving_distance() const;

    G1 move(const Move move) const;
    void moved(const Move move);
    void moved(const Maneuver& maneuver);

    bool is_g1() const;

    void print() const;
};