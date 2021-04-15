#
# Makefile of meshplot
#
#  Created on: Apr. 14th, 2021
#      Author: Dr. R. Poller
#
#  Synopsis
#  	Reads in mesh data
#


LEX = 		flex
LFLAGS =	-L

YACC = 		bison
YFLAGS =	-d -l

CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -std=c++11

OBJS =		meshplot.o Point.o Polygon.o readmesh.o meshparser.o meshscanner.o

LIBS =		-lglut -lglu -lgl -lfl

TARGET =	meshplot.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)
	
meshplot.cpp: meshplot.h Point.h Polygon.h
	touch $@
	
Point.cpp: Point.h
	touch $@
	
Polygon.cpp: Polygon.h
	touch $@
	
readmesh.cpp: Point.h Polygon.h meshparser.tab.hpp
	touch $@
	
meshparser.ypp meshscanner.l: parsescan.h
	touch $@

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
	rm -f meshparser.tab.{cpp,hpp} stack.hh
	rm -f meshscanner.cpp
	