CXX = g++
CXXFLAGS = -Wall -O -std=c++23
LDLIBS += -lstdc++ -lm

default : Out.txt linear.svg quadratic.svg

Out.txt linear.dat data.dat quadratic.dat : main
	./main > Out.txt

main : main.o LS.o
main.o: LS.h
LS.o : LS.h
linear.svg : linear.gpi linear.dat data.dat
	gnuplot $<
quadratic.svg : quadratic.gpi quadratic.dat
	gnuplot $<

clean:
	rm -f main *.o *.dat