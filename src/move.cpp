#include <array>
#include <map>
#include <iostream>
#include <string>

#include "move.hpp"

Move::Move(MoveFace f, MoveDirection dir) : face(f), direction(dir) {}

const static std::map<MoveFace, char> face_char_mapping = {
    std::pair<MoveFace, char>(MoveFace::U, 'U'),
    std::pair<MoveFace, char>(MoveFace::R, 'R'),
    std::pair<MoveFace, char>(MoveFace::F, 'F'),
    std::pair<MoveFace, char>(MoveFace::D, 'D'),
    std::pair<MoveFace, char>(MoveFace::L, 'L'),
    std::pair<MoveFace, char>(MoveFace::B, 'B'),
};

const static std::map<MoveDirection, char> dir_char_mapping = {
    std::pair<MoveDirection, char>(MoveDirection::CW, ' '),
    std::pair<MoveDirection, char>(MoveDirection::CCW, '\''),
    std::pair<MoveDirection, char>(MoveDirection::HT, '2'),
};

const Move Move::none = Move(MoveFace::None, MoveDirection::CW);

const std::array<Move, 18> Move::possible_moves = {
    Move(MoveFace::U, MoveDirection::CW), Move(MoveFace::U, MoveDirection::HT), Move(MoveFace::U, MoveDirection::CCW),
    Move(MoveFace::R, MoveDirection::CW), Move(MoveFace::R, MoveDirection::HT), Move(MoveFace::R, MoveDirection::CCW), 
    Move(MoveFace::F, MoveDirection::CW), Move(MoveFace::F, MoveDirection::HT), Move(MoveFace::F, MoveDirection::CCW), 
    Move(MoveFace::D, MoveDirection::CW), Move(MoveFace::D, MoveDirection::HT), Move(MoveFace::D, MoveDirection::CCW), 
    Move(MoveFace::L, MoveDirection::CW), Move(MoveFace::L, MoveDirection::HT), Move(MoveFace::L, MoveDirection::CCW), 
    Move(MoveFace::B, MoveDirection::CW), Move(MoveFace::B, MoveDirection::HT), Move(MoveFace::B, MoveDirection::CCW), 
};

const std::map<MoveFace, std::array<int, 4>> Move::affected_edges = {
    std::pair<MoveFace, std::array<int, 4>>(MoveFace::U, std::array<int, 4>{0, 1, 2, 3}),
    std::pair<MoveFace, std::array<int, 4>>(MoveFace::R, std::array<int, 4>{3, 11, 7, 8}),
    std::pair<MoveFace, std::array<int, 4>>(MoveFace::F, std::array<int, 4>{0, 8, 4, 9}),
    std::pair<MoveFace, std::array<int, 4>>(MoveFace::D, std::array<int, 4>{4, 7, 6, 5}),
    std::pair<MoveFace, std::array<int, 4>>(MoveFace::L, std::array<int, 4>{1, 9, 5, 10}),
    std::pair<MoveFace, std::array<int, 4>>(MoveFace::B, std::array<int, 4>{2, 10, 6, 11}),
};

const std::map<MoveFace, std::array<int, 4>> Move::affected_corners = {
    std::pair<MoveFace, std::array<int, 4>>(MoveFace::U, std::array<int, 4>{0, 1, 2, 3}),
    std::pair<MoveFace, std::array<int, 4>>(MoveFace::R, std::array<int, 4>{0, 3, 7, 4}),
    std::pair<MoveFace, std::array<int, 4>>(MoveFace::F, std::array<int, 4>{1, 0, 4, 5}),
    std::pair<MoveFace, std::array<int, 4>>(MoveFace::D, std::array<int, 4>{4, 7, 6, 5}),
    std::pair<MoveFace, std::array<int, 4>>(MoveFace::L, std::array<int, 4>{2, 1, 5, 6}),
    std::pair<MoveFace, std::array<int, 4>>(MoveFace::B, std::array<int, 4>{3, 2, 6, 7}),
};

Maneuver::Maneuver() : moves() {}

static Move parse_move(std::string str) {
    MoveFace face = MoveFace::None;
    for (const auto& mapping : face_char_mapping) {
        if (mapping.second == str[0]) {
            face = mapping.first;
            break;
        }
    }
    
    if (str.size() == 1) {
        return Move(face, MoveDirection::CW);
    }
    if (str[1] == '2') {
        return Move(face, MoveDirection::HT);
    }
    if (str[1] == '\'') {
        return Move(face, MoveDirection::CCW);
    }

    std::cout << "Failed to parse move " << str << '\n';
    return Move::none;
}

Maneuver::Maneuver(std::string str) : moves() {
    std::vector <std::string> move_list;
    std::string move = "";
    for (size_t i = 0; i < str.size(); i++) {
        if (isalpha(str[i]) && move.size() > 0) {
            moves.push_back(parse_move(move));
            move = "";
        }
        if (str[i] != ' ') {
            move += str[i];
        }
    }
    if (!move.empty()) {
        moves.push_back(parse_move(move));
        move = "";
    }
}

Move Maneuver::last_move() const {
    if (moves.size() > 0) {
        return moves.back();
    }
    else {
        return Move::none;
    }
}

void Maneuver::append(Move move) {
    moves.push_back(move);
}

void Maneuver::print() const {
    for (const auto& move : moves) {
        std::cout << face_char_mapping.at(move.face) << dir_char_mapping.at(move.direction) << ' ';
    }
}

bool operator==(const Move& lhs, const Move& rhs) {
    if (lhs.face == MoveFace::None && rhs.face == MoveFace::None) {
        return true;
    }
    else {
        return (lhs.face == rhs.face) && (lhs.direction == rhs.direction);
    }
}

bool operator!=(const Move& lhs, const Move& rhs) {
    return !(lhs == rhs);
}