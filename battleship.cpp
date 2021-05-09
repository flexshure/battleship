#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#include "ship.h"
#include "point.h"
#include "board.h"
using namespace std;

void Setup();
void Draw();
void Input();
void Logic();

//global vars
	int stop = 0;
	bool bindows = 0;
	Board userBoard(false);
	Board cpuBoard(false);
	bool gameOver = false;
	Board *currentBoard = &userBoard;

	//	create my ships
	Ship myShips[] = { Ship("CARRIER", 5), Ship("BATTLESHIP", 4), Ship("CRUISER", 3), Ship("SUBMARINE", 3), Ship("DESTROYER", 2) };

	//	create cpu ships
	Ship cpuShips[] = { Ship("CARRIER", 5), Ship("BATTLESHIP", 4), Ship("CRUISER", 3), Ship("SUBMARINE", 3), Ship("DESTROYER", 2) };

// logic funcs
Point randPoint();
Point cpuGuess(Board);

// input funcs
void switchBoard();
void firePrompt(Board&);


// setup funcs
void isBindows();
void genCPUShips(Board);

int main()
{
	srand(time(NULL));
	Setup();

	while(!gameOver)
	{
		Draw();
		Input();
		Logic();
	}
}


void Setup()
{
	isBindows();
	genCPUShips(cpuBoard);
	for(int i = 0; i < 5; i++)
		cpuBoard.addShip(cpuShips[i]);
}


void Draw()
{
	if(bindows)
		system("cls");
	else
		system("clear");
	cout << setw(28) << setfill('\\') << "\n";
	cout << "||||     BATTLESHIP    ||||\n";
	cout << setw(28) << setfill('/') << "\n";
	currentBoard->drawBoard();
}

void Input()
{
	if(userBoard.getNumOfShips() < 5)
		userBoard.addShipQuery(myShips[userBoard.getNumOfShips()]);
	else
	{
		char input = 'F';
		do
		{
			cout << "ACTIONS:\n";
			cout << "(F)ire     (S)witch view\n";
			cin >> input;
		} while(input != 'F' && input != 'S');

		switch(input) {
			case 'F' :
				switchBoard();
				firePrompt(cpuBoard);
				break;
			case 'S' :
				switchBoard();
				break;
		}

	}

}

void Logic()
{
	cout << "logic\n";
	if(!(userBoard.getNumOfShips() < 5))
		userBoard.fireShot(cpuGuess(userBoard));
	stop++;
	if(stop > 10)
	gameOver = true;
}

void switchBoard()
{
	 if(currentBoard == &userBoard)
	 	currentBoard = &cpuBoard;
	 else
	 	currentBoard = &userBoard;
}

void isBindows()
{
	char input;
	cout << "Are you using cmd.exe? (y/n)";
	cin >> input;
	if(input == 'y')
		bindows = true;
}

Point randPoint()
{
	Point output;
	output.setX(rand() % 10);
	output.setY(rand() % 10);
	return output;
}

Point cpuGuess(Board board)
{
	bool valid = true;
	Point guess;
	do
	{
		guess = randPoint();
		if(board.getStatus(guess.getX(), guess.getY()) == 'o' || board.getStatus(guess.getX(), guess.getY()) == 's')
			valid = true;
		else
			valid = false;

	} while (valid);

	return(guess);
}

void genCPUShips(Board board)
{
	for(int i = 0; i < 5; i++)
	{
		char o;
		bool valid = 1;
		do
		{
			if(rand() % 2 == 1)
				o = 'V';
			else
				o = 'H';
			cpuShips[i].setPos(randPoint(), o);
			valid = board.isLegal(cpuShips[i]);
		} while (!valid);
		board.addShip(cpuShips[i]);
	}
}

void firePrompt(Board &board)
{
	char input;
	int xPos;
	int yPos;
	Point target;
	int valid = 1;

	do
	{
		if(valid == 0)
			cout << "Invalid location. Try again.\n";

		cout << "FIRE\n";
		//	xpos query
		do
		{
			cout << "Select X position (A-J): ";
			cin >> input;
		} while(!(input > 64 && input < 75));
		xPos = input-65;

		// ypos query
		do
		{
			cout << "Select Y position (0-9): ";
			cin >> yPos;
		} while(!(yPos >= 0 && yPos <= 9));

		//	confirm?
		if(valid == 1)
		{
			do
			{
				cout << "FIRE on ";
				cout << static_cast<char>(xPos+65) << yPos << "? (Y/N)";
				cin >> input;
			} while (input != 'Y' && input != 'N');
			if(input == 'N')
				valid = 2;
		}

	} while(valid == 0 || valid == 2);

	target.setPoint(xPos,yPos);
	board.fireShot(target);
}
