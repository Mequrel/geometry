all: lab4

lab4: triangulation.o ../algorithms/triangulation.o ../lib/core.o ../lib/print.o ../lib/parser.o
	g++ triangulation.o ../algorithms/triangulation.o ../lib/core.o ../lib/print.o ../lib/parser.o -o lab4

intersections.o: triangulation.cpp
	g++ -c triangulation.cpp -I..

clean:
	rm lab4
	rm *.o