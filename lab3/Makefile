all: lab3

lab3: intersections.o ../algorithms/brutal_intersections.o ../algorithms/shamos_hoey.o ../lib/core.o ../lib/print.o ../lib/parser.o
	g++ intersections.o ../algorithms/brutal_intersections.o ../algorithms/shamos_hoey.o ../lib/core.o ../lib/print.o ../lib/parser.o -o lab3

intersections.o: intersections.cpp
	g++ -c intersections.cpp -I..