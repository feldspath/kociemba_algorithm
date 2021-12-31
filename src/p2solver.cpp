#include <stack>
#include <iostream>

#include "p2solver.hpp"
#include "position.hpp"
#include "move.hpp"

P2Solve::P2Solve(Maneuver maneuver, P2Coord coords) : current_moves(maneuver), p2_coords(coords) {}

static bool is_move_invalid(Move previous_move, Move current_move) {
    if (current_move.rotates_any()) return true;
    if (previous_move == Move::none) return false;
    bool same_face = previous_move.face == current_move.face;
    bool opposite_face = static_cast<int>(previous_move.face) > 0 && static_cast<int>(previous_move.face) == -static_cast<int>(current_move.face);
    return same_face || opposite_face;
}

void p2_ida(P2Coord initial_position) {
    std::stack<P2Solve> solving;
    solving.push(P2Solve(Maneuver(), initial_position));

    size_t max_length = initial_position.solving_distance();
    printf("Init length: %ld\n", max_length);

    while (max_length <= 18) {
        const P2Solve current_solve = solving.top();
        solving.pop();

        for (const auto& move : Move::possible_moves) {
            const auto last_move = current_solve.current_moves.last_move();
            if (is_move_invalid(last_move, move)) {
                continue;
            }
            P2Solve next_state = current_solve.move(move);
            if (next_state.current_moves.moves.size() + next_state.p2_coords.solving_distance() > max_length) continue;
            solving.push(next_state);
            if (next_state.p2_coords.is_solved()) {
                next_state.current_moves.print();
                std::cout << '\n';
                return;
            }
        }

        if (solving.size() == 0) {
            ++max_length;
            printf("Exploring new length: %ld\n", max_length);
            solving.push(P2Solve(Maneuver(), initial_position));
        }
    }
}

P2Solve P2Solve::move(Move move) const {
    auto new_maneuver = Maneuver(current_moves);
    new_maneuver.append(move);
    auto new_coords = p2_coords.move(move);
    return P2Solve(new_maneuver, new_coords);
}