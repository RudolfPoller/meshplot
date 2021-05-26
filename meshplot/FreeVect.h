/*
 * FreeVect.h
 *
 *  Created on: May 17th, 2021
 *      Author: Dr. R. Poller
 *
 *  Task
 *      Free vector
 *
 */

#ifndef FREEVECT_H_
#define FREEVECT_H_

#include "meshplot.h"


template<typename CoordType>
class FreeVect {

    static_assert(eligible<CoordType>() == true, "invalid type for coordinates");

    CoordType x, y, z;

    void printCoos(void) const;

public:
    FreeVect();
    FreeVect(const CoordType, const CoordType);
    FreeVect(const CoordType, const CoordType, const CoordType);
    FreeVect(const FreeVect &other);
    FreeVect(FreeVect &&other) = default;
    FreeVect& operator=(const FreeVect &other);
    FreeVect& operator=(FreeVect &&other) = default;

    void setX(CoordType x) { this->x = x; }
    void setY(CoordType y) { this->y = y; }
    void setZ(CoordType z) { this->z = z; }

    CoordType getX() const { return x; }
    CoordType getY() const { return y; }
    CoordType getZ() const { return z; }

    CoordType abs() const { return std::sqrt(x*x + y*y + z*z); }

    FreeVect operator-(void) const { return FreeVect(-x, -y, -z); }

    void print(void) const;
    void print(std::string title) const;
};

template<typename CoordType>
FreeVect<CoordType>::FreeVect() {
    x = y = z = static_cast<CoordType>(0);
}

template<typename CoordType>
FreeVect<CoordType>::FreeVect(const CoordType x, const CoordType y) {
    this->x = x;
    this->y = y;
    this->z = static_cast<CoordType>(0);
}

template<typename CoordType>
FreeVect<CoordType>::FreeVect(const CoordType x, const CoordType y, const CoordType z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template<typename CoordType>
FreeVect<CoordType>& FreeVect<CoordType>::operator=(const FreeVect<CoordType> &other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

template<typename CoordType>
FreeVect<CoordType>::FreeVect(const FreeVect<CoordType> &other) {
    x = other.x;
    y = other.y;
    z = other.z;
}


// Printing

template<typename CoordType>
void FreeVect<CoordType>::printCoos(void) const
{
    std::ios_base::fmtflags prevformat = std::cout.flags();

    std::cout << std::left <<
            std::setw(COORD_FIELDWIDTH) << x <<
            std::setw(COORD_FIELDWIDTH) << y <<
            std::setw(COORD_FIELDWIDTH) << z << "\n";
    std::cout.flags(prevformat);
}

template<typename CoordType>
void FreeVect<CoordType>::print(void) const
{
    printCoos();
}

template<typename CoordType>
void FreeVect<CoordType>::print(std::string title) const
{
    std::cout << title << "\n";
    printCoos();
}

template<typename CoordType>
FreeVect<CoordType> operator+(const FreeVect<CoordType> a, const FreeVect<CoordType> b)
{
    FreeVect<CoordType> c;

    c.setX(a.getX() + b.getX());
    c.setY(a.getY() + b.getY());
    c.setZ(a.getZ() + b.getZ());
    return c;
}

template<typename CoordType>
FreeVect<CoordType> operator-(const FreeVect<CoordType> a, const FreeVect<CoordType> b)
{
    return a + (-b);
}

template<typename CoordType>
FreeVect<CoordType> operator*(CoordType a, FreeVect<CoordType> v) {
    return FreeVect<CoordType>(a * v.getX(), a * v.getY(), a * v.getZ());
}

template<typename CoordType>
FreeVect<CoordType> operator*(FreeVect<CoordType> v, CoordType a) {
    return FreeVect<CoordType>(v.getX() * a, v.getY() * a, v.getZ() * a);
}

typedef FreeVect<GLfloat>   RealVector;
typedef FreeVect<int>       IntVector;

int rotDir(const RealVector, const RealVector);
float vectAngleRad(const RealVector, const RealVector);
float vectAngleDeg(const RealVector, const RealVector);
float operator*(const RealVector, const RealVector);
RealVector operator&(const RealVector, const RealVector);

inline float rotAngleDeg(const RealVector a, const RealVector b) {
    return rotDir(a, b) * vectAngleDeg(a, b);
}

#endif /* FREEVECT_H_ */
