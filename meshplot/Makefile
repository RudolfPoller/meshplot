#
# Makefile of meshplot
#
#  Created on: Apr. 14th, 2021
#      Author: Dr. Rudolf Poller
#
#  Synopsis
#  	Reads in mesh using yacc/lex (more precisely, bison/flex)
#   and displays it
#
#  Remark
#	'make DEBUG=y target' generates code for debugging


LEX = 		flex
LFLAGS =	-L

YACC = 		bison
YFLAGS =	-d -l

CXXFLAGS =	-Wall -fmessage-length=0 -std=c++11

OBJS =		meshplot.o \
			Point.o Polygon.o \
			readmesh.o \
			meshparser.o meshscanner.o \
			ansparser.o ansscanner.o

LIBS =		-lGLEW -lGLUT -lGLU -lGL -lfl

TARGET =	meshplot.exe

ifeq ($(DEBUG), y)
	CXXFLAGS := -g $(CXXFLAGS)
else
	CXXFLAGS := -O2 $(CXXFLAGS)
endif

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)
	
meshplot.cpp: meshplot.h Point.h Polygon.h
	
Point.cpp: Point.h
	
Polygon.cpp: Polygon.h
	
readmesh.cpp: Point.h Polygon.h meshparser.tab.hpp ansparser.tab.hpp
	
meshparser.ypp meshscanner.l: meshplot.h parsescan.h

%.tab.cpp %.tab.hpp: %.ypp
	$(YACC) $(YFLAGS) $<
	
%.o: %.tab.o
	mv -f $< $@

%.c: %.l

%.cpp: %.l
	$(LEX) -t $(LFLAGS) $< > $@

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f meshparser.tab.{cpp,hpp} meshscanner.cpp
	rm -f ansparser.tab.{cpp,hpp} ansscanner.cpp
	