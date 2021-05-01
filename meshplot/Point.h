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


class Point {

	GLfloat x, y, z;

public:

	Point() { x = y = z = 0.0f; };

	Point(GLfloat x, GLfloat y);
	Point(GLfloat x, GLfloat y, GLfloat z);

	Point(const Point&);
	Point(Point&&) = default;
	Point& operator=(const Point&);
	Point& operator=(Point&&) = default;

	virtual ~Point();

	GLfloat GetX(void) const { return x; }
	GLfloat GetY(void) const { return y; }

};

typedef map<serial, Point> NodeSet;

void GetCoordExtremes(const NodeSet&, GLdouble&, GLdouble&, GLdouble&, GLdouble&);

#endif /* POINT_H_ */
