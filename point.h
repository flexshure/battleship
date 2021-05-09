#ifndef POINT_H
#define POINT_H

struct Point
{
private:
	int x,y;
	char status;
public:
	int getX() const { return x; }
	int getY() const { return y; }
	char getStatus() const { return status; }
	void setX(int xI) { x = xI; }
	void setY(int yI) { y = yI; }
	void setStatus(char s) { status = s; }
	void setPoint(int x, int y, char s);
	void setPoint(int x, int y);
};

#endif