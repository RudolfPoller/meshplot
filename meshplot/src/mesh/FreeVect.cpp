/*
 * FreeVect.cpp
 *
 *  Created on: May 17th, 2021
 *      Author: Dr. R. Poller
 *
 *  Task
 *      Free vector
 *
 */

#include "FreeVect.h"

using namespace std;

const RealVector baseI(1.0f, 0.0f, 0.0f);
const RealVector baseJ(0.0f, 1.0f, 0.0f);
const RealVector baseK(0.0f, 0.0f, 1.0f);


// Scalar product

float operator*(const RealVector a, const RealVector b)
{
    return a.compX()*b.compX() + a.compY()*b.compY() + a.compZ()*b.compZ();
}


// Vector product

RealVector operator&(const RealVector a, const RealVector b)
{
    RealVector c;

    c.compX(a.compY()*b.compZ() - b.compY()*a.compZ());
    c.compY(b.compX()*a.compZ() - a.compX()*b.compZ());
    c.compZ(a.compX()*b.compY() - b.compX()*a.compY());
    return c;
}


// Direction of rotation

int rotDir(const RealVector a, const RealVector b)
{
    float smagn = (a & b) * baseK;

    if (smagn == 0.0f)
        return 0;
    else
        return std::signbit(smagn) == true ? -1 : 1;
}


// Angle of two vectors in radians

float vectAngleRad(const RealVector a, const RealVector b)
{
    return acos(a * b / (a.norm() * b.norm()));
}


// Angle of two vectors in degrees

float vectAngleDeg(const RealVector a, const RealVector b)
{
    using namespace std::numbers;
    const float halfCircDeg = 180.0;

    return vectAngleRad(a, b) / pi * halfCircDeg;
}
