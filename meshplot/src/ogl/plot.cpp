/*
 * plot.cpp
 *
 *  Created on: May 12th, 2021
 *      Author: Dr. R. Poller
 *
 *  Task
 *      Plotting
 *
 */

#include <GL/glew.h>

#include "../meshplot.h"
#include "../mesh/Point.h"
#include "../mesh/Polygon.h"

// For the sake of Eclipse CDT only.
// It is clearly a bug since the below lines
// are copied from glew.h which is included above.
#ifdef ECLIPSE_CDT_BUG
#define glGenBuffers GLEW_GET_FUN(__glewGenBuffers)
#define glBindBuffer GLEW_GET_FUN(__glewBindBuffer)
#define glBufferData GLEW_GET_FUN(__glewBufferData)
#define glEnableVertexAttribArray GLEW_GET_FUN(__glewEnableVertexAttribArray)
#define glVertexAttribPointer GLEW_GET_FUN(__glewVertexAttribPointer)
#define glDisableVertexAttribArray GLEW_GET_FUN(__glewDisableVertexAttribArray)
#define glUseProgram GLEW_GET_FUN(__glewUseProgram)
#endif


// Number of DOFs
const GLsizei dofNum = 3;

typedef std::pair<NodeSet, ElemSet> FEMesh;

extern GLuint ShaderId;
extern FEMesh mesh;

GLsizei nodePairNum;
GLuint vertexBuffId;


/*
 *  Display callback
 */

void plotFEMesh(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffId);
    glUseProgram(ShaderId);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, dofNum, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINES, 0, nodePairNum);
    glDisableVertexAttribArray(0);
    glUseProgram(0);
    glutSwapBuffers();
}


// Passing node coordinates to the vertex buffer object

void passNodePairs(void)
{
    const ElemSet& elems = mesh.second;
    GLsizei coordNum, byteNum;
    GLfloat *coords;
    std::list<GLfloat> ConNDCoords;
    void collCoos(const GLenum, const ElemSet&, std::list<GLfloat>&);

    collCoos(GL_LINES, elems, ConNDCoords);
    coordNum = ConNDCoords.size();
    byteNum = coordNum * sizeof(GLfloat);
    nodePairNum = coordNum / dofNum;
    coords = new GLfloat[coordNum];
    std::move(ConNDCoords.begin(), ConNDCoords.end(), coords);
    glGenBuffers(1, &vertexBuffId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffId);
    glBufferData(GL_ARRAY_BUFFER, byteNum, coords, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    delete[] coords;
}


// Collecting node coordinates as input for openGL vertex buffer object

void collCoos(GLenum mode, const ElemSet& elems, std::list<GLfloat>& coos)
{

    switch(mode) {
    case GL_LINES:
        for (const std::pair<serial, Polygon>& elem : elems)
            coos.splice(coos.end(), elem.second.listConnCoos());
        break;
    case GL_LINE_STRIP:
        for (const std::pair<serial, Polygon>& elem : elems)
            coos.splice(coos.end(), elem.second.listNodeCoos());
        break;
    default:
        break;
    }
}


