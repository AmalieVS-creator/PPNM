# #CXX = clang++ -std=c++2a
# CXX = g++ -std=c++23
# CXXFLAGS = -Wall -O
# LDLIBS += -lstdc++ -lm

# default : Out.txt groundstate.svg dr_convergence.svg

# Out.txt groundstate.dat dr_convergence.dat: main
# 	./main > Out.txt

# main.o: matrix.h evd.h QR.h

# groundstate.svg : groundstate.gpi groundstate.dat
# 	gnuplot $<

# dr_convergence.svg : dr_convergence.gpi dr_convergence.dat
# gnuplot $<


# clean:
# 	$(RM) main *.o

CXX = g++
CXXFLAGS = -Wall -O -std=c++23

default: Out.txt groundstate.svg dr_convergence.svg rmax_convergence.svg wavefunctions.svg

# ---- build executable ----
main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o

main.o: main.cc matrix.h evd.h QR.h
	$(CXX) $(CXXFLAGS) -c main.cc

# ---- run program ----
Out.txt groundstate.dat dr_convergence.dat rmax_convergence wavefunctions.svg: main
	./main > Out.txt

# ---- plots ----
groundstate.svg: groundstate.gpi groundstate.dat
	gnuplot groundstate.gpi

dr_convergence.svg: dr_convergence.gpi dr_convergence.dat
	gnuplot dr_convergence.gpi

rmax_convergence.svg: rmax_convergence.gpi rmax_convergence.dat
	gnuplot rmax_convergence.gpi

wavefunctions.svg: wavefunctions.gpi wavefunctions.dat
	gnuplot wavefunctions.gpi

clean:
	rm -f main *.o *.dat