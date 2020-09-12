/** @file */
#include <iostream>
#include <cmath>
#include <cassert>
#include <iomanip>

namespace constants {
    double eps = 0.000001;
    int INF = -1;
    int precision = 6;
}

//-----------------------------------------------------------------------
/*! Checks double value for proximity to zero
    @param [in] x some double value
    
    @return true if the argument is close to zero
*/
bool isZero(double x) {
    assert(std::isfinite(x));
    if (fabs(x) <= constants::eps) {
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------


//---------------------------------------------------------------------------
/*! Solves a linear equation bx + c = 0

 @param [in] b b-coefficient
 @param [in] c c-coefficient
 @param [out] root Reference to root

 @return Number of roots

 @note In case of infinite number of roots,
       returns constants::INF
*/
//---------------------------------------------------------------------------
int SolveLinEq(double b, double c, double &root) {
    assert(std::isfinite(b));
    assert(std::isfinite(c));
    if (isZero(b) && isZero(c)) {
        return constants::INF;
    }
    if (isZero(b)) {
        return 0;
    }
    if (isZero(c)) {
        root = 0;
        return 1;
    }
    root = -c / b;
    return 1;
}


//---------------------------------------------------------------------------
/*! Solves a square equation ax^2 + bx + c = 0

 @param [in] a a-coefficient
 @param [in] b b-coefficient 
 @param [in] c c-coefficient
 @param [out] root1 Reference to first root
 @param [out] root2 Reference to second root

 @return Number of roots

 @note In case of infinite number of roots,
       returns constants::INF
*/
//---------------------------------------------------------------------------
int SolveQuadEq(double a, double b, double c, double &root1, double &root2) {
    assert(std::isfinite(a));
    assert(std::isfinite(b));
    assert(std::isfinite(c));
    if (isZero(a)) {
        return SolveLinEq(b, c, root1);
    }
    double d = b * b - 4 * a * c;
    if (d > constants::eps) {
        root1 = (-b + sqrt(d)) / (2 * a);
        root2 = (-b - sqrt(d)) / (2 * a);
        return 2;   
    }
    if (isZero(d)) {   
        root1 = -b / (2 * a);
        return 1;
    }
    return 0;
}

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


int main() {
    std::cout << "Square equation solver\n";
    TestSolveLinEq();
    TestSolveQuadEq();
    double a = NAN, b = NAN, c = NAN;
    std::cout << "Enter the coefficients a, b, c of the quadratic equation\n";
    std::cin >> a >> b >> c;
    if (std::cin.fail()) {
        std::cout << "Invalid input.\nExit.\n";
        return 1;
    }
    double root1, root2;
    int numOfRoots = SolveQuadEq(a, b, c, root1, root2);
    if (numOfRoots == constants::INF) { 
        std::cout << "The equation has an infinite number of roots.\n"; 
    } else {
        std::cout << "numOfRoots = " << numOfRoots << "\n";
        if (numOfRoots == 2) {
            std::cout << std::fixed << std::setprecision(constants::precision) << "root1 = " << root1 << " root2 = " << root2 << "\n";
        } else if (numOfRoots == 1) {
            std::cout << std::fixed << std::setprecision(constants::precision) << "root = " << root1 << "\n";
        }
    }
}
