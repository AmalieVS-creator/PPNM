CXX = g++
CXXFLAGS = -Wall -O -std=c++23
LDLIBS += -lstdc++ -lm



Out.txt: main
	./main > Out.txt

main : main.o QR.o root.o
main.o : main.cc
#symcol.o : symcol.h symcol.cc
QR.o : QR.h QR.cc
root.o : root.cc root.h
# main: main.o root.o QR.o
# main.o: main.cc
# QR.o: QR.cc QR.h
# root.o: root.cc root.h

clean:
	rm -f main *.o *.dat
