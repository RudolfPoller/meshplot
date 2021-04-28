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

typedef pair<serial, Point*> LabPointP;

class Polygon {

	list<LabPointP> p_nodes;

public:

	Polygon() = default;

	Polygon(LabPointP, LabPointP, LabPointP);
	Polygon(LabPointP, LabPointP, LabPointP, LabPointP);
	Polygon(list<LabPointP>&);

	Polygon(const Polygon&);
	Polygon(Polygon&&) = default;
	Polygon& operator=(const Polygon&);
	Polygon& operator=(Polygon&&) = default;

	virtual ~Polygon();

	bool empty(void) const { return p_nodes.empty(); }

	void AddCorner(const LabPointP&);
	void DrawLines(void) const;
	void Print(serial) const;

};

typedef map<serial, Polygon> ElemSet;

#endif /* POLYGON_H_ */
