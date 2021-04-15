//============================================================================
// Name        : meshplot.cpp
// Author      : Dr. R. Poller
// Version     : 1.0
// Copyright   : Learning
// Description : Draws the sides of a set of polygons
//               conceived as a finite element mesh
//============================================================================

#include <iostream>
#include <cmath>
using namespace std;

#include "meshplot.h"
#include "Point.h"
#include "Polygon.h"

typedef tuple<GLdouble, GLdouble, GLdouble, GLdouble> reals4;

typedef pair<NodeSet, ElemSet> FEMesh;

// Geometry data of the X window
const int XWinOrigX  =	  50;
const int XWinOrigY  =	  50;
const int XWinWidth  =	1100;
const int XWinHeight =	 600;

FEMesh mesh;

inline GLdouble midval(GLdouble min, GLdouble max){
	return 0.5 * (max + min);
}

inline GLdouble halfdist(GLdouble dist){
	return 0.5 * dist;
}

extern void ReadFEMesh(FEMesh&);

void InitGraphics(int, char**);
void PlottingFEMesh(void);

void SetViewSystem(GLsizei, GLsizei);

void SetVpEqSidesCent(GLsizei, GLsizei, GLint&, GLint&, GLsizei&);
void SetWinEqSides(reals4&);

void LookThruWin(reals4);

void WriteStepTitle(const string&);

int main(int argc, char **argv)
{
	cout << "*** Plotting FE Mesh by openGL" << endl;
	ReadFEMesh(mesh);
	InitGraphics(argc, argv);
	glutMainLoop();
	return 0;
}

void InitGraphics(int argc, char **argv)
{
	WriteStepTitle("Displaying mesh");

	// Initialization of GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Window
	glutInitWindowSize(XWinWidth, XWinHeight);
	glutInitWindowPosition(XWinOrigX, XWinOrigY);
	glutCreateWindow("FE Mesh");

	// Background color: white
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// Registering the drawing procedure
	glutDisplayFunc(PlottingFEMesh);

	// Registering the reshape procedure
	glutReshapeFunc(SetViewSystem);
}

void SetViewSystem(GLsizei vpWidth, GLsizei vpHeight)
{
	GLint vpOrgX, vpOrgY;
	GLsizei vpSideLg;

	// X window
	SetVpEqSidesCent(vpWidth, vpHeight, vpOrgX, vpOrgY, vpSideLg);
	glViewport(vpOrgX, vpOrgY, vpSideLg, vpSideLg);
}

void PlottingFEMesh(void)
{
	const NodeSet& nodes = mesh.first;
	const ElemSet& elems = mesh.second;
	GLdouble xmin, xmax, ymin, ymax;
	GLdouble centx, centy;

	glClear(GL_COLOR_BUFFER_BIT);

	GetCoordExtremes(nodes, xmin, xmax, ymin, ymax);
	centx = midval(xmin, xmax);
	centy = midval(ymin, ymax);

	// View position of the FE mesh
	gluLookAt(centx, centy, 0.0, centx, centy, -100.0, 0.0, 1.0, 0.0);
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
	GLdouble Width, Height;
	GLdouble stripX, stripY;
	GLdouble BrdOffsX, BrdOffsY;

	tie(xmin, xmax, ymin, ymax) = geodat;
	Width  = xmax - xmin;
	Height = ymax - ymin;
	stripX = Width * stripRatio;
	stripY = Height * stripRatio;
	xmin -= stripX; xmax += stripX;
	ymin -= stripY; ymax += stripY;
	sidelg = fmax(Width, Height);
	BrdOffsX = halfdist(sidelg - Width);
	xmin -= BrdOffsX; xmax += BrdOffsX;
	BrdOffsY = halfdist(sidelg - Height);
	ymin -= BrdOffsY; ymax += BrdOffsY;
	geodat = reals4(xmin, xmax, ymin, ymax);
}


/*
 * Setting the viewport (Vp) geometric data
 *
 * The viewport will be centered in the X window
 * and will have maximal equal sides
 */

void SetVpEqSidesCent(
		GLsizei width, GLsizei height,
		GLint& origx, GLint& origy,
		GLsizei& sidelg
		)
{
	sidelg = min(width, height);
	origx = 0.5 * (width - sidelg);
	origy = 0.5 * (height - sidelg);
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
