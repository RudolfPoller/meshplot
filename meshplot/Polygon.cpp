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

Polygon::Polygon(const LabPointP& C1, const LabPointP& C2, const LabPointP& C3)
{
	p_nodes.push_back(C1);
	p_nodes.push_back(C2);
	p_nodes.push_back(C3);
}

Polygon::Polygon(const LabPointP& C1, const LabPointP& C2, const LabPointP& C3, const LabPointP& C4)
{
	p_nodes.push_back(C1);
	p_nodes.push_back(C2);
	p_nodes.push_back(C3);
	p_nodes.push_back(C4);
}

Polygon::Polygon(list<LabPointP>& ps)
{
	for (const LabPointP& p : ps)
	    p_nodes.push_back(p);
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


void Polygon::addCorner(const LabPointP& C)
{
	p_nodes.push_back(C);
}


/*
 * Provides the coordinates of nodes pairs element sides
 * or their segments in the case of higher order approximation.
 *
 * The loop will be closed so that the last and the
 * first nodes will also be connected.
 */

list<GLfloat> Polygon::listConnCoos(void) const
{
	const LabPointP first = p_nodes.front();
	const LabPointP last = p_nodes.back();
	LabPointP secp1, secp2;
	list<LabPointP>::const_iterator i, j;
	list<GLfloat> connNodes;

    for (i = j = p_nodes.begin(), ++j; j != p_nodes.end(); ++i, ++j){
        secp1 = *i; secp2 = *j;
        connNodes.splice(connNodes.cend(), secp1.second->listPos());
        connNodes.splice(connNodes.cend(), secp2.second->listPos());
    }
    connNodes.splice(connNodes.cend(), last.second->listPos());
    connNodes.splice(connNodes.cend(), first.second->listPos());
    return connNodes;
}


/*
 * Provides the node coordinates in order
 */

list<GLfloat> Polygon::listNodeCoos(void) const
{
    list<GLfloat> nodeCoos;

    for (const LabPointP& p_node : p_nodes)
        nodeCoos.splice(nodeCoos.cend(), p_node.second->listPos());
    return nodeCoos;
}

#define FIELDWIDTH  5

void Polygon::print(serial label) const
{
	cout << setw(FIELDWIDTH) << label;
	for (const LabPointP& corner : p_nodes)
		cout << setw(FIELDWIDTH) << corner.first;
	cout << "\n";
}

void printElements(const ElemSet& elems)
{
	cout << "@ Elements:\n";
	for (const std::pair<serial, Polygon>& elem : elems)
		elem.second.print(elem.first);
	cout << endl;
}
