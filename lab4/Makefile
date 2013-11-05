all: lab4 classify

lab4: triangulation.o ../lib/core.o ../lib/print.o ../lib/parser.o
	g++ triangulation.o ../lib/core.o ../lib/print.o ../lib/parser.o -o lab4

classify: classify.o ../lib/core.o ../lib/print.o ../lib/parser.o
	g++ classify.o ../lib/core.o ../lib/print.o ../lib/parser.o -o classify

triangulation.o: triangulation.cpp
	g++ -c triangulation.cpp

classify.o: classify.cpp
	g++ -c classify.cpp

clean:
	rm lab4
	rm *.o