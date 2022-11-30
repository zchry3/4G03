OBJECTFILES=main.o MCsim.o
CXXFLAGS=-std=c++11

main: $(OBJECTFILES)
	c++ $(OBJECTFILES) -o $@

$(OBJECTFILES):
	c++ $*.cc $(CXXFLAGS) -c

main.o: main.cc MCvar.h MCsim.h

MCsim.o: MCsim.cc MCvar.h MCsim.h
