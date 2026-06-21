CXX = g++
CXXFLAGS = -Wall -O -std=c++23
LDLIBS += -lstdc++ -lm

default : Out.txt Error.svg 

Out.txt Error.dat ErrorB.dat: main
	./main > Out.txt

main : main.o Mon.o
main.o: Mon.h main.cc
Mon.o : Mon.h Mon.cc
Error.svg : Error.gpi Error.dat ErrorB.dat
	gnuplot $<

clean:
	rm -f main *.o *.dat