CXX = g++
CXXFLAGS = -Wall -O -std=c++23
LDLIBS += -lstdc++ -lm

default : Out.txt erf_curve.svg erf_error_acc.svg

Out.txt erf_curve.dat erf_error_acc.dat: main
	./main > Out.txt

main: main.o rec.o
main.o: main.cc
rec.o: rec.cc rec.h

erf_curve.svg : erf_curve.gpi erf_curve.dat
	gnuplot $<
erf_error_acc.svg : erf_error_acc.gpi erf_error_acc.dat
	gnuplot $<

clean:
	rm -f main *.o *.dat 