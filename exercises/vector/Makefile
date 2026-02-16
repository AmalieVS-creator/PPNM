#CXX = clang++ -std=c++2a
CXX = g++ -std=c++17
CXXFLAGS = -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm

Out.txt: main
	./main > Out.txt

main: main.o vec.o
main.o: main.cc vec.cc
vec.o: vec.cc vec.h

clean:
	$(RM) main main,o Out,txt *.o
