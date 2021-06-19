/*
 * Point.h
 *
 *  Created on: Apr. 7th, 2021
 *      Author: Dr. Rudolf Poller
 *
 *  Task
 *  	Point and node set definitions
 *
 */

#ifndef POINT_H_
#define POINT_H_

#include "../meshplot.h"
#include "FreeVect.h"


template<typename CoordType>
class Point {

    static_assert(eligible<CoordType>(), "invalid type for coordinates");

    CoordType x, y, z;

public:

	Point() { x = y = z = static_cast<CoordType>(0); };
	Point(const CoordType x, const CoordType y);
	Point(const CoordType x, const CoordType y, const CoordType z);
    Point(const Point& other);
	Point(Point &&other) = default;
	Point& operator=(const Point &other);
	Point& operator=(Point &&other) = default;

	virtual ~Point() {}

    void compX(CoordType x) { this->x = x; }
    void compY(CoordType y) { this->y = y; }
    void compZ(CoordType z) { this->z = z; }

    CoordType compX(void) const { return x; }
    CoordType compY(void) const { return y; }
    CoordType compZ(void) const { return z; }

    std::list<CoordType> listPos(void) const;

    void print(std::ostream&, std::string title) const;
    void print(std::string title) const;
};

template<typename CoordType>
Point<CoordType>::Point(const CoordType x, const CoordType y) {
    this->x = x;
    this->y = y;
    this->z = static_cast<CoordType>(0);
}


template<typename CoordType>
Point<CoordType>::Point(const CoordType x, const CoordType y, const CoordType z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template<typename CoordType>
Point<CoordType>::Point(const Point<CoordType>& other) {
    x = other.x;
    y = other.y;
    z = other.z;
}

template<typename CoordType>
Point<CoordType>& Point<CoordType>::operator=(const Point &other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

template<typename CoordType>
std::list<CoordType> Point<CoordType>::listPos(void) const
{
    std::list<CoordType> cooList;

    cooList.push_back(x);
    cooList.push_back(y);
    cooList.push_back(z);
    return cooList;
}

/*
 * Printing
 */

template<typename CoordType>
std::ostream& operator<<(std::ostream& os, const Point<CoordType>& p)
{
    std::ios_base::fmtflags prevformat = os.flags();

    os << std::left
       << std::setw(COORD_FIELDWIDTH) << p.compX()
       << std::setw(COORD_FIELDWIDTH) << p.compY()
       << std::setw(COORD_FIELDWIDTH) << p.compZ()
       << "\n";
    os.flags(prevformat);
    return os;
}

template<typename CoordType>
void Point<CoordType>::print(std::ostream& os, std::string title) const
{
    std::ios_base::fmtflags prevformat = os.flags();

    os << std::left << std::setw(LABEL_FIELDWIDTH) << title;
    os << *this;
    os.flags(prevformat);
}

template<typename CoordType>
inline void Point<CoordType>::print(std::string title) const
{
    print(std::cout, title);
}

typedef Point<int>      IntPoint;
typedef Point<GLfloat>  RealPoint;

typedef std::pair<serial, RealPoint>   LabPoint;
typedef std::pair<serial, RealPoint*>  LabPointP;
typedef std::map<serial, RealPoint>    NodeSet;


// Global operators

template<typename CoordType>
Point<CoordType> operator+(const Point<CoordType>& a, const FreeVect<CoordType>& v)
{
    Point<CoordType> b;

    b.compX(a.compX() + v.compX());
    b.compY(a.compY() + v.compY());
    b.compZ(a.compZ() + v.compZ());
    return b;
}

template<typename CoordType>
FreeVect<CoordType> operator-(const Point<CoordType>& a, const Point<CoordType>& b)
{
    FreeVect<CoordType> v;

    v.compX(a.compX() - b.compX());
    v.compY(a.compY() - b.compY());
    v.compZ(a.compZ() - b.compZ());
    return v;
}

void getCoordBounds(const NodeSet&, reals4&);
void printNodes(const NodeSet&);

#endif /* POINT_H_ */
