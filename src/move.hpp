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

    inline int index() const;
    inline int g1_index() const;
    inline bool rotates_edges() const;
    inline bool rotates_corners() const;
    inline bool rotates_any() const;

    const static Move none;
    const static std::array<Move, 18> possible_moves;
    const static std::map<MoveFace, std::array<int, 4>> affected_edges;
    const static std::map<MoveFace, std::array<int, 4>> affected_corners;
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

inline int Move::index() const {
    int face_id = static_cast<int>(face);
    int dir = static_cast<int>(direction);
    face_id = face_id > 0 ? face_id - 1 : -face_id + 2;
    return face_id * 3 + dir - 1;
}

inline int Move::g1_index() const {
    int id = static_cast<int>(face);
    if (face == MoveFace::U) return index();
    if (face == MoveFace::D) return index()-6;
    if (id > 0) return id+4;
    else return -id+6;
    return -1;
}

inline bool Move::rotates_corners() const {
    if (direction == MoveDirection::HT) return false;
    return !(face == MoveFace::U || face == MoveFace::D);
}

inline bool Move::rotates_edges() const {
    if (direction == MoveDirection::HT) return false;
    return face == MoveFace::F || face == MoveFace::B;
}

inline bool Move::rotates_any() const {
    return rotates_corners();
}