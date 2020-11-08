#include <iostream>
#include "Square.h"
#include "Window.h"

Square::Square()
{
	setX(0);
	setY(0);
}

Square::Square(int x, int y, Colour colour)
{
	setX(x);
	setY(y);
	setWidth(1);
	setHeight(1);
	setColour(colour);
}

int Square::getX()
{
	return x;
}

int Square::getY()
{
	return y;
}

int Square::getWidth() {
	return width;
}

int Square::getHeight() {
	return height;
}

void Square::setY(int yVal)
{
	y = yVal;
}

void Square::setX(int xVal)
{
	x = xVal;
}

void Square::setWidth(int widthVal) {
	width = widthVal;
}

void Square::setHeight(int heightVal) {
	height = heightVal;
}

void Square::setColour(Colour colour) {
	squareColour = colour;
}

void Square::printSquare()
{
	std::cout << "(" << getX() << ", " << getY() << ")" << std::endl;
}

bool Square::operator==(Square right)
{
	return(getX() == right.getX() && getY() == right.getY());
}


void Square::drawSquare() {
	std::cout << squareColour << std::endl;

	switch (squareColour) {
	case LIGHTBROWN:
		glColor3f(0.7f, 0.6f, 0.38f);
		break;
	case DARKBROWN:
		glColor3f(0.44, 0.3, 0.05);
		break;
	}
	glBegin(GL_QUADS);
	glVertex3f(x * width,  y * height, 0.0f);
	glVertex3f(width + (x * width), (y * height), 0.0f);
	glVertex3f(width + (x * width), (y * height) - height, 0.0f);
	glVertex3f((x * width),  (y * height) - height, 0.0f);
	glEnd();
}
//End of Square.cpp