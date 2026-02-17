CXXFLAGS += -Wall -std=c++23 
LDLIBS += -lstdc++ -lm

all: erf.svg sgamma.svg lngamma.svg

erf.data: main Makefile
	./$< erf >$@

erf.svg: erf.gpi erf.data
	gnuplot $<

sgamma.data: main Makefile
	./$< sgamma >$@

sgamma.svg: sgamma.gpi sgamma.data
	gnuplot $<

lngamma.data: main Makefile
	./$< lngamma >$@

lngamma.svg: lngamma.gpi lngamma.data
	gnuplot $<

clean:
	$(RM) main 