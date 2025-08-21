#pragma once
class Position
{
private:
	int row;
	int col;

public:
	Position(int row = 0, int col = 0);
	int getRow() const;
	int getCol() const;
	void setPosition(int r, int c);

	bool equals(const Position& other) const;
};