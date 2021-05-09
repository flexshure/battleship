#ifndef SHIP_H
#define SHIP_H

#include <string>
#include "point.h"
using namespace std;


class Ship
{
private:
	string name;
	int length;
	int hits;
	char orientation;
	Point position;
public:
	Ship(string, int);
	Ship() {};
	int getLength() const { return length; }
	int getHits() const { return hits; }
	string getName() const { return name; }
	Point getPos() const { return position; }
	int getX() const { return position.getX(); }
	int getY() const { return position.getY(); }
	char getOrient() const { return orientation; }
	void setPos(int, int, char);
	void setPos(int, int);
	void setPos(Point, char);
	void setPos(Point);
	void hitReg() { hits++; }
};


#endif