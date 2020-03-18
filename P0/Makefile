all: test_fecha

CXX=g++
CXXFLAGS=-std=c++11 -ggdb

test_fecha: test_fecha.o fecha.o
	$(CXX) $(CXXFLAGS) -o test_fecha test_fecha.o fecha.o

test_fecha_w: test_fecha.o fecha.o
	$(CXX) $(CXXFLAGS) -o test_fecha.exe test_fecha.o fecha.o

test_fecha.o: test_fecha.cpp
	$(CXX) $(CXXFLAGS) -c test_fecha.cpp

fecha.o: fecha.cpp fecha.hpp
	$(CXX) $(CXXFLAGS) -c fecha.cpp fecha.hpp

checks: fecha_check cadena_check

fecha_check:
	${MAKE} -f Make_check.mk $@

cadena_check:
	${MAKE} -f Make_check.mk $@

check_Fecha:
	${MAKE} -f Make_check.mk $@

check_Cadena:
	${MAKE} -f Make_check.mk $@

clean:
	rm -f test_fecha test_fecha.o fecha.hpp.gch fecha.o core *~

clean_w:
	del test_fecha.exe test_fecha.o fecha.hpp.gch fecha.o core
