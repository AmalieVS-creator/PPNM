#CXX = clang++ -std=c++2a
CXX = g++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm

Out.txt: main
	./main > Out.txt

main: main.o

main.o: main.cc vec.h

clean:
	$(RM) main *.o