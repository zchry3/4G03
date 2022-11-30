OBJECTFILES=diag.o main.o
CXXFLAGS=-std=c++11

main: $(OBJECTFILES)
	c++ $(OBJECTFILES) -o $@

$(OBJECTFILES):
	c++ $*.cc $(CXXFLAGS) -c

diag.o: diag.cc diag.h

main.o: main.cc diag.h
