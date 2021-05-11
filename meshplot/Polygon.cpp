/*
 * Polygon.cpp
 *
 *  Created on: Apr. 7th, 2021
 *      Author: Dr. Rudolf Poller
 *
 *  Task
 *  	Polygon methods and related functions
 *
 */


#include "Polygon.h"

using namespace std;

Polygon::Polygon(LabPointP C1, LabPointP C2, LabPointP C3)
{
	p_nodes.push_back(C1);
	p_nodes.push_back(C2);
	p_nodes.push_back(C3);
}

Polygon::Polygon(LabPointP C1, LabPointP C2, LabPointP C3, LabPointP C4)
{
	p_nodes.push_back(C1);
	p_nodes.push_back(C2);
	p_nodes.push_back(C3);
	p_nodes.push_back(C4);
}

Polygon::Polygon(list<LabPointP>& ps)
{
	p_nodes.splice(p_nodes.begin(), ps);
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


void Polygon::AddCorner(const LabPointP& C)
{
	p_nodes.push_back(C);
}


/*
 * Draws the sides of the polygon as lines one by one
 *
 * The loop will be closed so that the last and the
 * first nodes will also be connected.
 */

list<GLfloat> Polygon::LsConNDCoords(void) const
{
	const LabPointP first = p_nodes.front();
	const LabPointP last = p_nodes.back();
	LabPointP secp1, secp2;
	list<LabPointP>::const_iterator i, j;
	list<GLfloat> conNodes;

    for (i = j = p_nodes.begin(), ++j; j != p_nodes.end(); ++i, ++j){
        secp1 = *i; secp2 = *j;
        conNodes.splice(conNodes.cend(), secp1.second->ListPos());
        conNodes.splice(conNodes.cend(), secp2.second->ListPos());
    }
    conNodes.splice(conNodes.cend(), last.second->ListPos());
    conNodes.splice(conNodes.cend(), first.second->ListPos());
    return conNodes;
}

void Polygon::Print(serial label) const
{
	cout << setw(5) << label;
	for (const LabPointP& corner : p_nodes)
		cout << setw(5) << corner.first;
	cout << "\n";
}

void PrintElements(const ElemSet& elems)
{
	cout << "@ Elements:\n";
	for (const pair<serial, Polygon>& elem : elems)
		elem.second.Print(elem.first);
	cout << endl;
}
