CXX = g++
CXXFLAGS = -Wall -O -std=c++23
LDLIBS += -lstdc++ -lm

default: Out.txt timing.svg

Out.txt timing.dat: main
	./main > Out.txt

main : main.o QR.o root.o symcol.o
main.o : main.cc
symcol.o : symcol.h symcol.cc
QR.o : QR.h QR.cc
root.o : root.cc root.h


timing.svg : timing.gpi timing.dat 
	gnuplot $<

clean:
	rm -f main *.o *.dat
