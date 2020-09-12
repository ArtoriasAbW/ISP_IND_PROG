#include <cassert>
#include "QuadEq.h"
#include "TestEq.h"

void TestSolveLinEq() {
    double root;

    assert(SolveLinEq(4, -8, root) ==  1);
    assert(root == 2);

    assert(SolveLinEq(0, 2.434, root) == 0);

    assert(SolveLinEq(4, 0, root) == 1);
    assert(root == 0);

    assert(SolveLinEq(0, 0, root) == constants::INF);

    std::cerr << "TestSolveLinEq Done\n"; 
}

void TestSolveQuadEq() {
    double root1, root2;

    assert(SolveQuadEq(1, 2, 1, root1, root2) == 1);
    assert(root1 == -1);

    assert(SolveQuadEq(1, 5, 423, root1, root2) == 0);

    assert(SolveQuadEq(1, 5, 6, root1, root2) == 2);
    assert(root1 == -2 && root2 == -3);

    assert(SolveQuadEq(1, 4, 0, root1, root2) == 2);
    assert(root1 == 0 && root2 == -4);

    assert(SolveQuadEq(432.312312, 0, 0, root1, root2) == 1);
    assert(root1 == 0);

    assert(SolveQuadEq(0, 0, 0, root1, root2) == constants::INF);

    std::cerr << "TestSolveQuadEq Done\n";
}
