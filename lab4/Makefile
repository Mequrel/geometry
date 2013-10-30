all: lab4

lab4: triangulation.o ../lib/core.o ../lib/print.o ../lib/parser.o
	g++ triangulation.o ../lib/core.o ../lib/print.o ../lib/parser.o -o lab4

triangulation.o: triangulation.cpp
	g++ -c triangulation.cpp

clean:
	rm lab4
	rm *.o