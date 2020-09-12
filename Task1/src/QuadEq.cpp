/** @file */
#include "TestEq.h"
#include "QuadEq.h"



namespace constants {
    double eps = 0.000001;
    int INF = -1;
    int precision = 6;
}

bool isZero(double x) {
    assert(std::isfinite(x));
    if (fabs(x) <= constants::eps) {
        return true;
    }
    return false;
}


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

void Solver() {
    std::cout << "Square equation solver\n";
    TestSolveLinEq();
    TestSolveQuadEq();
    double a = NAN, b = NAN, c = NAN;
    std::cout << "Enter the coefficients a, b, c of the quadratic equation\n";
    std::cin >> a >> b >> c;
    if (std::cin.fail()) {
        std::cout << "Invalid input.\nExit.\n";
        exit(1);
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

