#pragma once
//! @file

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>

namespace constants {
    extern double eps;
    extern int INF;
    extern int precision;
}


/*! Checks double value for proximity to zero
    @param [in] x some double value
    
    @return true if the argument is close to zero
*/
bool isZero(double x);


/*! Solves a linear equation bx + c = 0

 @param [in] b b-coefficient
 @param [in] c c-coefficient
 @param [out] root Reference to root

 @return Number of roots

 @note In case of infinite number of roots,
       returns constants::INF
*/
int SolveLinEq(double b, double c, double &root);


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
int SolveQuadEq(double a, double b, double c, double &root1, double &root2);


void Solver();
