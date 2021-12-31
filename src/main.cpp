#include <iostream>

#include "p1coord.hpp"
#include "p1solver.hpp"
#include "move.hpp"
#include "p2coord.hpp"
#include "p2solver.hpp"

int main() {
    // Maneuver test_man(std::string("R B2 U' L2 U2 B2 F2 R2 U L2 B2 L F2 R' D B L D2 U2 F2"));
    Maneuver test_man(std::string("R2 F2 U D2 L2 B2 D' F2 L2 U B2 R2 D B2"));
    //Maneuver test_man(std::string("R2 U"));
    

    // P1Coord test(0, 0, 0);

    P2Coord test(0, 0, 0);
    test.moved(test_man);
    test.print();

    p2_ida(test);


    // printf("corners coord: %x\n", test.corners_coord());
    // auto c = P2Coord::corners_from_coord(test.corners_coord());
    // for (auto v : c) {
    //     std::cout << v << ' ';
    // }
    // std::cout << '\n';

    // printf("edges coord: %x\n", test.edges_coord());
    // auto e = P2Coord::edges_from_coord(test.edges_coord());
    // for (auto v : e) {
    //     std::cout << v << ' ';
    // }
    // std::cout << '\n';

    // printf("ud coord: %x\n", test.ud_coord());
    // auto ud = P2Coord::ud_from_coord(test.ud_coord());
    // for (auto v : ud) {
    //     std::cout << v << ' ';
    // }
    // std::cout << '\n';

    return 0;
}