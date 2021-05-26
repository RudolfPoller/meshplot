/*
 * plot.cpp
 *
 *  Created on: May 12th, 2021
 *      Author: Dr. R. Poller
 *
 *  Task
 *      Setting the view
 *
 */

#include "meshplot.h"
#include "Point.h"
#include "Polygon.h"

using namespace std;

typedef std::pair<NodeSet, ElemSet> FEMesh;

extern reals4 modelLims;
extern GLint viewPortData[GL_VECTORDIM];
extern GLdouble projMatrix[GL_MATRIXDIM];

const extern FEMesh mesh;
const NodeSet& nodes = mesh.first;

void getViewSize(int&, int&);


/*
 *  Reshape callback
 */

void setViewSystem(GLsizei width, GLsizei height)
{
    void setLookWin(const reals4, const float);

    setLookWin(modelLims, sideRatio(width, height));
    glViewport(0, 0, width, height);
    glGetIntegerv(GL_VIEWPORT, viewPortData);
}


/*
 * Creation of the window through which
 * the FE mesh will be viewed
 *
 * Sets the shader matrix gl_ProjectionView
 *
 */

void setLookWin(const reals4 wlims, const float ratio)
{
    GLdouble xmin, xmax, ymin, ymax;
    reals4 geodat(wlims);
    void setWindowSides(reals4&, const float);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setWindowSides(geodat, ratio);
    tie(xmin, xmax, ymin, ymax) = geodat;
    gluOrtho2D(xmin, xmax, ymin, ymax);
    glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
}


/*
 * The FE mesh will be viewed through a window
 * of equal sides
 */

void setWindowSides(reals4& geodat, const float ratio)
{
    GLdouble xmin, xmax, ymin, ymax;
    GLdouble sidex, sidey, rsidey;
    void lims(const GLdouble, GLdouble&, GLdouble&);
    void marglims(GLdouble&, GLdouble&);

    tie(xmin, xmax, ymin, ymax) = geodat;
    marglims(xmin, xmax); marglims(ymin, ymax);
    sidex = xmax - xmin; sidey = ymax - ymin;
    rsidey = sidex * ratio;
    if (rsidey < sidey)
        sidex = sidey / ratio;
    else
        sidey = rsidey;
    lims(sidex, xmin, xmax); lims(sidey, ymin, ymax);
    geodat = reals4(xmin, xmax, ymin, ymax);
}

void marglims(GLdouble& min, GLdouble& max)
{
    const GLdouble stripRatio = 0.1;
    GLdouble length, strip;

    length  = max - min;
    strip = length * stripRatio;
    min -= strip; max += strip;
}

void lims(const GLdouble lg, GLdouble& min, GLdouble& max)
{
    GLdouble offs, orig;

    offs = halfdist(lg);
    orig = midpoint(min, max);
    min = orig - offs;
    max = orig + offs;
}


void getModelView(void)
{
    extern GLdouble modelViewMatrix[GL_MATRIXDIM];

    glGetDoublev(GL_MODELVIEW_MATRIX, modelViewMatrix);
}

static reals4 modelLimsStore;
static GLdouble modelviewMatrixStore[GL_MATRIXDIM];

void saveModelView(void)
{
    glGetDoublev(GL_MODELVIEW_MATRIX, modelviewMatrixStore);
    modelLimsStore = modelLims;
}

void resetModelView(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(modelviewMatrixStore);
    modelLims = modelLimsStore;
    getModelView();
}

void resetView(void)
{
    int width, height;
    void resetModelView(void);

    resetModelView();
    getViewSize(width, height);
    setLookWin(modelLims, sideRatio(width, height));
    glutPostRedisplay();
}

void maximizeView(void)
{
    int width, height;

    getViewSize(width, height);
    getCoordBounds(nodes, modelLims);
    setLookWin(modelLims, sideRatio(width, height));
    glutPostRedisplay();
}

void getViewSize(int& w, int& h)
{
    glGetIntegerv(GL_VIEWPORT, viewPortData);
    w = viewPortData[viewport_index::width];
    h = viewPortData[viewport_index::height];
}
