#pragma once
class Position
{
public:
	int x;
	int y;
	//Position();
	~Position();

	Position(int r = 0, int c = 0);
	int getY() const;
	int getX() const;
	void setPosition(int r, int c);

	bool equals(const Position& other) const;

};