/*
 * Polygon.h
 *
 *  Created on: Apr. 7th, 2021
 *      Author: Dr. R. Poller
 *
 *  Task
 *  	Polygon and element definitions
 *
 */

#ifndef POLYGON_H_
#define POLYGON_H_

#include "meshplot.h"
#include "Point.h"

class Polygon {

	list<Point*> p_nodes;

public:

	Polygon() = default;

	Polygon(Point *p_C1, Point *p_C2, Point *p_C3);
	Polygon(Point *p_C1, Point *p_C2, Point *p_C3, Point *p_C4);
	Polygon(list<Point*> p_corners);

	Polygon(const Polygon&);
	Polygon(Polygon&&) = default;
	Polygon& operator=(const Polygon&);
	Polygon& operator=(Polygon&&) = default;

	virtual ~Polygon();

	bool empty(void) const { return p_nodes.empty(); }

	void AddCorner(Point&);
	void DrawLines(void) const;

};

typedef map<serial, Polygon> ElemSet;

#endif /* POLYGON_H_ */
