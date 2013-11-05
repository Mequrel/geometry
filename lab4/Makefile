all: lab4 classify

lab4: triangulation.o ../lib/core.o ../lib/print.o ../lib/parser.o
	g++ triangulation.o ../lib/core.o ../lib/print.o ../lib/parser.o -o lab4 -std=c++11

classify: classify.o ../lib/core.o ../lib/print.o ../lib/parser.o
	g++ classify.o ../lib/core.o ../lib/print.o ../lib/parser.o -o classify -std=c++11

triangulation.o: triangulation.cpp
	g++ -c triangulation.cpp -std=c++11

classify.o: classify.cpp
	g++ -c classify.cpp -std=c++11

clean:
	rm lab4
	rm *.o