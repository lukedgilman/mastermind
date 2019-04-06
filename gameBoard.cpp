#include "gameBoard.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <windows.h>
#include <vector>
//#include "stdafx.h"


using namespace std;


char assignedColor[4]; //the random generated colors
char newColors[6] = { 'R', 'O', 'Y', 'G', 'B', 'P' };//The player will have to guess 4 assigned colors
bool winner = false; //has the user won?
char guessedColor[10][4];
char feedBack[10][4];
int numAttempts = 0;
int numRed, numOrange, numYellow, numGreen, numBlue, numPurple;
bool contained;
int numCorrect = 0;
int blackPeg = 0;
int whitePeg = 0;
char pegCombo0[4] = {'B', 'B', 'B', 'B'};
char pegCombo1[4] = {'B', 'B', 'B', ' '};
char pegCombo2[4] = {'B', 'B', 'B', 'W'};
char pegCombo3[4] = {'B', 'B', ' ', ' '};
char pegCombo4[4] = {'B', 'B', 'W', ' '};
char pegCombo5[4] = {'B', 'B', 'W', 'W'};
char pegCombo6[4] = {'B', ' ', ' ', ' '};
char pegCombo7[4] = {'B', 'W', ' ', ' '};
char pegCombo8[4] = {'B', 'W', 'W', ' '};
char pegCombo9[4] = {'B', 'W', 'W', 'W'};
char pegCombo10[4] = {'W', 'W', 'W', 'W'};
char pegCombo11[4] = {' ', ' ', ' ', ' '};
char pegCombo12[4] = {'W', ' ', ' ', ' '};
char pegCombo13[4] = {'W', 'W', 'W', ' '};
char pegCombo14[4] = {'W', 'W', ' ', ' '};

gameBoard::gameBoard(){
	assignColors();
}

void gameBoard::assignColors(){
	srand(time(NULL)); //seeds the random generator
	
	int r, i;
	for (i = 0; i < 4; i++)
	{
		r = rand() % 6;
		assignedColor[i] = newColors[r];
	}
}

void gameBoard::start(){
	cout << "	   ";
	
	for(int c = 0; c < 10; c++ ){ //RESETS GAMEBOARD TO BEING BLANK IF REPLAYING
		for(int d = 0; d < 4; d++){
			guessedColor[c][d] = ' ';
			feedBack[c][d] = ' ';
		}
	}
	
	for (int r = 0; r < 10; r++){ //users 10 trys...
	
		numCorrect = 0;
		whitePeg = 0;
		blackPeg = 0;
		numRed = 0;         //resets solution peg counts after every try
		numOrange = 0;
		numYellow = 0;
		numGreen = 0;
		numBlue = 0;
		numPurple = 0;
		blackPeg = 0;
		whitePeg = 0;
		
		for(int g = 0; g < 4; g++){ //reassigns the correct number of colors with solution
		
			switch(assignedColor[g]){
		
			case 'R':
			numRed++;
			break;
			
			case 'O':
			numOrange++;
			break;
			
			case 'Y':
			numYellow++;
			break;
			
			case 'G':
			numGreen++;
			break;
			
			case 'B':
			numBlue++;
			break;
			
			case 'P':
			numPurple++;
			break;
			}
		}
		
		display(); //prints updated gameboard with user new guess
		cin >> guessedColor[r][0] >> guessedColor[r][1] >> guessedColor[r][2] >> guessedColor[r][3]; //r is the try && [0..3] is the guessed slot
		
		for (int i = 0; i < 4; i++){
			blackPegLogic(r, i);
		}
		for (int i = 0; i < 4; i++){
			whitePegLogic(r, i);
		}
		feedbackLogic(r);
		if (blackPeg > 3){ //ends for loop if user has more than 3 black pegs
			winner = true;
			getKey();
			break;
		} else {
			numAttempts++;
		}
	} //main for loop (runs for 10 times unless person wins)
		display(); //to show last and correct entry and winner display
} // end start()

void gameBoard::whitePegLogic(int r, int i){
	if(isContained(r, i)){
		if (guessedColor[r][i] != assignedColor[i]){
			switch(guessedColor[r][i]){
				
				case 'R':
				if(numRed > 0){
				whitePeg++;
				numRed--;
				}
				break;
							
				case 'O':
				if(numOrange > 0){
				whitePeg++;
				numOrange--;
				}
				break;
							
				case 'Y':
				if(numYellow > 0){
				whitePeg++;
				numYellow--;
				}
				break;
							
				case 'G':
				if(numGreen > 0){
				whitePeg++;
				numGreen--;
				}
				break;
							
				case 'B':
				if(numBlue > 0){
				whitePeg++;
				numBlue--;
				}
				break;
							
				case 'P':
				if(numPurple > 0){
				whitePeg++;
				numPurple--;
				}
				break;
							
				default:
				cout << "Error: please relaunch game!" << endl;
						
				} //ends switch statement
			}
		}
	}

