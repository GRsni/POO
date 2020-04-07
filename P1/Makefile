
CXX=clang++
STD=c++11
CXXFLAGS=-std=c++11 -ggdb -Wall -pedantic
CPPFLAGS=-DP1 -I../Tests-auto -I. 
VPATH=../Tests-auto:.

all: test-P1-auto test-P1-consola

test-P1-auto: test-caso1-fecha-auto.o test-caso0-cadena-auto.o \
	test-auto.o cadena.o fecha.o
	$(CXX) -o $@ $(LDFLAGS) $^

test-caso1-fecha-auto.o test-caso1-cadena-auto.o test-auto.o:\
	test-caso1-fecha-auto.cpp test-caso1-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp	

test-P1-consola: test-P1-consola.o fecha.o cadena.o
	$(CXX) -o $@ $(LDFLAGS) $^

test_P1-consola.o: fecha.hpp cadena.hpp

fecha.o: fecha.cpp fecha.hpp

cadena.o: cadena.cpp cadena.hpp

checks: fecha_check cadena_check fecha.cpp fecha.hpp cadena.cpp cadena.hpp

fecha_check:
	${MAKE} -f Make_check.mk $@

cadena_check:
	${MAKE} -f Make_check.mk $@

clean:
	$(RM) t *.o *.gch core *~ test-P1-consola test-P1-auto cadena_check fecha_check
