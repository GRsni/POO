
CXX=clang++
STD=c++11
CXXFLAGS=-std=c++11 -ggdb -Wall -pedantic
CPPFLAGS=-DP0 -I../Tests-auto -I. 
VPATH=../Tests-auto:.

all: test-P0-auto test-P0-consola

test-P0-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o \
	test-auto.o cadena.o fecha.o
	$(CXX) -o $@ $(LDFLAGS) $^

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o:\
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp	

test-P0-consola: test-P0-consola.o fecha.o cadena.o
	$(CXX) -o $@ $(LDFLAGS) $^

test_P0-consola.o: fecha.hpp cadena.hpp

fecha.o: fecha.cpp fecha.hpp

cadena.o: cadena.cpp cadena.hpp

checks: fecha_check cadena_check fecha.cpp fecha.hpp cadena.cpp cadena.hpp

fecha_check:
	${MAKE} -f Make_check.mk $@

cadena_check:
	${MAKE} -f Make_check.mk $@

clean:
	$(RM) t *.o *.gch test_a core *~ test test-P0-consola test-P0-auto cadena_check fecha_check
