all: test_fecha

CXX=g++
CXXFLAGS=-std=c++11 -ggdb -Wall

tests: tests.o fecha.o cadena.o
	$(CXX) $(CXXFLAGS) -o tests tests.o fecha.o cadena.o

tests_w: tests.o fecha.o cadena.o
	$(CXX) $(CXXFLAGS) -o tests.exe tests.o fecha.o cadena.o

tests.o: tests.cpp
	$(CXX) $(CXXFLAGS) -c tests.cpp

fecha.o: fecha.cpp fecha.hpp
	$(CXX) $(CXXFLAGS) -c fecha.cpp fecha.hpp

cadena.o: cadena.cpp cadena.hpp
	$(CXX) $(CXXFLAGS) -c cadena.cpp cadena.hpp

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
	rm -f tests tests.o fecha.hpp.gch fecha.o cadena.o cadena.hpp.gch core *~

clean_w:
	del tests.exe tests.o fecha.hpp.gch fecha.o  cadena.hpp.gch cadena.o core
