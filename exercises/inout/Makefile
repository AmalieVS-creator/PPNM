#CXX = clang++ -std=c++2a
CXX = g++ -std=c++17
CXXFLAGS = -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm

all: command stdio filestream

command: command.o
	g++ command.o -o command
command.o: command.cc
	g++ -c command.cc -o command.o

stdio: stdio.o
	g++ stdio.o -o stdio
stdio.o: stdio.cc
	g++ -c stdio.cc -o stdio.o

filestream: filestream.o
	g++ filestream.o -o filestream
filestream.o: filestream.cc
	g++ -c filestream.cc -o filestream.o

clean:
	$(RM) command stdio filestream *.o

