CXX = g++
CXXFLAGS = -Wall -O -std=c++23
LDLIBS += -lstdc++ -lm



default : Out.txt wave.svg

Out.txt wave.dat: main
	./main > Out.txt

main : main.o root.o QR.o RKE.o
main.o : main.cc
root.o : root.h root.cc
QR.o : QR.cc QR.h
RKE.o: RKE.cc RKE.h

wave.svg : wave.gpi wave.dat 
	gnuplot $<

clean:
	rm -f main *.o *.dat
