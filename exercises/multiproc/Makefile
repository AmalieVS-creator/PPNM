CXXFLAGS = -std=c++23 -Wall -O2 -march=native
LDLIBS = -lstdc++ -lm -lpthread

TIME = /usr/bin/time -f "%e %U" -a -o out.times

default: Out.gnuplot.png

N = 1000000000

out.times: main
	> out.times
	for nthreads in 1 2 3 4 5 6 7 8; do \
		echo "Running $$nthreads threads"; \
		T=$$(/usr/bin/time -p ./main -nthreads $$nthreads -nterms $(N) 2>&1 | awk '/^real/ {print $$2}'); \
		echo "$$nthreads $$T" >> out.times; \
	done

Out.gnuplot.png: out.times
	echo '\
	set terminal png background "white";\
	set output "$@";\
	set tics out;\
	set title "Program running time as function of number of threads";\
	set xlabel "number of threads";\
	set ylabel "real time in seconds";\
	set xtics 1;\
	plot "$<" using 1:2 with linespoints title "c++";\
	' | gnuplot

clean:
	$(RM) main out.times log.main Out*.png