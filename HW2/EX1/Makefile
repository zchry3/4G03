OBJECTFILES=monte_carlo.o main.o
CXXFLAGS=-std=c++11

main: $(OBJECTFILES)
	c++ $(OBJECTFILES) -o $@

$(OBJECTFILES):
	c++ $*.cc $(CXXFLAGS) -c

monte_carlo.o: monte_carlo.cc monte_carlo.h

main.o: main.cc monte_carlo.h
