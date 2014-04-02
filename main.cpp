//Spencer King, Lab 6 Part 1, main.cpp
#include <iostream>
#include <string>
#include <fstream>
#include "puzzle.h"
#include "puzzle.cpp"

using namespace std;

int main(int argc, char *argv[]){

	//check if provided input file
	if (argc==1 || argc>2){
		cout << "Usage: ./main [sudoku_file]" << endl;
		return 1;
	}
	puzzle<int> sudoku(argv[1]);

	
	sudoku.print(); //print the initial puzzle
	int x=2; //while loop true condition
	while (x!=1){
		sudoku.solve(); //tries to solve the puzzle
		x=sudoku.checkDone(); //returns 1 if the puzzle is solved
	}
	cout << endl;
	sudoku.print(); //print the solved puzzle

}
