#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <string>
using namespace std;
//#pragma once

class gameBoard
{
public:

	gameBoard(); //default constructor

	void getKey();

	void assignColors();

	void start();

	bool restart();

	bool getWinner();

	bool isContained(int, int);

	void end();

	void display();
	
	void blackPegLogic(int, int);
	
	void whitePegLogic(int, int);
	
	void feedbackLogic(int);

};

#endif
