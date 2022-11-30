OBJECTFILES=hv.o ../EX1/diag.o Lan.o main.o
CXXFLAGS=-std=c++11

main: $(OBJECTFILES)
	c++ $(OBJECTFILES) -o $@

$(OBJECTFILES):
	c++ $*.cc $(CXXFLAGS) -c

hv.o: hv.cc hv.h

Lan.o: Lan.cc Lan.h hv.h

main.o: main.cc hv.h ../EX1/diag.h Lan.h
