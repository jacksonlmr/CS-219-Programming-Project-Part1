simulator: main.o simulator.o
	g++ -g -o simulator main.o simulator.o

main.o: simulator.h main.cpp
	g++ -g -c main.cpp
	
simulator.o: simulator.h simulator.cpp
	g++ -g -c simulator.cpp

clean:
	rm *.o simulator