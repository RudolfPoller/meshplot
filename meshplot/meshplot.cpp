//============================================================================
// Name        : meshplot.cpp
// Author      : Dr. Rudolf Poller
// Version     : 1.0
// Copyright   : Learning
// Description : Draws the sides of a set of polygons
//               conceived as a finite element mesh
//============================================================================

#include <cstring>
#include <GL/glew.h>

#include "meshplot.h"
#include "Point.h"
#include "Polygon.h"

using namespace std;

typedef pair<NodeSet, ElemSet> FEMesh;

// Geometry definition of the X window
const int XWinOrigX  =	  50;
const int XWinOrigY  =	  60;
const int XWinWidth  =	1100;
const int XWinHeight =	 600;

// Number of DOFs
const GLsizei dofNum = 3;

string problem_title;
FEMesh mesh;

template<typename T>
inline T midval(T min, T max) {
	return 0.5 * (max + min);
}

template<typename T>
inline T halfdist(T dist) {
	return 0.5 * dist;
}

extern void ReadFEMesh(input_grammar, FEMesh&);

GLuint VBuffIds[1];
GLsizei nodePairNum;

int  InitGraphics(int, char**);
void PassNodePairs(void);
void CollectCoordinates(const ElemSet&, list<GLfloat>&);
void PlottingFEMesh(void);
void SetViewSystem(GLsizei, GLsizei);
void SetWinEqSides(reals4&);
void SetLookWin(reals4);
void KeyBoardHit(unsigned char, int, int);
void WriteStepTitle(const string&);

input_grammar getinpform(int, char**);

int main(int argc, char **argv)
{
	cout << "*** Plotting FE Mesh by openGL" << endl;
	ReadFEMesh(getinpform(argc, argv), mesh);
	if (!InitGraphics(argc, argv))
		return 1;
	glutMainLoop();
	return 0;
}

input_grammar getinpform(int argc, char **argv)
{
	char opt;
	input_grammar format = meshplot;

	while (--argc)
		if (argv[argc][0] == '-' && strlen(argv[argc]) == 2)
			switch (opt = argv[argc][1]) {
			case 'a':
				format = ansys;
				break;
			default:
				cerr << "invalid option: -" << opt << endl;
				exit(1);
				break;
			}

	return format;
}

int InitGraphics(int argc, char **argv)
{
	GLenum glew_check;

	WriteStepTitle("Displaying mesh");

	// Initialization of GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

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

    // Line attributes
	glColor3f(0, 0, 0); // black
    glLineWidth(1.0);

	// Feeding nodes that are to be connected
	PassNodePairs();

	// Registering the drawing procedure
	glutDisplayFunc(PlottingFEMesh);

	// Registering the reshape procedure
	glutReshapeFunc(SetViewSystem);

    glutKeyboardFunc(KeyBoardHit);

	return 1;
}

void PassNodePairs(void)
{
    const NodeSet& nodes = mesh.first;
    const ElemSet& elems = mesh.second;
    reals4 wlims;
    GLsizei coordNum, byteNum;
    GLfloat *coords;
    list<GLfloat> ConNDCoords;

    GetCoordExtremes(nodes, wlims);
    SetLookWin(wlims);
    CollectCoordinates(elems, ConNDCoords);
    coordNum = ConNDCoords.size();
    byteNum = coordNum * sizeof(GLfloat);
    nodePairNum = coordNum / dofNum;
    coords = new GLfloat[coordNum];
    copy(ConNDCoords.begin(), ConNDCoords.end(), coords);
    glGenBuffers(1, VBuffIds);
    glBindBuffer(GL_ARRAY_BUFFER, VBuffIds[0]);
    glBufferData(GL_ARRAY_BUFFER, byteNum, coords, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    delete[] coords;
}

void CollectCoordinates(const ElemSet& elems, list<GLfloat>& connCoords)
{
    for (const pair<serial, Polygon>& elem : elems)
        connCoords.splice(connCoords.end(), elem.second.LsConNDCoords());
}

void PlottingFEMesh(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, VBuffIds[0]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, dofNum, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINES, 0, nodePairNum);
    glDisableVertexAttribArray(0);
	glutSwapBuffers();
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

void SetLookWin(reals4 geodat)
{
	GLdouble xmin, xmax, ymin, ymax;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	SetWinEqSides(geodat);
	tie(xmin, xmax, ymin, ymax) = geodat;
	gluOrtho2D(xmin, xmax, ymin, ymax);
	glMatrixMode(GL_MODELVIEW);
}

#define ESCAPE_CHAR 27

void KeyBoardHit(unsigned char key, int x, int y)
{
    switch (key) {
    case ESCAPE_CHAR:
        glutLeaveMainLoop();
        cout << "Exit by ESC\n";
        return;
    }
}


void WriteStepTitle(const string& title)
{
	cout << ". " << title << "..." << endl;
}
