#include <iostream>

#include "g1coord.hpp"
#include "g1solver.hpp"
#include "move.hpp"

int main() {
    Maneuver test_man(std::string("R B2 U' L2 U2 B2 F2 R2 U L2 B2 L F2 R' D B L D2 U2 F2"));

    G1 test(0, 0, 0);
    test.moved(test_man);
    printf("distance: %d\n", test.solving_distance());
    g1_ida(test);
    
    return 0;
}