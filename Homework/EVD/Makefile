#CXX = clang++ -std=c++2a
CXX = g++ -std=c++23
CXXFLAGS = -Wall -O
LDLIBS += -lstdc++ -lm

Out.txt: main
	./main > Out.txt

main.o: matrix.h evd.h QR.h


clean:
	$(RM) main *.o