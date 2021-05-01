/*
 * readmesh.cpp
 *
 *  Created on: Apr. 7th, 2021
 *      Author: Dr. Rudolf Poller
 *
 *  Synopsis
 *  	Reads mesh data from the standard input
 *
 *  	The reading is done by modules generated by
 *  	bison (parser) and flex (lexical analyzer)
 *
 */

#include "Point.h"
#include "Polygon.h"

#include "meshparser.tab.hpp"
#include "ansparser.tab.hpp"

extern string problem_title;
extern void WriteStepTitle(const string&);

const yy::parser::debug_level_type      ParserDebug = 0;
const ans::parser::debug_level_type ans_ParserDebug = 0;

typedef pair<NodeSet, ElemSet> FEMesh;
FEMesh *p_mesh;

void WriteStatistics(void);
void PrintNodes(const NodeSet&);
void PrintElements(const ElemSet&);

void ReadFEMesh(input_grammar format, FEMesh& mesh)
{
	p_mesh = &mesh;
	WriteStepTitle("Reading mesh data");
	switch (format) {
	case ansys:
		{
			ans::parser meshreader;
			meshreader.set_debug_level(ans_ParserDebug);
			meshreader.parse();
			break;
		}
	case meshplot:
	default:
		{
			yy::parser meshreader;
			meshreader.set_debug_level(ParserDebug);
			meshreader.parse();
			break;
		}
	}
	WriteStatistics();
}

void WriteStatistics(void)
{
	if (problem_title.size())
		cout << problem_title << endl;
	cout << "\tnumber of nodes:    " << setw(4) << p_mesh->first.size() << endl;
	cout << "\tnumber of elements: " << setw(4) << p_mesh->second.size() << endl;
}

