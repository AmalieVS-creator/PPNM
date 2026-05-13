CXX = g++
CXXFLAGS = -Wall -O -std=c++23
LDLIBS += -lstdc++ -lm

default : Out.txt decay.svg

Out.txt decay.dat data.dat : main
	./main > Out.txt

main : main.o QR.o
main.o: A.h matrix.h
QR.o : QR.h
decay.svg : decay.gpi decay.dat data.dat
	gnuplot $<

clean:
	rm -f main *.o *.dat
