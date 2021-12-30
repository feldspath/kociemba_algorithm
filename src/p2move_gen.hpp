#pragma once

#include <array>
#include <map>
#include <functional>

#include "move.hpp"

#define N_MOVES_P2 10

class P2MoveGen {

private:
    std::array<unsigned short, (N_MOVES_P2+1) * 40320> corner_moves;
    std::array<unsigned short, (N_MOVES_P2+1) * 40320> edge_moves;
    std::array<unsigned short, (N_MOVES_P2+1) * 24> ud_moves;

    template <size_t N>
    inline unsigned short piece_coord_after_move(const std::array<unsigned short, N>& pieces_moves, unsigned short coord, Move move) const ;
    template <size_t N>
    inline unsigned short estimated_distance(const std::array<unsigned short, N>& pieces_moves, unsigned short coord) const;

    template <size_t N>
    inline void update_piece_coord_after_move(std::array<unsigned short, N>& pieces_moves, unsigned short coord, Move move, unsigned int new_coord);
    template <size_t N>
    inline void update_estimated_distance(std::array<unsigned short, N>& pieces_moves, unsigned short coord, unsigned int new_distance);

    template <size_t N>
    void explore_values(std::array<unsigned short, N>& piece_moves, std::function<unsigned short(unsigned short, Move)> move_function);


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

    void export_to(char* file) const;
    void import_from(char* file);
};

template <size_t N>
inline unsigned short P2MoveGen::piece_coord_after_move(const std::array<unsigned short, N>& pieces_moves, unsigned short coord, Move move) const {
    static_assert(N%(N_MOVES_P2+1) == 0);
    return pieces_moves[coord*(N_MOVES_P2+1) + move.g1_index()];
}

template <size_t N>
inline unsigned short P2MoveGen::estimated_distance(const std::array<unsigned short, N>& pieces_moves, unsigned short coord) const {
    static_assert(N%(N_MOVES_P2+1) == 0);
    return pieces_moves[coord*(N_MOVES_P2+1) + N_MOVES_P2];
}

template <size_t N>
inline void P2MoveGen::update_piece_coord_after_move(std::array<unsigned short, N>& pieces_moves, unsigned short coord, Move move, unsigned int new_coord) {
    static_assert(N%(N_MOVES_P2+1) == 0);
    pieces_moves[coord*(N_MOVES_P2+1) + move.g1_index()] = new_coord;
}


template <size_t N>
inline void P2MoveGen::update_estimated_distance(std::array<unsigned short, N>& pieces_moves, unsigned short coord, unsigned int new_distance) {
    static_assert(N%(N_MOVES_P2+1) == 0);
    pieces_moves[coord*(N_MOVES_P2+1) + N_MOVES_P2] = new_distance;
}