#include "g1coord.hpp"
#include "move.hpp"
#include "utility.hpp"
#include "g1moves_gen.hpp"

#include <iostream>

G1::G1() : corners(0), edges(0), ud(0) {};
G1::G1(unsigned short c, unsigned short e, unsigned short s) : corners(c), edges(e), ud(s) {};

unsigned short G1::corners_coord(unsigned short corners) {
    unsigned short coord = 0;
    int multiplier = 1;
    for (int c = 1; c < N_CORNERS; ++c) {
        char c_or = (corners >> (2 * c)) & 0b11;
        coord += c_or * multiplier;
        multiplier *= 3;
    }
    return coord;
}

unsigned short G1::edges_coord(unsigned short edges) {
    return edges >> 1;
}

unsigned short G1::ud_coord(unsigned short ud) {
    unsigned short coord = 0;
    int k = 3;
    for (int e = 0; e < N_EDGES; ++e) {
        bool e_occ = (ud >> e) & 1U;
        if (e_occ) {
            if (k == 0){
                break;
            }
            --k;
        }
        else {
            coord += binomial(N_EDGES - 1 - e, k);
        }
    }
    return coord;
}

unsigned short G1::corners_from_coord(unsigned short coord) {
    unsigned short corners = 0;
    int rot_sum = 0;
    for (int c = 1; c < N_CORNERS; ++c) {
        int c_or = coord % 3;
        rot_sum += c_or;
        coord = (coord - c_or) / 3;
        corners |= c_or << (2 * c);
    }
    int first_rot = (3 - (rot_sum % 3)) % 3;
    corners |= first_rot;
    return corners;
}

unsigned short G1::edges_from_coord(unsigned short coord) {
    unsigned short sum = 0;
    for (int i = 0; i < N_EDGES; ++i) {
        sum ^= (coord >> i) & 1U;
    }
    return (coord << 1) | sum;
}

unsigned short G1::ud_from_coord(unsigned short coord) {
    unsigned short ud = 0;
    int n = N_EDGES - 1;
    int k = 3;
    while (k >= 0) {
        int current_value = binomial(n, k);
        if (current_value <= coord) {
            coord -= current_value;
            --n;
        }
        else {
            --k;
            ud |= 1U << (N_EDGES - 1 - n);
            --n;
        }
    }
    return ud;
}

unsigned short G1::corners_coord() const {
    return corners;
}

unsigned short G1::edges_coord() const {
    return edges;
}

unsigned short G1::ud_coord() const {
    return ud;
}

G1 G1::move(const Move move) const {
    unsigned short new_edges = G1MoveGen::get().move_edges(edges, move);
    unsigned short new_ud = G1MoveGen::get().move_ud(ud, move);
    unsigned short new_corners = G1MoveGen::get().move_corners(corners, move);
    return G1(new_corners, new_edges, new_ud);
}

void G1::moved(const Move move) {
    G1 new_g1 = this->move(move);
    this->edges = new_g1.edges;
    this->corners = new_g1.corners;
    this->ud = new_g1.ud;
}

void G1::moved(const Maneuver& maneuver) {
    for (const auto& move : maneuver.moves) {
        moved(move);
    }
}

bool G1::is_g1() const {
    return (corners == 0 && edges == 0 && ud == 0);
}

void G1::print() const {
    std::cout << "G1 coords:\n";
    std::cout << "ud: " << ud_coord() << '\n';
    std::cout << "corners: " << corners_coord() << '\n';
    std::cout << "edges: " << edges_coord() << '\n';
}

unsigned short G1::solving_distance() const {
    unsigned short max = G1MoveGen::get().ud_distance(ud);
    max = std::max(max, G1MoveGen::get().corner_distance(corners));
    max = std::max(max, G1MoveGen::get().edge_distance(edges));
    return max;
}