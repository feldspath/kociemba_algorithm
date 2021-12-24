#include <vector>
#include <queue>
#include <iostream>

#include "g1solver.hpp"
#include "position.hpp"
#include "move.hpp"

G1Move::G1Move(Maneuver maneuver, G1 coords) : current_moves(maneuver), g1_coords(coords) {}

static bool is_move_invalid(Move previous_move, Move current_move) {
    if (previous_move == Move::none) {
        return false;
    }
    bool same_face = previous_move.face == current_move.face;
    bool opposite_face = static_cast<int>(previous_move.face) > 0 && static_cast<int>(previous_move.face) == -static_cast<int>(current_move.face);
    return  same_face || opposite_face;
}

void g1_solver(G1 initial_position, std::vector<G1Solve>& g1_solutions) {
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
                //G1Solve next_solve(next_g1_move, initial_position);
                // bool existing_position = false;
                // for (const auto& solves : g1_solutions) {
                //     if (solves.phase2_coord == next_solve.phase2_coord) {
                //         existing_position = true;
                //         break;
                //     }
                // }
                // if (!existing_position) {
                //     g1_solutions.push_back(next_solve);
                // }
                next_g1_move.current_moves.print();
                std::cout << '\n';
                //getchar();
                //return;
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