CXX = g++
CXXFLAGS = -Wall -O -std=c++23
LDLIBS += -lstdc++ -lm



default : Out.txt ann.svg partB.svg

Out.txt ann.dat partB.dat: main
	./main > Out.txt

main : main.o nn.o 
main.o : main.cc
nn.o : nn.h nn.cc


ann.svg : ann.gpi ann.dat 
	gnuplot $<

partB.svg : partB.gpi partB.dat 
	gnuplot $<

clean:
	rm -f main *.o *.dat
