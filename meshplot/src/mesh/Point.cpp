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


void getCoordBounds(const NodeSet& nodes, reals4& geodat)
{
    extern RealPoint mapModelToMoved(const RealPoint&);
    void checkExtremes(const GLfloat, GLdouble&, GLdouble&);
    GLdouble xmin, xmax;
    GLdouble ymin, ymax;
    RealPoint point, point1;

    tie(xmin, xmax, ymin, ymax) = geodat;
    point1 = mapModelToMoved(nodes.begin()->second);
	xmin = xmax = point1.compX();
	ymin = ymax = point1.compY();
	for (const LabPoint& node : nodes) {
	    point = mapModelToMoved(node.second);
        checkExtremes(point.compX(), xmin, xmax);
        checkExtremes(point.compY(), ymin, ymax);
	}
    geodat = reals4(xmin, xmax, ymin, ymax);
}

void checkExtremes(const GLfloat v, GLdouble& min, GLdouble& max)
{
    min = fmin(min, v);
    max = fmax(max, v);
}


/*
 * Printing all the nodes
 */

void printNodes(const NodeSet& nodes)
{
    std::cout << "@ Nodes:\n";
    for (const std::pair<serial, RealPoint>& node : nodes)
        node.second.print(std::to_string(node.first));
}
