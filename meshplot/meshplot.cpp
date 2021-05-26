//============================================================================
// Name        : meshplot.cpp
// Author      : Dr. Rudolf Poller
// Version     : 1.0
// Copyright   : Learning
// Description : Draws the sides of a set of polygons
//               conceived as a finite element mesh
//============================================================================

#include <cstring>
#include <filesystem>
#include <GL/glew.h>

#include "meshplot.h"
#include "Point.h"
#include "Polygon.h"

using namespace std;

typedef std::pair<NodeSet, ElemSet> FEMesh;

// Geometry definition of the initial X window
const int XWinOrigX  =	  50;
const int XWinOrigY  =	  60;
const int XWinWidth  =	1200;
const int XWinHeight =	 600;

string progFileName;
string problem_title;
GLuint ShaderId;
reals4 modelLims;
FEMesh mesh;

extern void setViewSystem(GLsizei, GLsizei);
extern void getModelView(void);
extern void saveModelView(void);
extern void resetView(void);
extern void maximizeView(void);
extern void readFEMesh(input_grammar, FEMesh&);
extern void mouseEvent(int, int, int, int);
extern void mouseKeptDown(int, int);
extern void getShader(GLuint*);

int   initGraphics(int, char**);
void  passNodePairs(void);
void  plotFEMesh(void);
void  keyBoardHit(unsigned char, int, int);
void  writeTitle(string);
void  writeStepTitle(const string&);
void  writeKeyFuncInfo(void);
void  writeMouseFuncInfo(void);

void errorHandle(const string&);
template void errorHandle(const string&, const string&);

input_grammar getInpForm(int, char**);

int main(int argc, char **argv)
{
    filesystem::path progPath(argv[0]);

    progFileName = progPath.filename();
    writeTitle("Plotting FE Mesh by openGL");
	readFEMesh(getInpForm(argc, argv), mesh);
	if (!initGraphics(argc, argv))
		return 1;
	glutMainLoop();
	return 0;
}

input_grammar getInpForm(int argc, char **argv)
{
	char opt;
	char *optArray;
	input_grammar format = meshplot;

	while (--argc) {
	    optArray = argv[argc];
        if (optArray[0] == '-' && strlen(optArray) == 2)
            switch (opt = optArray[1]) {
            case 'a':
                format = ansys;
                break;
            default:
                errorHandle("invalid option -", opt);
                break;
            }
	}
	return format;
}

int initGraphics(int argc, char **argv)
{
    const NodeSet& nodes = mesh.first;
    GLenum glew_check;

	writeStepTitle("Displaying mesh");

	// Initialization of GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Window
	glutInitWindowSize(XWinWidth, XWinHeight);
	glutInitWindowPosition(XWinOrigX, XWinOrigY);
	glutCreateWindow("FE Mesh");

	// Checking for openGL availability
	glew_check = glewInit();
	if (GLEW_OK != glew_check)
        errorHandle("GLEW Error:", *glewGetErrorString(glew_check));

    // Printing the version of the current openGL implementation
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

    // Printing the version of the current GLSL
    cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

	// Background color: white
	glClearColor(1.0, 1.0, 1.0, 0.0);

    // Line attributes
	glColor3f(0.0f, 0.0f, 0.0f); // black
    glLineWidth(1.0);

    // Storing the model-view matrix (which will be now the identity)
    getModelView();

    // Getting the boundaries of the FE mesh
    getCoordBounds(nodes, modelLims);

    // Saving the view, so that it can be recalled
    saveModelView();

	// Feeding nodes that are to be connected
	passNodePairs();

	// Creating shader program
	getShader(&ShaderId);

	// Registering callback procedures
	glutDisplayFunc(plotFEMesh);
	glutReshapeFunc(setViewSystem);
    glutKeyboardFunc(keyBoardHit);
    glutMouseFunc(mouseEvent);
    glutMotionFunc(mouseKeptDown);

    writeKeyFuncInfo();
    writeMouseFuncInfo();

	return 1;
}


enum class usedkey : unsigned char {
    ESCAPE = 27,
    KEY_M = 'm',
    KEY_O = 'o',
    KEY_R = 'r',
    KEY_Z = 'z'
};

void keyBoardHit(unsigned char key, int x, int y)
{
    switch (static_cast<usedkey>(key)) {
    case usedkey::ESCAPE:
        glutLeaveMainLoop();
        cout << "Exited by ESC\n";
        return;
    case usedkey::KEY_M:
        maximizeView();
        return;
    case usedkey::KEY_R:
        resetView();
        return;
    default:
        cout << "key " << key << " has no effect" << "\n";
        break;
    }
}


void errorHandle(const string& msg)
{
    cerr << progFileName << ": " << msg << endl;
    exit(1);
}

template <typename T>
void errorHandle(const string& msg, const T& spec)
{
    cerr << progFileName << ": " << msg << spec << endl;
    exit(1);
}


void writeTitle(string title)
{
    cout << "*** " << title << endl;
}

void writeStepTitle(const string& title)
{
	cout << ". " << title << "..." << endl;
}

void  writeKeyFuncInfo(void)
{
    cout << "\n- Keyboard functions:" << "\n";
    cout << "m    maximize view" << "\n";
    cout << "r    reset view" << "\n";
    cout << "ESC  exit" << endl;
}

void writeMouseFuncInfo(void)
{
    cout << "\n- Mouse functions:" << "\n";
    cout << "Left button   offset" << "\n";
    cout << "Scroll        zoom" << "\n";
    cout << "Right button  rotation" << "\n";
}
