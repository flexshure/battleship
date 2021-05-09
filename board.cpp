#include "point.h"
#include "ship.h"
#include "board.h"

using namespace std;

Board::Board(bool hiddenI)
{
	//	fill board with empty ocean
	for(int x = 0; x < 10; x++)
	{
		for(int y = 0; y < 10; y++)
		{
			this->board[x][y].setPoint(x,y,'o');
		}		
	}
	numOfShips = 0;
	hidden = hiddenI;
}

void Board::addShip(Ship &ship)
{
	if(ship.getOrient() == 'V')
		for(int i = 0; i < ship.getLength(); i++)
			this->board[ship.getX()][ship.getY()+i].setStatus('s');
	else
		for(int i = 0; i < ship.getLength(); i++)
			this->board[ship.getX()+i][ship.getY()].setStatus('s');

	this->ships.push_back(ship);
	numOfShips++;
}

void Board::addShip(Ship &ship, int x, int y, char orientation)
{
	ship.setPos(x,y,orientation);
	this->addShip(ship);
}

bool Board::isConflict(Ship ship) const
{
	if(ship.getOrient() == 'H')
	{
		for(int i = 0; i < ship.getLength(); i++)
			if(board[ship.getX()+i][ship.getY()].getStatus() == 's')
			return true;
				
	} else if(ship.getOrient() == 'V')	
	{
		for(int i = 0; i < ship.getLength(); i++)
			if(board[ship.getX()][ship.getY()+i].getStatus() == 's')
				return true;
	}
	return false;
}

bool Board::isLegal(Ship ship) const
{
	//	check board boundaries
	if(ship.getOrient() == 'V')
	{
		if(ship.getY() + ship.getLength() > 10)
			return(false);
	} else if(ship.getOrient() == 'H')
	{
		if(ship.getX() + ship.getLength() > 10)
			return(false);
	}
	
	if(isConflict(ship))
		return(false);
	

	return(true);	
}

void Board::addShipQuery(Ship &ship)
{
	char input;
	char orient;
	int xPos;
	int yPos;
	int valid = 1;

	do
	{
		if(valid == 0)
			cout << "Invalid location. Try again.\n";

		cout << ship.getName() << " (" << ship.getLength() << ")" << endl;

		//	orientation query
		do
		{
			cout << "Select an orientation (V/H): ";
			cin >> orient;
		} while(orient != 'V' && orient != 'H');

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

		ship.setPos(xPos, yPos, orient);
		valid = isLegal(ship);	//	check validity

		//	confirm?
		if(valid == 1)
		{
			do
			{
				cout << "Place " << ship.getName() << " " << ship.getOrient() << " on ";
				cout << static_cast<char>(ship.getX()+65) << ship.getY() << "? (Y/N)";
				cin >> input;
			} while (input != 'Y' && input != 'N');
			if(input == 'N')
				valid = 2;
		}

	} while(valid == 0 || valid == 2);

	this->addShip(ship); z
}

void Board::drawBoard() const
{
	for(int y = 0; y < 10; y++)
	{
		cout << "|" << y << "| ";
		for(int x = 0; x < 10; x++)
		{
			switch(this->board[x][y].getStatus()) {
				case 'o' :	//	open ocean
					cout << "~";
					break;
				case 's' :	//	ship
					if(!hidden)
						cout << "@";
					else
						cout << "~";
					break;
				case 'h' :	//	hit ship
					cout << "H";
					break;
				case 'm' :	//	miss
					cout << "x";
					break;
				case 'x' :	//	sunk ship
					cout << "=";
					break;
			};
			cout << " ";

		}
		if(y == 9)
			cout << "\\\\\\\n" << "------------------------\\\\\\\n";
		else
			cout << "\\\\\\\n";
	}

	cout << "|x| ";
	for(int i = 0; i < 10; i++)
	{
		cout << static_cast<char>(i+65) << " ";
		if(i == 9)
			cout << "\\\\\\";
	}
		
	cout << "\n///////////////////////////\n";
	if(!hidden)
		cout << "|||     YOUR  BOARD     |||\n";
	else
		cout << "|||      CPU BOARD      |||\n";
	cout << "///////////////////////////\n";
}

void Board::fireShot(Point point)
{
	int x = point.getX();
	int y = point.getY();

	switch(board[x][y].getStatus())
	{
		case 's' :
			board[x][y].setStatus('h');
			break;
		case 'o' :
			board[x][y].setStatus('m');
			break;
	}
}

void Board::updateShip(Ship ship)
{
	char orientation = ship.getOrient();
	int x = ship.getX();
	int y = ship.getY();

	if(orientation == 'V')
	{
		for(int i = 0; i < ship.getLength(); i++)
			if(board[x][y+i].getStatus() == 'h')
				ship.hitReg();

		if(ship.getHits() == ship.getLength())
			for(int i = 0; i < ship.getLength(); i++)
				board[x][y+i].setStatus('x');
	}
	if(orientation == 'H')
	{
		for(int i = 0; i < ship.getLength(); i++)
			if(board[x+i][y].getStatus() == 'h')
				ship.hitReg();

		if(ship.getHits() == ship.getLength())
			for(int i = 0; i < ship.getLength(); i++)
				board[x+i][y].setStatus('x');
	}		
}

void Board::updateShips()
{
	for(int i = 0; i < numOfShips; i++)
		updateShip(ships[i]);
}

void Board::listShips() const
{
	cout << "SHIPS:\n";
	for(int i = 0; i < numOfShips; i++)
	{
		cout << ships.at(i).getName() << this->ships.at(i).getX() << this->ships.at(i).getY() << endl;
	}		
}