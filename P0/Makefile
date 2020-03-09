all: test_fecha

CXX=g++
CXXFLAGS=-std=c++11

test_fecha: test_fecha.o fecha.o
	$(CXX) $(CXXFLAGS) -o test_fecha test_fecha.o fecha.o

test_fecha.o: test_fecha.cpp
	$(CXX) $(CXXFLAGS) -c test_fecha.cpp

fecha.hpp.gch: fecha.hpp
	$(CXX) $(CXXFLAGS) -c fecha.hpp

clean:
	rm -f test_fecha test_fecha.o  fecha.o fecha.hpp.gch core *~
