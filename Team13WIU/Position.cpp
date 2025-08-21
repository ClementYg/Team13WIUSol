#include "Position.h"

// When a position created, x and y set to 0
/*Position::Position()
{
	x = 0;
	y = 0;
}
*/
// Destroy Position to free memory
Position::~Position()
{

}

Position::Position(int r, int c) : y(r), x(c) {}


int Position::getY() const { return y; }
int Position::getX() const { return x; }




void Position::setPosition(int r, int c) {
	y = r;
	x = c;
}

bool Position::equals(const Position& other) const {
	return y == other.y && x == other.x;
}
