#CXX = clang++ -std=c++2a
CXX = g++ -std=c++17
CXXFLAGS = -Wall -Wextra -Werror -O
LDLIBS += -lstdc++ -lm 

Out.txt: main
	./main > Out.txt	

main: main.o calc.o sfuns.o 
main.o: calc.h main.cc sfuns.cc 
calc.o: calc.h calc.cc
sfuns.o: sfuns.h sfuns.cc


clean:
	$(RM) main main,o Out,txt *.o
