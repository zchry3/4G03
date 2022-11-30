EX3: main.o bisection.o bessel.o
	c++ main.o bisection.o bessel.o -o EX3

main.o: main.cpp bisection.h ../EX2/bessel.h
	c++ -c main.cpp

bisection.o: bisection.cpp ../EX2/bessel.h bisection.h
	c++ -c bisection.cpp

bessel.o: ../EX2/bessel.cpp ../EX2/bessel.h
	c++ -c ../EX2/bessel.cpp
