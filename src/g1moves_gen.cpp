#include "move.hpp"
#include "g1coord.hpp"
#include "utility.hpp"
#include "g1moves_gen.hpp"

#include <array>
#include <queue>

static unsigned short update_edges_rot(const unsigned short previous, const std::array<int, 4>& affected_edges, bool ignore_rot=false) {
    unsigned short new_edges = previous;
    bool prev_e_or = (previous >> affected_edges.back()) & 1U;
    for (const auto& e : affected_edges) {
        prev_e_or = ignore_rot ? prev_e_or : !prev_e_or;
        new_edges ^= (-prev_e_or ^ new_edges) & (1U << e);
        prev_e_or = (previous >> e) & 1U;
    }
    return new_edges;
}

static unsigned short update_ud_slice(const unsigned short previous, const std::array<int, 4>& affected_edges) {
    unsigned short new_ud = previous;
    bool prev_ud = (previous >> (N_EDGES - 1 - affected_edges.back())) & 1U;
    for (const auto& e : affected_edges) {
        new_ud ^= (-prev_ud ^ new_ud) & (1U << (N_EDGES - 1 - e));
        prev_ud = (previous >> (N_EDGES - 1 - e)) & 1U;
    }
    return new_ud;
}

static unsigned short update_corners_rot(const unsigned short previous, const std::array<int, 4>& affected_corners, bool ignore_rot = false) {
    unsigned short new_corners = previous;
    int prev_c_or = (previous >> (2 * affected_corners.back())) & 0b11U;
    int val = ignore_rot ? 0 : 1;
    for (const auto& c : affected_corners) {
        int c_or = (prev_c_or + 3 + val) % 3;
        val *= -1;
        new_corners &= ~(0b11 << (2 * c));
        new_corners |= c_or << (2 * c);

        prev_c_or = (previous >> (2 * c)) & 0b11;
    }
    return new_corners;
}

void G1MoveGen::generate_moves() {
    // Corners
    for (int i = 0; i < static_cast<int>(corner_moves.size()); ++i) {
        unsigned short corners = G1::corners_from_coord(i);
        for (int m = 0; m < static_cast<int>(Move::possible_moves.size()); ++m) {
            const auto& move = Move::possible_moves[m];
            bool ignore_rot = move.face == MoveFace::U || move.face == MoveFace::D;
            const auto& affected_corners = Move::affected_corners.at(move.face);
            unsigned short new_corners = corners;
            for (int i = 0; i < static_cast<int>(move.direction); ++i) {
                new_corners = update_corners_rot(new_corners, affected_corners, ignore_rot);
            }
            corner_moves[i][m] = G1::corners_coord(new_corners);
        }
    }

    // Edges
    for (int i = 0; i < static_cast<int>(edges_moves.size()); ++i) {
        unsigned short edges = G1::edges_from_coord(i);
        for (int m = 0; m < static_cast<int>(Move::possible_moves.size()); ++m) {
            const auto& move = Move::possible_moves[m];
            bool ignore_rot = move.face == MoveFace::U || move.face == MoveFace::D || move.face == MoveFace::R || move.face == MoveFace::L;
            const auto& affected_edges = Move::affected_edges.at(move.face);
            unsigned short new_edges = edges;
            for (int i = 0; i < static_cast<int>(move.direction); ++i) {
                new_edges = update_edges_rot(new_edges, affected_edges, ignore_rot);
            }
            edges_moves[i][m] = G1::edges_coord(new_edges);
        }
    }

    // UD slice
    for (int i = 0; i < static_cast<int>(ud_moves.size()); ++i) {
        unsigned short ud = G1::ud_from_coord(i);
        for (int m = 0; m < static_cast<int>(Move::possible_moves.size()); ++m) {
            const auto& move = Move::possible_moves[m];
            if (move.face == MoveFace::U || move.face == MoveFace::D) {
                ud_moves[i][m] = i;
                continue;
            }
            const auto& affected_edges = Move::affected_edges.at(move.face);
            unsigned short new_ud = ud;
            for (int i = 0; i < static_cast<int>(move.direction); ++i) {
                new_ud = update_ud_slice(new_ud, affected_edges);
            }
            ud_moves[i][m] = G1::ud_coord(new_ud);
        }
    }
}

G1MoveGen::G1MoveGen() {
    generate_moves();
}

G1MoveGen& G1MoveGen::get() {
    static G1MoveGen move_gen;
    return move_gen;
}

unsigned short G1MoveGen::move_corners(unsigned short corner, Move move) {
    int move_index = Move::map_move(move);
    return corner_moves[corner][move_index];
}

unsigned short G1MoveGen::move_edges(unsigned short edge, Move move) {
    int move_index = Move::map_move(move);
    return edges_moves[edge][move_index];
}

unsigned short G1MoveGen::move_ud(unsigned short ud, Move move) {
    int move_index = Move::map_move(move);
    return ud_moves[ud][move_index];
}