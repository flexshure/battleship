#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "point.h"
#include "ship.h"
using namespace std;

class Board
{
	Point board[10][10];
	vector<Ship> ships;
	int numOfShips;
	bool hidden;
public:
	Board(bool);
	~Board() {};

	void unhide() { hidden = false; }
	bool isHidden() const { return hidden; }

	void addShip(Ship&);
	void addShip(Ship&, int, int, char);
	void addShipQuery(Ship&);

	bool isLegal(Ship) const;
	bool isConflict(Ship) const;

	void drawBoard() const;

	int getNumOfShips() const { return numOfShips; }
	char getStatus(int x, int y) const { return board[x][y].getStatus(); }


	void fireShot(Point);

	void updateShip(Ship);
	void updateShips();

	void listShips() const;
};

#endif