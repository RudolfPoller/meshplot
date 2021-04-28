//============================================================================
// Name        : meshplot.cpp
// Author      : Dr. Rudolf Poller
// Version     : 1.0
// Copyright   : Learning
// Description : Draws the sides of a set of polygons
//               conceived as a finite element mesh
//============================================================================

#include <iostream>
#include <cmath>
using namespace std;

#include <GL/glew.h>

#include "meshplot.h"
#include "Point.h"
#include "Polygon.h"

typedef tuple<GLdouble, GLdouble, GLdouble, GLdouble> reals4;

typedef pair<NodeSet, ElemSet> FEMesh;

// Geometry definition of the X window
const int XWinOrigX  =	  50;
const int XWinOrigY  =	  60;
const int XWinWidth  =	1100;
const int XWinHeight =	 600;

FEMesh mesh;

template<typename T>
inline T midval(T min, T max) {
	return 0.5 * (max + min);
}

template<typename T>
inline T halfdist(T dist) {
	return 0.5 * dist;
}

extern void ReadFEMesh(FEMesh&);

int  InitGraphics(int, char**);
void PlottingFEMesh(void);
void SetViewSystem(GLsizei, GLsizei);
void SetWinEqSides(reals4&);
void LookThruWin(reals4);
void WriteStepTitle(const string&);

int main(int argc, char **argv)
{
	cout << "*** Plotting FE Mesh by openGL" << endl;
	ReadFEMesh(mesh);
	if (!InitGraphics(argc, argv))
			return 1;
	glutMainLoop();
	return 0;
}

int InitGraphics(int argc, char **argv)
{
	GLenum glew_check;

	WriteStepTitle("Displaying mesh");

	// Initialization of GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Window
	glutInitWindowSize(XWinWidth, XWinHeight);
	glutInitWindowPosition(XWinOrigX, XWinOrigY);
	glutCreateWindow("FE Mesh");

	// Checking for openGL availability
	glew_check = glewInit();
	if (GLEW_OK != glew_check) {
		cerr << "GLEW Error: " << glewGetErrorString(glew_check) << endl;
		return 0;
	}

	// Printing the version of the current openGL implementation
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

	// Background color: white
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// Registering the drawing procedure
	glutDisplayFunc(PlottingFEMesh);

	// Registering the reshape procedure
	glutReshapeFunc(SetViewSystem);

	return 1;
}

void SetViewSystem(GLsizei width, GLsizei height)
{
	GLint cornx, corny;
	GLint origx, origy;
	GLsizei sidelg, sideoffs;

	sidelg = min(width, height);
	origx = halfdist(width);
	origy = halfdist(height);
	sideoffs = halfdist(sidelg);
	cornx = origx - sideoffs;
	corny = origy - sideoffs;
	glViewport(cornx, corny, sidelg, sidelg);
}

void PlottingFEMesh(void)
{
	const NodeSet& nodes = mesh.first;
	const ElemSet& elems = mesh.second;
	GLdouble xmin, xmax, ymin, ymax;

	glClear(GL_COLOR_BUFFER_BIT);
	GetCoordExtremes(nodes, xmin, xmax, ymin, ymax);
	LookThruWin(reals4(xmin, xmax, ymin, ymax));
	for (const pair<serial, Polygon>& elem : elems)
		elem.second.DrawLines();
	glFlush();
}


/*
 * The FE mesh will be viewed through a window
 * of equal sides
 */

void SetWinEqSides(reals4& geodat)
{
	const GLdouble stripRatio = 0.1;
	GLdouble sidelg;
	GLdouble xmin, xmax, ymin, ymax;
	GLdouble width, height;
	GLdouble stripx, stripy;
	GLdouble sideoffs, origx, origy;

	tie(xmin, xmax, ymin, ymax) = geodat;
	width  = xmax - xmin;
	height = ymax - ymin;
	stripx = width * stripRatio;
	stripy = height * stripRatio;
	xmin -= stripx; xmax += stripx;
	ymin -= stripy; ymax += stripy;
	sidelg = fmax(xmax - xmin, ymax - ymin);
	sideoffs = halfdist(sidelg);
	origx = midval(xmin, xmax);
	origy = midval(ymin, ymax);
	xmin = origx - sideoffs;
	xmax = origx + sideoffs;
	ymin = origy - sideoffs;
	ymax = origy + sideoffs;
	geodat = reals4(xmin, xmax, ymin, ymax);
}


/*
 * Creation of the window through which
 * the FE mesh will be viewed
 */

void LookThruWin(reals4 geodat)
{
	GLdouble xmin, xmax, ymin, ymax;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	SetWinEqSides(geodat);
	tie(xmin, xmax, ymin, ymax) = geodat;
	gluOrtho2D(xmin, xmax, ymin, ymax);
	glMatrixMode(GL_MODELVIEW);
}

void WriteStepTitle(const string& title)
{
	cout << ". " << title << "..." << endl;
}
