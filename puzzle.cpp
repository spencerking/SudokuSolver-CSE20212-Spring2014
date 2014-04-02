//Spencer King, Lab 6 Part 1, puzzle.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "puzzle.h"
#include <cstdlib>
#include <math.h>
#include <stdio.h>
using namespace std;


//default constructor
template <typename T>
puzzle<T>::puzzle(){
	
}

//non-default constructor
template <typename T>
puzzle<T>::puzzle(string filename){

	numLines=9;
	//open the file for reading
	ifstream dataFile1;
	dataFile1.open(filename.c_str());


	//adjust the board size
	SudokuBoard.resize(numLines);
	testBoard.resize(numLines);	

	int tmpInt;
	for (int i=0; i<numLines; ++i){
		for (int j=0; j<numLines; ++j){
			if (!(dataFile1 >> tmpInt)){ //determine if file can be read
				cout << "There was a problem reading the file." <<endl;
				exit(1);
			}
			//fill the board with values
			if (tmpInt==0 || (tmpInt>0 && tmpInt<=9)){
				SudokuBoard[i].push_back(tmpInt);
			}
		}
	}
	//initialize the 3d vector with values 1 through 9 in every position
	for (int i=0; i<numLines; i++){
		testBoard.push_back(vector<intVector>());
		for (int j=0; j<numLines; j++){
			testBoard[i].push_back(intVector());
			for (int k=1; k<numLines+1; k++){
				testBoard[i][j].push_back(k);
			}
		}
	}

}

template <typename T>
//prints the current puzzle
void puzzle<T>::print(){
	for (int i=0; i<numLines; i++){
		for (int j=0; j<numLines; j++){
			if (SudokuBoard[i][j]==0){ //replace 0s with blanks
				cout << "  ";
			}
			else{ //print the number followed by a space
				cout << SudokuBoard[i][j] << " ";
			}

		}
		cout << endl;

	}

}

template <typename T>
void puzzle<T>::userInput(){

	int xcoord;
	int ycoord;
	int number;

	//get user input for adding a number
	cout<<"The board starts at (0,0) and goes to either (4,4) or (8,8)."<<endl;
	cout<<"Please enter an x position: "<<endl;
	cin >> ycoord;
	cout<<"Please enter an y position: "<<endl;
	cin >> xcoord;
	cout<<"Please enter a number: "<<endl;
	cin >> number;
	cout<<endl;

	check(xcoord, ycoord, number);

}

template <typename T>
void puzzle<T>::check(int xcoord, int ycoord){
	int x = xcoord;
	int y = ycoord;
	//makes sure the space is blank
	if (SudokuBoard[xcoord][ycoord]!=0){
		for (int z=0; z < numLines; z++){
			testBoard[xcoord][ycoord][z]=0;
		}
	}
	//the first two for loops check rows and columns
	//puts a 0 in the 3d vector is the value is not possible
	for (x=0; x<numLines; x++){
		for (int z=0; z < numLines; z++){
			if (SudokuBoard[x][ycoord] == testBoard[xcoord][ycoord][z]){
				testBoard[xcoord][ycoord][z]=0;
			}
		}

	}
	
	for (y=0; y<numLines; y++){
		for (int z=0; z < numLines; z++){
			if (SudokuBoard[xcoord][y] == testBoard[xcoord][ycoord][z]){
				testBoard[xcoord][ycoord][z]=0;
			}
		}

	}
	
	x=xcoord;
	y=ycoord;	
	int sqrSize = sqrt(numLines);
	int rSqr= xcoord/sqrSize;
	int cSqr= ycoord/sqrSize;
	//check the mini grid
	//puts a 0 in the 3d vector if the value is not possible
	for (int i=sqrSize*rSqr; i<sqrSize*rSqr + sqrSize; i++){
		for (int j=sqrSize*cSqr; j<sqrSize*cSqr + sqrSize; j++){
			for (int z=0; z < numLines; z++){
			if (SudokuBoard[i][j] == testBoard[xcoord][ycoord][z]){
				testBoard[xcoord][ycoord][z]=0;
			}
			}

		}

	}
	
}


template <typename T>
//find out if the user would like to continue playing
void puzzle<T>::playAgain(){

	string userAnswer;
	cout<<endl;
	cout<<"Would you like to make another move?"<<endl;
	cin >> userAnswer;
	if (userAnswer == "yes"){
		userInput();
	}

}

template <typename T>
//solves the puzzle
void puzzle<T>::solve(){
//run through the entire board and call the check function
for (int i=0; i<numLines; i++){
	for (int j=0; j<numLines; j++){
		check(i, j);		
	}
}

		

//cout<<"solve1"<<endl;
int counter=0;
int a;
int b;
int i;
int j;
int k;
int l;
int z;
//checks for single values
for (i=0; i<numLines; i++){ //run through dim1 of testBoard
	for (j=0; j<numLines; j++){ //run through dim2 of testBoard
		counter=0;
		for (z=0; z<numLines; z++){ //run through dim3
			if (testBoard[i][j][z]!=0){ //checks if there is a possible number
				counter++;
				a=z+1;
			}
		}	
		if (counter==1){ //if there is only one possible number, add it to the board
			SudokuBoard[i][j]=a;
		}	
	}
}

//check for rows
counter=0;
for (i=0; i<numLines; i++){ //run through dim1 of testBoard
	for (j=1; j<numLines+1; j++){ //run through possible numbers
		counter=0;
		for (k=0; k<numLines; k++){ //run through dim2 of testBoard
			for (z=0; z<9; z++){ //run through dim3 of testBoard
				if (testBoard[i][k][z]==j){
					counter++;
					a=i;
					b=k;
				}
			}
		}
		if (counter==1){ //if there is only one possible number, add it to the board
			SudokuBoard[a][b]=j;
		}
	}
}

//check for columns
counter=0;
for (k=0; k<numLines; k++){ //run through dim2 of testBoard
	for (j=1; j<numLines+1; j++){ //run through possible numbers
		counter=0;
		for (i=0; i<numLines; i++){ //run through dim1 of testBoard
			for (int z=0; z<9; z++){ //run through dim3 of testBoard
				if (testBoard[i][k][z]==j){
					counter++;
					a=i;
					b=k;
				}
			}
		}
		if (counter==1){ //if there is only one possible number, add it to the board
			SudokuBoard[a][b]=j;
		}
	}
}

//check for mini-grids
counter=0;
int sqrSize = sqrt(numLines);
for (i=0; i<sqrSize; i++){
	for (z=1; z<numLines+1; z++){ //run through possible numbers
		counter=0;
		for (j=i*sqrSize; j<i*sqrSize+sqrSize; j++){ //run through dim1 of testBoard
			for (k=i*sqrSize; k<i*sqrSize+sqrSize; k++){ //run through dim2 of testBoard
				for (l=0; l<numLines; l++){
				if (testBoard[j][k][l]==z){
					counter++;
					a=j;
					b=k;
				}
				}
			
			}
		}
	
		if (counter==1){ //if there is only one possible number, add it to the board
			SudokuBoard[a][b]=z;
		}
	}
}


}

//checks if the puzzle is solved
template <typename T>
int puzzle<T>::checkDone(){
//runs through the entire testBoard to see if there are any possible values remaining
for (int i=0; i<numLines; i++){
	for (int j=0; j<numLines; j++){
		for (int k=0; k<numLines; k++){
			if (testBoard[i][j][k]!=0){
				return 0; //there are possible values remaining
			}
		}
	}
}

return 1; //the board is full
}

