all:	main

main: main.o puzzle.o 
	g++ main.o puzzle.o -o main

main.o: main.cpp
	g++ -c main.cpp
puzzle.o:  puzzle.cpp
	g++ -c puzzle.cpp
clean:
	rm -f *.o main
