/*
 * Point.cpp
 *
 *  Created on: Apr. 7th, 2021
 *      Author: Dr. Rudolf Poller
 *
 *  Task
 *  	Point methods and related functions
 *
 */

#include "Point.h"

using namespace std;


Point::Point(GLfloat x, GLfloat y) {
	this->x = x;
	this->y = y;
	this->z = 0.0f;
}

Point::Point(GLfloat x, GLfloat y, GLfloat z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point::~Point() {
	// TODO Auto-generated destructor stub
}

Point::Point(const Point &other) {
	x = other.x;
	y = other.y;
	z = other.z;
}

Point& Point::operator=(const Point &other) {
	if (this != &other) {
		x = other.x;
		y = other.y;
		z = other.z;
	}
	return *this;
}

list<GLfloat> Point::ListPos(void) const {
    list<GLfloat> cooList;
    cooList.push_back(x);
    cooList.push_back(y);
    cooList.push_back(z);
    return cooList;
}

void GetCoordExtremes(const NodeSet& nodes, reals4& geodat)
{
	GLdouble x, y;
    GLdouble xmin, xmax;
    GLdouble ymin, ymax;
	Point point1;

    tie(xmin, xmax, ymin, ymax) = geodat;
	point1 = nodes.begin()->second;
	xmin = xmax = point1.GetX();
	ymin = ymax = point1.GetY();
	for (const pair<serial, Point>& node : nodes) {
		x = node.second.GetX();
		y = node.second.GetY();
		xmin = fmin(xmin, x);
		xmax = fmax(xmax, x);
		ymin = fmin(ymin, y);
		ymax = fmax(ymax, y);
	}
    geodat = reals4(xmin, xmax, ymin, ymax);
}

#define FIELDWIDTH  10

void PrintNodes(const NodeSet& nodes)
{
	cout << "@ Nodes:\n";
	for (const pair<serial, Point>& node : nodes)
		cout << setw(FIELDWIDTH) << node.first <<
			setw(FIELDWIDTH) << node.second.GetX() <<
			setw(FIELDWIDTH) << node.second.GetY() << "\n";
	cout << endl;
}
