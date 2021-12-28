#include <iostream>

#include "p2coord.hpp"
#include "utility.hpp"
#include "p2move_gen.hpp"

P2Coord::P2Coord() : 
    corners(0), edges(0), ud_slice(0) {}

P2Coord::P2Coord(unsigned short _corners, unsigned short _edges, unsigned short _ud_slice) :
    corners(_corners), edges(_edges), ud_slice(_ud_slice) {}

unsigned short P2Coord::corners_coord(P2Corners corners) {
    return static_cast<unsigned short>(factorial_coord(corners));
}

unsigned short P2Coord::edges_coord(P2Edges edges) {
    return static_cast<unsigned short>(factorial_coord(edges));
}

unsigned short P2Coord::ud_coord(P2Slice ud) {
    return static_cast<unsigned short>(factorial_coord(ud));
}

P2Corners P2Coord::corners_from_coord(unsigned short coord) {
    return std::move(inverse_factorial_coord<N_CORNERS>(coord));
}

P2Edges P2Coord::edges_from_coord(unsigned short coord) {
    return std::move(inverse_factorial_coord<N_EDGES-N_SLICE>(coord));
}

P2Slice P2Coord::ud_from_coord(unsigned short coord) {
    return std::move(inverse_factorial_coord<N_SLICE>(coord));
}

unsigned short P2Coord::corners_coord() const {
    return corners;
}

unsigned short P2Coord::edges_coord() const {
    return edges;
}

unsigned short P2Coord::ud_coord() const {
    return ud_slice;
}

unsigned short P2Coord::solving_distance() const {
    unsigned short max = P2MoveGen::get().ud_distance(ud_slice);
    max = std::max(max, P2MoveGen::get().corner_distance(corners));
    max = std::max(max, P2MoveGen::get().edge_distance(edges));
    return max;
}

P2Coord P2Coord::move(const Move move) const {
    unsigned short new_edges = P2MoveGen::get().move_edges(edges, move);
    unsigned short new_ud = P2MoveGen::get().move_ud(ud_slice, move);
    unsigned short new_corners = P2MoveGen::get().move_corners(corners, move);
    return P2Coord(new_corners, new_edges, new_ud);
}

void P2Coord::moved(const Move move) {
    P2Coord new_coord = this->move(move);
    this->edges = new_coord.edges;
    this->corners = new_coord.corners;
    this->ud_slice = new_coord.ud_slice;
}

void P2Coord::moved(const Maneuver& maneuver) {
    for (const auto& move : maneuver.moves) {
        moved(move);
    }
}

bool P2Coord::is_solved() const {
    return corners == 0 && edges == 0 && ud_slice == 0;
}

void P2Coord::print() const {
    std::cout << "P2 coords:\n";
    std::cout << "ud: " << ud_coord() << '\n';
    std::cout << "corners: " << corners_coord() << '\n';
    std::cout << "edges: " << edges_coord() << '\n';
}