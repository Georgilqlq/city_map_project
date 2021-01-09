
output: main.o graph.o city_map.o CrossRoad.o
	g++ main.o graph.o city_map.o CrossRoad.o -o output

main.o: city_map.cpp city_map.h
	g++ -c main.cpp

graph.o: graph.h graph.cpp
	g++ -c graph.cpp 

city_map.o: city_map.h city_map.cpp
	g++ -c city_map.cpp 

CrossRoad.o: CrossRoad.h CrossRoad.cpp
	g++ -c CrossRoad.cpp 

build_tests: tests.o graph.o
	g++ tests.o graph.o -o tests.exe

tests.o: tests.cpp
	g++ -c tests.cpp

clean:
	rm tests.o graph.o CrossRoad.o city_map.o main.o output

run_tests:
	./tests.exe