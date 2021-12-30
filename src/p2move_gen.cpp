#include <array>
#include <queue>
#include <iostream>
#include <functional>
#include <string>

#include "move.hpp"
#include "utility.hpp"
#include "p2move_gen.hpp"
#include "p2coord.hpp"
#include "exporter.hpp"

template<size_t N>
static void update_pos(std::array<int, N>& pieces, const std::array<int, 4>& affected_pieces) {
    auto previous = pieces[affected_pieces.back()];
    for (const auto& c : affected_pieces) {
        const auto temp = pieces[c];
        pieces[c] = previous;
        previous = temp;
    }
}

static unsigned short update_corners(unsigned short coord, Move move) {
    const auto& affected_corners = Move::affected_corners.at(move.face);
    auto new_corners = P2Coord::corners_from_coord(coord);
    for (int i = 0; i < static_cast<int>(move.direction); ++i) {
        update_pos(new_corners, affected_corners);
    }
    return P2Coord::corners_coord(new_corners);
}

template <typename T>
static void switch_values(T& arr, int i1, int i2) {
    const auto temp = arr[i1];
    arr[i1] = arr[i2]; 
    arr[i2] = temp; 
}

static unsigned short update_edges(unsigned short coord, Move move) {
    const auto& affected_edges = Move::affected_edges.at(move.face);
    auto new_edges = P2Coord::edges_from_coord(coord);
    if (move.face == MoveFace::U || move.face == MoveFace::D) {
        for (int i = 0; i < static_cast<int>(move.direction); ++i) {
            update_pos(new_edges, affected_edges);
        }
    }
    else {
        const auto i1 = affected_edges[0];
        const auto i2 = affected_edges[2];
        switch_values(new_edges, i1, i2);
    }
    
    return P2Coord::edges_coord(new_edges);
}

static unsigned short update_ud(unsigned short coord, Move move) {
    if (move.face == MoveFace::U || move.face == MoveFace::D) return coord;
    const auto& affected_edges = Move::affected_edges.at(move.face);
    auto new_ud = P2Coord::ud_from_coord(coord);
    const auto i1 = affected_edges[1]-8;
    const auto i2 = affected_edges[3]-8;
    switch_values(new_ud, i1, i2);
    return P2Coord::ud_coord(new_ud);
}

template <size_t N>
void P2MoveGen::explore_values(std::array<unsigned short, N>& piece_moves, std::function<unsigned short(unsigned short, Move)> move_function) {
    static_assert(N%(N_MOVES_P2+1)==0);
    std::queue<unsigned short> exploring;
    exploring.push(0);
    update_estimated_distance(piece_moves, 0, 0);
    size_t count = 0;
    size_t max_count = N/(N_MOVES_P2+1);
    while (count < max_count) {
        const unsigned short values = exploring.front();
        exploring.pop();
        ++count;
        for (const auto& move : Move::possible_moves) {
            if (move.rotates_any()) continue;
            unsigned short new_values = move_function(values, move);
            update_piece_coord_after_move(piece_moves, values, move, new_values);
            if (estimated_distance(piece_moves, new_values) != (unsigned short)-1) continue;
            exploring.push(new_values);
            update_estimated_distance(piece_moves, new_values, estimated_distance(piece_moves, values)+1);
        }
    }
}

void P2MoveGen::generate_moves_and_distances() {
    explore_values(corner_moves, &update_corners);
    explore_values(edge_moves, &update_edges);
    explore_values(ud_moves, &update_ud);
}

P2MoveGen::P2MoveGen() {
    corner_moves.fill(-1);
    edge_moves.fill(-1);
    ud_moves.fill(-1);
    import_from("moves/p2");
    //generate_moves_and_distances();
}

P2MoveGen& P2MoveGen::get() {
    static P2MoveGen move_gen;
    return move_gen;
}

unsigned short P2MoveGen::move_corners(unsigned short corner, Move move) const {
    return piece_coord_after_move(corner_moves, corner, move);
}

unsigned short P2MoveGen::move_edges(unsigned short edge, Move move) const {
    return piece_coord_after_move(edge_moves, edge, move);
}

unsigned short P2MoveGen::move_ud(unsigned short ud, Move move) const {
    return piece_coord_after_move(ud_moves, ud, move);
}

unsigned short P2MoveGen::corner_distance(unsigned short coord) const {
    return estimated_distance(corner_moves, coord);
}

unsigned short P2MoveGen::edge_distance(unsigned short coord) const {
    return estimated_distance(edge_moves, coord);
}

unsigned short P2MoveGen::ud_distance(unsigned short coord) const {
    return estimated_distance(ud_moves, coord);
}

void P2MoveGen::export_to(char* file) const {
    std::string path(file);
    Exporter::export_array(corner_moves, path + ".crn");
    Exporter::export_array(edge_moves, path + ".edg");
    Exporter::export_array(ud_moves, path + ".ud");
}

void P2MoveGen::import_from(char* file) {
    std::string path(file);
    Exporter::import_array(corner_moves, path + ".crn");
    Exporter::import_array(edge_moves, path + ".edg");
    Exporter::import_array(ud_moves, path + ".ud");
}