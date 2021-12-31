#include <queue>
#include <stack>
#include <iostream>

#include "p1solver.hpp"
#include "position.hpp"
#include "move.hpp"

G1Move::G1Move(Maneuver maneuver, P1Coord coords) : current_moves(maneuver), g1_coords(coords) {}

static bool is_move_invalid(Move previous_move, Move current_move) {
    if (previous_move == Move::none) {
        return false;
    }
    bool same_face = previous_move.face == current_move.face;
    bool opposite_face = static_cast<int>(previous_move.face) > 0 && static_cast<int>(previous_move.face) == -static_cast<int>(current_move.face);
    return same_face || opposite_face;
}

void g1_ida(P1Coord initial_position) {
    std::stack<G1Move> solving;
    solving.push(G1Move(Maneuver(), initial_position));

    size_t max_length = initial_position.solving_distance();
    printf("Init length: %ld\n", max_length);

    while (max_length <= 20) {
        const G1Move current_solve = solving.top();
        solving.pop();

        for (const auto& move : Move::possible_moves) {
            const auto last_move = current_solve.current_moves.last_move();
            if (is_move_invalid(last_move, move)) {
                continue;
            }
            G1Move next_g1_move = current_solve.move(move);
            if (next_g1_move.current_moves.moves.size() + next_g1_move.g1_coords.solving_distance() > max_length) continue;
            solving.push(next_g1_move);
            if (next_g1_move.g1_coords.is_g1()) {
                next_g1_move.current_moves.print();
                std::cout << '\n';
            }
        }

        if (solving.size() == 0) {
            ++max_length;
            printf("Exploring new length: %ld\n", max_length);
            solving.push(G1Move(Maneuver(), initial_position));
        }
    }
}

void g1_solver(P1Coord initial_position) {
    std::queue<G1Move> solving_queue;
    solving_queue.push(G1Move(Maneuver(), initial_position));

    while (true) {
        const G1Move current_solve = solving_queue.front();
        solving_queue.pop();

        for (const auto& move : Move::possible_moves) {
            const auto last_move = current_solve.current_moves.last_move();
            if (is_move_invalid(last_move, move)) {
                continue;
            }
            G1Move next_g1_move = current_solve.move(move);
            solving_queue.push(next_g1_move);
            if (next_g1_move.g1_coords.is_g1()) {
                next_g1_move.current_moves.print();
                std::cout << '\n';
            }
        }
    }
}

G1Move G1Move::move(Move move) const {
    auto new_maneuver = Maneuver(current_moves);
    new_maneuver.append(move);
    auto new_coords = g1_coords.move(move);
    return G1Move(new_maneuver, new_coords);
}