void gameBoard::blackPegLogic(int r, int i){
			if (isContained(r, i)){
				if (guessedColor[r][i] == assignedColor[i]){ //r is the try && [0..3] is the guessed slot
				
					numCorrect++;
					
					blackPeg++;
					
					switch(guessedColor[r][i]){
						case 'R':
						numRed--;
						break;
						
						case 'O':
						numOrange--;
						break;
						
						case 'Y':
						numYellow--;
						break;
						
						case 'G':
						numGreen--;
						break;
						
						case 'B':
						numBlue--;
						break;
						
						case 'P':
						numPurple--;
						break;	
					}
					
				}
				
			}
			
		}
		
void gameBoard::feedbackLogic(int r){
				if (blackPeg == 4 && whitePeg == 0){
				copy(pegCombo0, pegCombo0 + 4, feedBack[r]);
			}else if(blackPeg == 3 && whitePeg == 0){
				copy(pegCombo1, pegCombo1 + 4, feedBack[r]);
			}else if(blackPeg == 3 && whitePeg == 1){
				copy(pegCombo2, pegCombo2 + 4, feedBack[r]);
			}else if (blackPeg == 2 && whitePeg == 0){
				copy(pegCombo3, pegCombo3 + 4, feedBack[r]);
			}else if (blackPeg == 2 && whitePeg == 1){
				copy(pegCombo4, pegCombo4 + 4, feedBack[r]);
			}else if (blackPeg == 2 && whitePeg == 2){
				copy(pegCombo5, pegCombo5 + 4, feedBack[r]);
			}else if (blackPeg == 1 && whitePeg == 0){
				copy(pegCombo6, pegCombo6 + 4, feedBack[r]);
			}else if (blackPeg == 1 && whitePeg == 1){
				copy(pegCombo7, pegCombo7 + 4, feedBack[r]);
			}else if (blackPeg == 1 && whitePeg == 2){
				copy(pegCombo8, pegCombo8 + 4, feedBack[r]);
			}else if (blackPeg == 1 && whitePeg == 3){
				copy(pegCombo9, pegCombo9 + 4, feedBack[r]);
			}else if (blackPeg == 0 && whitePeg == 4){
				copy(pegCombo10, pegCombo10 + 4, feedBack[r]);
			}else if (blackPeg == 0 && whitePeg == 0){
				copy(pegCombo11, pegCombo11 + 4, feedBack[r]);
			}else if (blackPeg == 0 && whitePeg == 1){
				copy(pegCombo12, pegCombo12 + 4, feedBack[r]);
			}else if (blackPeg == 0 && whitePeg == 3){
				copy(pegCombo13, pegCombo13 + 4, feedBack[r]);
			}else if (blackPeg == 0 && whitePeg == 2){
				copy(pegCombo14, pegCombo14 + 4, feedBack[r]);
			}else{
				cout << "Error: please relaunch game!" << endl;
			}
}

bool gameBoard::restart(){

	char playAgain;
	cout << endl << "Would you like to play again? (Y/N): ";
	cin >> playAgain;

	if (playAgain == 'Y' || playAgain == 'y') // accepts lower case or upper case responses
	{
		winner = false; //RESETS ALL VARIABLES TO ZERO
		numAttempts = 0;
		assignColors();
		
		return true;
	}
	else if (playAgain == 'N' || playAgain == 'n')
	{
		cout << endl << "Thanks for Playing!" << endl;
		return false;
	}
}

bool gameBoard::isContained(int r, int i){
	
	bool found = false;
	for (int j = 0; j < 4; j++)
	{
		if (guessedColor[r][i] == assignedColor[j])
			{
				found = true; 
			}
	}
	
	return found; 
}

void gameBoard::getKey() {
	cout << endl << "Solution: ";
	for (int y = 0; y < 4; y++)
	{
		cout << assignedColor[y] << " ";
	}
	cout << endl;
}

void gameBoard::display(){

	system("CLS"); //windows specific command
	//getKey(); //for debugging purposes
	cout << "		                MASTER  MIND 				        " << endl; //header
	cout << "	__________________________________________________________" << endl << endl;
	cout << "	       Board                                Feedback     " << endl;
	cout << "	___________________	               ___________________" << endl;

	for (int i = 0; i < 10; i++)
	{
		cout << "	";
		for (int j = 0; j < 4; j++) //i is the try && j [0..3] is the guessed slot
		{
			cout << "  " << guessedColor[i][j] << "  ";
		}
		cout << "	      	       ";
		for (int j = 0; j < 4; j++)
		{
			cout << "  " << feedBack[i][j] << "  ";
		}
		cout << endl;
	}
	
	if (winner == false && numAttempts < 10)
	{
		cout << "Attempt a guess: ";
		
	} else if (winner == true){
		cout << "You won!";
		getKey();
	}
	else {
		cout << endl << "You LOSE! Better luck next time!" << endl;
	}
}
