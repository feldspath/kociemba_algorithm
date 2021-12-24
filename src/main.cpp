#include <iostream>

#include "g1coord.hpp"
#include "g1solver.hpp"
#include "move.hpp"

int main() {
    Maneuver test_man(std::string("L B2 F' L2 F2 L'"));
    //Maneuver test_man(std::string("R"));
    test_man.print();

    G1 test(0, 0, 0);
    test.moved(test_man);

    std::vector<G1Solve> g1_solves;
    g1_solver(test, g1_solves);
    
    return 0;
}