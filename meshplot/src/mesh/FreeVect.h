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

#include "../meshplot.h"


template<typename CoordType>
class FreeVect {

    static_assert(eligible<CoordType>(), "invalid type for coordinates");

    CoordType x, y, z;

public:
    FreeVect();
    FreeVect(const CoordType, const CoordType);
    FreeVect(const CoordType, const CoordType, const CoordType);
    FreeVect(const FreeVect &other);
    FreeVect(FreeVect &&other) = default;
    FreeVect& operator=(const FreeVect &other);
    FreeVect& operator=(FreeVect &&other) = default;

    void compX(CoordType x) { this->x = x; }
    void compY(CoordType y) { this->y = y; }
    void compZ(CoordType z) { this->z = z; }

    CoordType compX() const { return x; }
    CoordType compY() const { return y; }
    CoordType compZ() const { return z; }

    CoordType norm() const { return std::sqrt(x*x + y*y + z*z); }

    FreeVect operator-(void) const { return FreeVect(-x, -y, -z); }

    std::ostream& operator<<(std::ostream&) const;
    void print(std::ostream&, std::string title) const;
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


/*
 * Printing
 */

template<typename CoordType>
std::ostream& operator<<(std::ostream& os, const FreeVect<CoordType>& v)
{
    std::ios_base::fmtflags prevformat = os.flags();

    os << std::left <<
          std::setw(COORD_FIELDWIDTH) << v.compX() <<
          std::setw(COORD_FIELDWIDTH) << v.compY() <<
          std::setw(COORD_FIELDWIDTH) << v.compZ() << "\n";
    os.flags(prevformat);
    return os;
}

template<typename CoordType>
inline void FreeVect<CoordType>::print(std::ostream& os, std::string title) const
{
    std::ios_base::fmtflags prevformat = os.flags();

    os << std::left << std::setw(LABEL_FIELDWIDTH) << title;
    os << *this;
    os.flags(prevformat);
}

template<typename CoordType>
inline void FreeVect<CoordType>::print(std::string title) const
{
    print(std::cout, title);
}

template<typename CoordType>
FreeVect<CoordType> operator+(const FreeVect<CoordType> a, const FreeVect<CoordType> b)
{
    FreeVect<CoordType> c;

    c.compX(a.compX() + b.compX());
    c.compY(a.compY() + b.compY());
    c.compZ(a.compZ() + b.compZ());
    return c;
}

template<typename CoordType>
FreeVect<CoordType> operator-(const FreeVect<CoordType> a, const FreeVect<CoordType> b)
{
    return a + (-b);
}

template<typename CoordType>
FreeVect<CoordType> operator*(CoordType a, FreeVect<CoordType> v) {
    return FreeVect<CoordType>(a * v.compX(), a * v.compY(), a * v.compZ());
}

template<typename CoordType>
FreeVect<CoordType> operator*(FreeVect<CoordType> v, CoordType a) {
    return FreeVect<CoordType>(v.compX() * a, v.compY() * a, v.compZ() * a);
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
