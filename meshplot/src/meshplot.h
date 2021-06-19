/*
 * meshplot.h
 *
 *  Created on: Apr. 7th, 2021
 *      Author: Dr. R. Poller
 *
 *  Task
 *  	General definitions
 *
 */

#ifndef MESHPLOT_H_
#define MESHPLOT_H_

#include <iostream>
#include <iomanip>
#include <list>
#include <map>
#include <cmath>
#include <numeric>
#include <numbers>

#include <GL/freeglut.h>

#define GL_VECTORDIM     4
#define GL_MATRIXDIM    16

#define LABEL_FIELDWIDTH   5
#define COORD_FIELDWIDTH  15

typedef unsigned serial;
typedef std::tuple<GLdouble, GLdouble, GLdouble, GLdouble> reals4;

enum input_grammar { meshplot, ansys };
enum cooindx_t : size_t { x = 0, y = 1, z = 2, w = 3 };
enum coordlim_t : size_t { xmin = 0, xmax = 1, ymin = 2, ymax = 3 };
enum viewport_index : size_t { origx = 0, origy = 1, width = 2, height = 3 };

template <typename T>
void errorHandle(const std::string&, const T&);

template<typename T>
inline T halfdist(T dist) {
    return dist / T(2);
}

inline float sideRatio(int width, int height) {
    return static_cast<float>(height) / static_cast<float>(width);
}

// Eligible types for vector operations
template<typename> constexpr bool eligible() { return false; }
template<> constexpr bool eligible<int>() { return true; }
template<> constexpr bool eligible<GLfloat>() { return true; }
template<> constexpr bool eligible<GLdouble>() { return true; }

#endif /* MESHPLOT_H_ */
