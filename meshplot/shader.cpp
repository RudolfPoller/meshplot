/*
 * shader.cpp
 *
 *  Created on: May 12th, 2021
 *      Author: Dr. R. Poller
 *
 *  Task
 *      Creates shader program
 *
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <list>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

#include "meshplot.h"

// For the sake of Eclipse CDT only.
// It is clearly a bug since the below lines
// are copied from glew.h which is included above.
#ifdef ECLIPSE_CDT_BUG
#define glCreateShader GLEW_GET_FUN(__glewCreateShader)
#define glShaderSource GLEW_GET_FUN(__glewShaderSource)
#define glCompileShader GLEW_GET_FUN(__glewCompileShader)
#define glGetShaderiv GLEW_GET_FUN(__glewGetShaderiv)
#define glCreateProgram GLEW_GET_FUN(__glewCreateProgram)
#define glAttachShader GLEW_GET_FUN(__glewAttachShader)
#define glLinkProgram GLEW_GET_FUN(__glewLinkProgram)
#define glGetProgramiv GLEW_GET_FUN(__glewGetProgramiv)
#define glDeleteShader GLEW_GET_FUN(__glewDeleteShader)
#define glGetShaderInfoLog GLEW_GET_FUN(__glewGetShaderInfoLog)
#define glGetProgramInfoLog GLEW_GET_FUN(__glewGetProgramInfoLog)
#endif

enum codsec { compile, link };

const string vertexFilename = "offset.vrx";

extern void errorHandle(const string&);
extern template void errorHandle(const string&, const string&);

void errorHandle(codsec, GLuint);

void getShader(GLuint *progId)
{
    GLint status;
    GLuint objId;
    GLuint compileShader(const string&);

    *progId = glCreateProgram();
    objId = compileShader(vertexFilename);
    glAttachShader(*progId, objId);
    glLinkProgram(*progId);
    glGetProgramiv(*progId, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
        errorHandle(link, *progId);
    glDeleteShader(objId);
}

GLuint compileShader(const string& fileName)
{
    GLuint shaderId;
    GLint lineno, status;
    GLchar **code;
    void getShaderStr(string, GLchar***, GLint*);

    shaderId = glCreateShader(GL_VERTEX_SHADER);
    getShaderStr(fileName, &code, &lineno);
    glShaderSource(shaderId, lineno, code, NULL);
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
        errorHandle(compile, shaderId);
    return shaderId;
}

void getShaderStr(string fileName, GLchar ***code, GLint *linenum)
{
    ifstream codeFile(fileName, ios_base::in);
    ostringstream codeLineStream;
    list<string> codeLines;

    if (!codeFile.is_open())
        errorHandle("could not open file", fileName);
    while (!codeFile.eof()) {
        string codeline;
        getline(codeFile, codeline);
        codeLines.push_back(codeline);
    }
    *code = new char*[*linenum = codeLines.size()];
    for (int i = 0; const string& codeline : codeLines) {
        (*code)[i] = new char[codeline.size()];
        strcpy((*code)[i++], codeline.c_str());
    }
}

void errorHandle(codsec comptype, GLuint compid)
{
    GLint logmsglg;
    GLchar *logmsg;
    string errmsg;
    void (*getinfo)(GLuint, GLenum, GLint*);
    void (*getlog)(GLuint, GLsizei, GLsizei*, GLchar*);

    getinfo = nullptr;
    getlog = nullptr;
    switch (comptype)
    {
    case compile:
        getinfo = glGetShaderiv;
        getlog = glGetShaderInfoLog;
        errmsg = "compilation of shader failed";
        break;
    case link:
        getinfo = glGetProgramiv;
        getlog = glGetProgramInfoLog;
        errmsg = "link of program failed";
        break;
    default:
        break;
    }
    getinfo(compid, GL_INFO_LOG_LENGTH, &logmsglg);
    logmsg = new char[logmsglg];
    getlog(compid, logmsglg, NULL, logmsg);
    cerr << logmsg;
    errorHandle(errmsg);
}
