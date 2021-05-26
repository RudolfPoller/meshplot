/*
 * motion.cpp
 *
 *  Created on: May 17th, 2021
 *      Author: Dr. R. Poller
 *
 *  Task
 *      Motions of the FE mesh
 *
 */

#include <iostream>

#include "meshplot.h"
#include "Point.h"
#include "Polygon.h"
#include "FreeVect.h"

extern GLdouble modelViewMatrix[GL_MATRIXDIM];
extern RealPoint mapWinToModel(const IntPoint);
extern RealPoint mapWinToPersp(const IntPoint);
extern void getModelView(void);

const RealPoint planeOrigin(0.0f, 0.0f);

int mouseButton;
bool firstCycle;
RealVector refRad;
RealPoint mouseRefPos;
RealPoint rotPoint;
RealPoint meshMidPoint;

void moveToPoint(const RealPoint);
void moveOffset(const RealVector offset);
void rotate(const RealPoint, const GLfloat);

void zoom(const RealPoint ref, const GLfloat factor)
{
    glMatrixMode(GL_MODELVIEW);
    moveOffset(ref - planeOrigin);
    glScalef(factor, factor, factor);
    moveOffset(planeOrigin - ref);
}

void rotate(const RealPoint pivot, const GLfloat angle)
{
    glMatrixMode(GL_MODELVIEW);
    moveOffset(pivot - planeOrigin);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    moveOffset(planeOrigin - pivot);
}

void moveOffset(const RealVector offset)
{
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(offset.getX(), offset.getY(), 0.0f);
}

void moveToPoint(const RealPoint dest)
{
    glMatrixMode(GL_MODELVIEW);
    moveOffset(dest - planeOrigin);
}


#define MOUSE_SCROLL_UP     0x0003
#define MOUSE_SCROLL_DOWN   0x0004

void mouseEvent(int button, int state, int x, int y)
{
    const float zoomInFact = float(1.01);
    const float zoomOutFact = float(1.0) / zoomInFact;
    const IntPoint winPoint(x, y);

    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            mouseButton = GLUT_LEFT_BUTTON;
            mouseRefPos = mapWinToModel(winPoint);
        }
        break;
    case GLUT_MIDDLE_BUTTON:
        mouseButton = GLUT_MIDDLE_BUTTON;
        getModelView();
        glutPostRedisplay();
        break;
    case MOUSE_SCROLL_UP:
        mouseRefPos = mapWinToModel(winPoint);
        zoom(mouseRefPos, zoomOutFact);
        getModelView();
        glutPostRedisplay();
        break;
    case MOUSE_SCROLL_DOWN:
        mouseRefPos = mapWinToModel(winPoint);
        zoom(mouseRefPos, zoomInFact);
        getModelView();
        glutPostRedisplay();
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN){
            mouseButton = GLUT_RIGHT_BUTTON;
            mouseRefPos = mapWinToPersp(winPoint);
            rotPoint = mapWinToModel(winPoint);
            firstCycle = true;
        }
        break;
    default:
        break;
    }
}


void mouseKeptDown(int x, int y)
{
    const IntPoint winPoint(x, y);
    RealPoint mouseCurrPos;
    RealVector currRad;

    switch (mouseButton) {
    case GLUT_LEFT_BUTTON:
        mouseCurrPos = mapWinToModel(winPoint);
        moveOffset(mouseCurrPos - mouseRefPos);
        getModelView();
        glutPostRedisplay();
        break;
    case GLUT_RIGHT_BUTTON:
        mouseCurrPos = mapWinToPersp(winPoint);
        if (firstCycle) {
            refRad = mouseCurrPos - mouseRefPos;
            firstCycle = false;
        }
        else {
            currRad = mouseCurrPos - mouseRefPos;
            rotate(rotPoint, rotAngleDeg(refRad, currRad));
            getModelView();
            glutPostRedisplay();
            refRad = currRad;
        }
        break;
    default:
        break;
    }
}


// Middle point of the mesh

void setMidPoint(reals4& wlims)
{
    RealPoint getMidPoint(reals4&);

    meshMidPoint = getMidPoint(wlims);
}


// Middle point of a rectangular region

RealPoint getMidPoint(reals4& wlims)
{
    GLdouble px, py;

    px = std::midpoint(get<coordlim_t::xmax>(wlims),
                       get<coordlim_t::xmin>(wlims));
    py = std::midpoint(get<coordlim_t::ymax>(wlims),
                       get<coordlim_t::ymin>(wlims));
    return RealPoint(px, py);
}
