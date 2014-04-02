//Spencer King, Lab 6 Part 1,  puzzle.h
#ifndef PUZZLE_H
#define PUZZLE_H
#include <iostream>
#include <vector>
#include <string>

using namespace std;
//define the 2d and 3d vectors
typedef vector<int> intVector;
typedef vector<intVector> twoDimVector;
typedef vector<vector<intVector> > threeDVector;

template <typename T>
class puzzle{

	public:
	puzzle(); //default constructor
	puzzle(string); //non-default constructor
	void print(); //prints the puzzle
	void check(int, int); //makes sure move is valid
	void userInput(); //gets user input
	void playAgain(); //determine if continue playing
	void solve(); //solves the puzzle
	int checkDone(); //checks if the puzzle is solved

	private:
	twoDimVector SudokuBoard; //2d vector for the board
	threeDVector testBoard; //3d vector
	int numLines; //variable for determining board size



};

#endif
