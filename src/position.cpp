#include "position.hpp"
#include "utility.hpp"

Position::Position(unsigned long edge_pos, unsigned int corner_pos, unsigned short edge_or, unsigned short corner_or) : edge_position(edge_pos), corner_position(corner_pos), edge_orientation(edge_or), corner_orientation(corner_or) {}

P1Coord Position::p1_coord() const {
    unsigned short ud = 0;
    for (int e = 0; e < N_EDGES; ++e) {
        int edge_cubie = (edge_position >> (4 * e)) & 0b1111;
        if (edge_cubie >= 8) {
            ud |= 1 << (N_EDGES - 1 - e);
        }
    }
    return P1Coord(corner_orientation, edge_orientation, ud);
}