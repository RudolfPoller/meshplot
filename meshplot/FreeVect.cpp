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
    return a.getX()*b.getX() + a.getY()*b.getY() + a.getZ()*b.getZ();
}


// Vector product

RealVector operator&(const RealVector a, const RealVector b)
{
    RealVector c;

    c.setX(a.getY()*b.getZ() - b.getY()*a.getZ());
    c.setY(b.getX()*a.getZ() - a.getX()*b.getZ());
    c.setZ(a.getX()*b.getY() - b.getX()*a.getY());
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
    return acos(a * b / (a.abs() * b.abs()));
}


// Angle of two vectors in degrees

float vectAngleDeg(const RealVector a, const RealVector b)
{
    using namespace std::numbers;
    const float halfCircDeg = 180.0;

    return vectAngleRad(a, b) / pi * halfCircDeg;
}
