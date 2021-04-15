/*
 * Polygon.cpp
 *
 *  Created on: Apr. 7th, 2021
 *      Author: Dr. R. Poller
 *
 *  Task
 *  	Polygon methods and related functions
 *
 */


#include <list>
#include <gl/glut.h>

#include "Polygon.h"



Polygon::Polygon(Point *p_C1, Point *p_C2, Point *p_C3)
{
	p_nodes.push_back(p_C1);
	p_nodes.push_back(p_C2);
	p_nodes.push_back(p_C3);
}

Polygon::Polygon(Point *p_C1, Point *p_C2, Point *p_C3, Point *p_C4)
{
	p_nodes.push_back(p_C1);
	p_nodes.push_back(p_C2);
	p_nodes.push_back(p_C3);
	p_nodes.push_back(p_C4);
}

Polygon::Polygon(list<Point*> p_corners)
{
	p_nodes.splice(p_nodes.begin(), p_corners);
}

Polygon::~Polygon() {
	// TODO Auto-generated destructor stub
}

Polygon::Polygon(const Polygon &other) {
	p_nodes = other.p_nodes;
}

Polygon& Polygon::operator=(const Polygon &other) {
	if (this != &other)
		p_nodes = other.p_nodes;
	return *this;
}


void Polygon::AddCorner(Point& C)
{
	p_nodes.push_back(&C);
}


/*
 * Draws the sides of the polygon as lines one by one
 *
 * The loop will be closed so that the last and the
 * first nodes will also be connected.
 */

void Polygon::DrawLines(void) const
{
	const Point *p_first = p_nodes.front();
	const Point *p_last = p_nodes.back();
	Point *p_secp1, *p_secp2;
	list<Point*>::const_iterator i, j;

	glColor3f(0, 0, 0); // black
	glLineWidth(1.0);

	glBegin(GL_LINES);

		for (i = j = p_nodes.begin(), ++j; j != p_nodes.end(); ++i, ++j){
			p_secp1 = *i; p_secp2 = *j;
			glVertex2f(p_secp1->GetX(), p_secp1->GetY());
			glVertex2f(p_secp2->GetX(), p_secp2->GetY());
		}

		glVertex2f(p_last->GetX(), p_last->GetY());
		glVertex2f(p_first->GetX(), p_first->GetY());

	glEnd();
}
