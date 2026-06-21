CXX = g++ 
CXXFLAGS = -Wall -O -std=c++23
LDLIBS += -lstdc++ -lm


default : Out.txt pendulum.svg planet.svg

Out.txt pendulum.dat planet1.dat planet2.dat planet3.dat: main
	./main > Out.txt

main : main.o RKE.o 
main.o: RKE.h matrix.h
RKE.o : RKE.h RKE.cc

pendulum.svg : pendulum.gpi pendulum.dat 
	gnuplot $<

planet.svg : planet.gpi planet1.dat planet2.dat planet3.dat
	gnuplot $<

# planet2.svg : planet2.gpi planet2.dat 
# 	gnuplot $<

# planet3.svg : planet3.gpi planet3.dat 
# 	gnuplot $<

clean:
	rm -f main *.o *.dat