/*
 * mapping.cpp
 *
 *  Created on: May 22nd, 2021
 *      Author: Dr. R. Poller
 *
 *  Task
 *      Collects maps between points
 *      - mapModelToWin: maps model space points to window points
 *      - mapWinToModel: maps window points to model space points
 *
 *  Remarks
 *   + The viewport and the window coordinate systems are distinct
 *   + The x coordinates are the same: they start at the left and
 *     proceed right
 *   + Viewport y coordinates start at the bottom and proceed upwards
 *   + Window y coordinates start at the top and proceed downwards
 */

#include "../meshplot.h"
#include "../mesh/Point.h"

GLint viewPortData[GL_VECTORDIM];
GLdouble projMatrix[GL_MATRIXDIM];
GLdouble modelViewMatrix[GL_MATRIXDIM];

const GLdouble identityMatrix[GL_MATRIXDIM] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
};

const GLint nullVector[GL_VECTORDIM] = { 0, 0, 0, 0 };

inline int windowHeight(void) {
    return viewPortData[viewport_index::height];
}

inline int mapVpToWinX(int x){
    return x;
}

inline int mapVpToWinY(int y){
    return windowHeight() - y;
}

inline int mapWinToVpX(int x){
    return x;
}

inline int mapWinToVpY(int y){
    return windowHeight() - y;
}


/*
 * Mapping model space points onto window points
 *   + gluProject() maps model points to viewport points
 */

IntPoint mapModelToWin(const RealPoint p)
{
    GLdouble wx, wy, wz;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelViewMatrix);
    gluProject(
            p.compX(), p.compY(), 0.0,
            modelViewMatrix, projMatrix, viewPortData,
            &wx, &wy, &wz
    );
    return IntPoint(mapVpToWinX(wx), mapVpToWinY(wy));
}


/*
 * Mapping window points onto model space points
 *   + Inverse mapping of mapModelToWin()
 *   + gluUnProject() maps viewport points to model points
 */

RealPoint mapWinToModel(const IntPoint wp)
{
    GLdouble objx, objy, objz;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelViewMatrix);
    gluUnProject(
            mapWinToVpX(wp.compX()), mapWinToVpY(wp.compY()), 0.0,
            modelViewMatrix, projMatrix, viewPortData,
            &objx, &objy, &objz
    );
    return RealPoint(objx, objy);
}


/*
 *  Mapping points of perspective plane onto window points
 *     + motions and scaling map onto the perspective plane
 */

IntPoint mapPerspToWin(RealPoint p)
{
    GLdouble vx, vy, vz;
    GLdouble wx, wy;

    gluProject(
            p.compX(), p.compY(), 0.0,
            identityMatrix, identityMatrix, viewPortData,
            &vx, &vy, &vz
    );
    wx = mapVpToWinX(vx);
    wy = mapVpToWinY(vy);
    return IntPoint(wx, wy);
}


/*
 * Mapping window points onto perspective plane
 *     + motions and scaling map onto the perspective plane
 */

RealPoint mapWinToPersp(IntPoint wp)
{
    GLdouble x, y, z;
    GLdouble vx, vy, vz;

    vx = mapWinToVpX(wp.compX());
    vy = mapWinToVpY(wp.compY());
    vz = 0.0;
    gluUnProject(
            vx, vy, vz,
            identityMatrix, identityMatrix, viewPortData,
            &x, &y, &z
    );
    return RealPoint(x, y);
}


/*
 * Mapping model points onto moved model points
 */

inline unsigned short indx(unsigned short i, unsigned short j){
    return i * GL_VECTORDIM + j % GL_VECTORDIM;
}

RealPoint mapModelToMoved(const RealPoint& mp)
{
    unsigned short i, j;
    GLdouble mpVec[GL_VECTORDIM], tmpVec[GL_VECTORDIM];
    using coo = cooindx_t;

    mpVec[coo::x] = mp.compX();
    mpVec[coo::y] = mp.compY();
    mpVec[coo::z] = mp.compZ();
    mpVec[coo::w] = 1.0;
    for (i = 0; i < GL_VECTORDIM; ++i){
        tmpVec[i] = 0.0;
        for (j = 0; j < GL_VECTORDIM; ++j)
            tmpVec[i] += modelViewMatrix[indx(j, i)] * mpVec[j];
    }
    return RealPoint(tmpVec[coo::x], tmpVec[coo::y], tmpVec[coo::z]);
}
