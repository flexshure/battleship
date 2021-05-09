#include <string>
#include <iostream>
#include "point.h"
#include "ship.h"
using namespace std;


Ship::Ship(string n, int l)
{
	name = n;
	length = l;
	hits = 0;
	this->setPos(0,0,'h');
}

void Ship::setPos(int x, int y, char o)
{
	this->setPos(x,y);
	orientation = o;
}

void Ship::setPos(int x, int y)
{
	position.setX(x);
	position.setY(y);
}

void Ship::setPos(Point point)
{
	int x = point.getX();
	int y = point.getY();
	this->setPos(x,y);
}

void Ship::setPos(Point point, char o)
{
	int x = point.getX();
	int y = point.getY();
	this->setPos(x,y,o);
}