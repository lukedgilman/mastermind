 // MasterMind.cpp : Defines the entry point for the console application.
/***************************************************************
* Name: Michael R. Nolan & Luke Gilman
* Course: Computer Science & Programming
* Class: CS04103 Section: 5
* Assignment Date: Monday, 04/30/18 @ 7:10pm
* File Name: MasterMind.cpp
*****************************************************************
* ID: MasterMind (Final Project)
* Purpose: Mimics the real life board game where the computer
* creates a random assortment of colours and the user has to
* guess the colors and in which order the go in.
*
*****************************************************************/

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstdlib>
#include "gameBoard.cpp"
//#include "stdafx.h"

using namespace std;


int main()
{
	bool playAgain;
	gameBoard g;
	
	do {
			g.start();
		}
		
	while (g.restart()); //function asking user if they want to play again after the game
	return 0;
}
