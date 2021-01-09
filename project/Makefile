
output: main.o graph.o cityMap.o crossRoad.o
	g++ main.o graph.o cityMap.o crossRoad.o -o output

main.o: cityMap.cpp cityMap.h
	g++ -c main.cpp

graph.o: graph.h graph.cpp
	g++ -c graph.cpp 

cityMap.o: cityMap.h cityMap.cpp
	g++ -c cityMap.cpp 

crossRoad.o: crossRoad.h crossRoad.cpp
	g++ -c crossRoad.cpp 

build_tests: tests.o graph.o
	g++ tests.o graph.o -o tests.exe

tests.o: tests.cpp
	g++ -c tests.cpp

clean:
	rm tests.o graph.o crossRoad.o cityMap.o main.o output

run_tests:
	./tests.exe