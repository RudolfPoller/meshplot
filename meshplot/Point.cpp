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

void GetCoordExtremes(
		const NodeSet& nodes,
		GLdouble& xmin, GLdouble& xmax,
		GLdouble& ymin, GLdouble& ymax
		)
{
	GLdouble x, y;
	Point point1;

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
}

void PrintNodes(const NodeSet& nodes)
{
	cout << "@ Nodes:\n";
	for (const pair<serial, Point>& node : nodes)
		cout << setw(10) << node.first <<
			setw(10) << node.second.GetX() <<
			setw(10) << node.second.GetY() << "\n";
	cout << endl;
}
