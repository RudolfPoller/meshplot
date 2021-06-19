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

#include "../meshplot.h"
#include "Point.h"

class Polygon {

	std::list<LabPointP> p_nodes;

public:

	Polygon() = default;

	Polygon(const LabPointP&, const LabPointP&, const LabPointP&);
	Polygon(const LabPointP&, const LabPointP&, const LabPointP&, const LabPointP&);
	Polygon(std::list<LabPointP>&);

	Polygon(const Polygon&);
	Polygon(Polygon&&) = default;
	Polygon& operator=(const Polygon&);
	Polygon& operator=(Polygon&&) = default;

	virtual ~Polygon();

	bool empty(void) const { return p_nodes.empty(); }

	std::list<LabPointP> getNodes(void) const { return p_nodes; }
	std::list<GLfloat> listConnCoos(void) const;
    std::list<GLfloat> listNodeCoos(void) const;

	void addCorner(const LabPointP&);

    void print(std::ostream&, serial) const;
    void print(serial) const;
};

typedef std::map<serial, Polygon> ElemSet;

std::ostream& operator<<(std::ostream& os, const Polygon& p);

#endif /* POLYGON_H_ */
