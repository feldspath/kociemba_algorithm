#pragma once

#include <vector>
#include <string>
#include <array>
#include <map>

enum class MoveFace {
    U = 1,
    R = 2,
    F = 3,
    D = -1,
    L = -2,
    B = -3,
    None = 0
};

enum class MoveDirection {
    CW = 1,
    CCW = 3,
    HT = 2,
};

struct Move {
    const MoveFace face;
    const MoveDirection direction;

    Move(MoveFace f, MoveDirection dir);
    const static Move none;
    const static std::array<Move, 18> possible_moves;
    const static std::map<MoveFace, std::array<int, 4>> affected_edges;
    const static std::map<MoveFace, std::array<int, 4>> affected_corners;

    static int map_move(Move move);
};

class Maneuver {
public:
    std::vector<Move> moves;

public:
    Maneuver();
    Maneuver(std::string moves);

    Move last_move() const;
    void append(Move move);
    void print() const;
};

bool operator==(const Move& lhs, const Move& rhs);
bool operator!=(const Move& lhs, const Move& rhs);