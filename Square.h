#ifndef Square_H
#define Square_H

#include <iostream>

enum Colour { LIGHTBROWN, DARKBROWN };

class Square
{
public:

	Square();
	Square(int x, int y, Colour squareColour);

	int getX();
	int getY();

	int getWidth();
	int getHeight();

	void setX(int x);
	void setY(int y);

	void setWidth(int width);
	void setHeight(int height);

	void setColour(Colour squareColour);

	void printSquare();

	bool Square::operator==(Square right);

	void drawSquare();

private:
	int x;
	int y;
	float width, height;

	Colour squareColour;
};
#endif

