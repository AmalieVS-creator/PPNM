#CXX = clang++ -std=c++2a
CXX = g++ -std=c++17
CXXFLAGS = -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm

Out.txt: main
	./main > Out.txt

main: main.o machine.o addition.o doubles.o
main.o: main.cc machine.cc addition.cc doubles.cc
machine.o: machine.cc machine.h 
addition.o: addition.cc addition.h
doubles.o: doubles.cc doubles.h

clean:
	$(RM) main main,o Out,txt *.o
