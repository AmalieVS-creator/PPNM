CXX = g++
CXXFLAGS = -Wall -O -std=c++23
LDLIBS += -lstdc++ -lm



default : Out.txt Higgs.svg

# Out.txt fit.dat data.dat : main
# 	./main > Out.txt

Out.txt fit.dat : main data.dat
	./main < data.dat > Out.txt

# Out.txt fit.dat: main 
# 	./main < data.dat 1> Out.txt

main : main.o Mini.o QR.o
main.o : main.cc
Mini.o : Mini.h Mini.cc
QR.o : QR.cc QR.h

Higgs.svg : Higgs.gpi fit.dat data.dat
	gnuplot $<

clean:
	rm -f main *.o fit.dat 
