all: gb-center-test

TRANSFINITE=/home/salvi/project/transfinite
INCLUDES=-I$(TRANSFINITE)/src/geom
CXXFLAGS=-g -Wall -std=c++17 $(INCLUDES)
LIBS=-L$(TRANSFINITE)/release/geom -lgeom

gb-center-test: gb-center-test.o gb-center.o c0-center.o
	g++ -o $@ $^ $(LIBS)
