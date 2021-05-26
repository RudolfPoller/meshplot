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

#include "meshplot.h"
#include "FreeVect.h"


template<typename CoordType>
class Point {

    static_assert(eligible<CoordType>() == true, "invalid type for coordinates");

    CoordType x, y, z;

    void printCoos(void) const
    {
        std::ios_base::fmtflags prevformat = std::cout.flags();

        std::cout << std::left <<
                std::setw(COORD_FIELDWIDTH) << x <<
                std::setw(COORD_FIELDWIDTH) << y <<
                std::setw(COORD_FIELDWIDTH) << z << "\n";
        std::cout.flags(prevformat);
    }

public:

	Point() { x = y = z = static_cast<CoordType>(0); };
	Point(const CoordType x, const CoordType y);
	Point(const CoordType x, const CoordType y, const CoordType z);
    Point(const Point& other);
	Point(Point &&other) = default;
	Point& operator=(const Point &other);
	Point& operator=(Point &&other) = default;

	virtual ~Point() {}

    void setX(CoordType x) { this->x = x; }
    void setY(CoordType y) { this->y = y; }
    void setZ(CoordType z) { this->z = z; }

    CoordType getX(void) const { return x; }
    CoordType getY(void) const { return y; }
    CoordType getZ(void) const { return z; }

    std::list<CoordType> listPos(void) const;

    void print(void) const;

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

template<typename CoordType>
void Point<CoordType>::print(void) const {
    printCoos();
}

template<typename CoordType>
void Point<CoordType>::print(std::string title) const {
    std::cout << title << "\n";
    printCoos();
}

typedef Point<int>      IntPoint;
typedef Point<GLfloat>  RealPoint;

typedef std::pair<serial, RealPoint>   LabPoint;
typedef std::pair<serial, RealPoint*>  LabPointP;
typedef std::map<serial, RealPoint>    NodeSet;

void getCoordBounds(const NodeSet&, reals4&);

template<typename CoordType>
void printNodes(const NodeSet& nodes)
{
    std::ios_base::fmtflags prevformat = std::cout.flags();

    std::cout << "@ Nodes:\n";
    for (const std::pair<serial, RealPoint>& node : nodes)
        std::cout << std::setw(COORD_FIELDWIDTH) << node.first <<
        std::setw(COORD_FIELDWIDTH) << node.second.getX() <<
        std::setw(COORD_FIELDWIDTH) << node.second.getY() <<
        std::setw(COORD_FIELDWIDTH) << node.second.getZ() << "\n";
    std::cout << std::endl;
    std::cout.flags(prevformat);
}


// Global operators

template<typename CoordType>
Point<CoordType> operator+(const Point<CoordType>& a, const FreeVect<CoordType>& v)
{
    Point<CoordType> b;

    b.setX(a.getX() + v.getX());
    b.setY(a.getY() + v.getY());
    b.setZ(a.getZ() + v.getZ());
    return b;
}

template<typename CoordType>
FreeVect<CoordType> operator-(const Point<CoordType>& a, const Point<CoordType>& b)
{
    FreeVect<CoordType> v;

    v.setX(a.getX() - b.getX());
    v.setY(a.getY() - b.getY());
    v.setZ(a.getZ() - b.getZ());
    return v;
}

#endif /* POINT_H_ */
