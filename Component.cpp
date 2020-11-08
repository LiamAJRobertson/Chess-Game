#define _USE_MATH_DEFINES

#include "Component.h"
#include "Window.h"
#include<math.h>
#include<Math.h>

using namespace std;

int Component::rightIndex = 1;

Component::Component(char piece, float x, float y, PieceColour colour) {
	setIndex(rightIndex);
	rightIndex += 1;

	setPiece(piece);
	setX(x);
	setY(y);
	moveHistory.reserve(100);
	moveHistory.push_back({ x, y });
	setPieceColour(colour);

	switch (piece) {
	case 'E' :
		break;
	case 'P':
		this->assignPawnMoves();
		break;
	case 'p':
		this->assignPawnMoves();
		break;
	case 'N':
		this->assignKnightMoves();
		break;
	case 'n':
		this->assignKnightMoves();
		break;
	case 'B':
		this->assignBishopMoves();
		break;
	case 'b':
		this->assignBishopMoves();
		break;
	case 'R':
		this->assignRookMoves();
		break;
	case 'r':
		this->assignRookMoves();
		break;
	case 'Q':
		this->assignQueenMoves();
		break;
	case 'q':
		this->assignQueenMoves();
		break;
	case 'K':
		this->assignKingMoves();
		break;
	case 'k':
		this->assignKingMoves();
		break;
	}
}


Component::Component() {
	setIndex(1);
	rightIndex += 1;

	setPiece(' ');
}

void Component::setIndex(int n) {
	index = n;
}

int Component::getIndex(void) {
	return index;
}

char Component::getPiece() {
	return piece;
}

void Component::setPiece(char name) {
	piece = name;
}

void Component::drawPiece() {
	
	drawCircle(x, y, width/2, piece);
	glColor3f(1.0f, 1.0f, 1.0f);
	
}

bool Component::operator==(Component right)
{
	return(getX() == right.getX() && getY() == right.getY() && getPiece() == right.getPiece() && getColour() == right.getColour());
}

bool Component::operator!=(Component right)
{
	return!(getX() == right.getX() && getY() == right.getY());
}


const float DEG2RAD = (float)M_PI / 180;
void Component::drawCircle(float x, float y, float radius, char pieceName) {
	
	switchColour();
	Window::write(&pieceName, x, y, GLUT_BITMAP_HELVETICA_18);

	switch (pieceColour) {
	case BLACK:
		glColor3f(0.0f, 0.0f, 0.0f);
		break;
	case WHITE:
		glColor3f(1.0f, 1.0f, 1.0f);
		break;
	}
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float degInRad = i*DEG2RAD;
		glVertex2f(cos(degInRad)* radius + x, sin(degInRad)*radius + y);
	}
	
	glEnd();
	
}


void Component::switchColour() {
	if (pieceColour == BLACK) {
		glColor3f(1.0f, 1.0f, 1.0f);
	}else {
		glColor3f(0.0f, 0.0f, 0.0f);
	}
}


void Component::setHeight(float h) {
	height = h;
}

void Component::setWidth(float w) {
	width = w;
}

void Component::setY(float newY) {
	y = newY;
}

void Component::setX(float newX) {
	x = newX;
}

float Component::getY() {
	return y;
}

float Component::getX() {
	return x;
}

float Component::getWidth() {
	return width;
}

float Component::getHeight() {
	return height;
}

PieceColour Component::getColour() { 
	return pieceColour; 
}

std::vector<std::vector<float>> Component::getMoveHistory() {
	return moveHistory;
}

void Component::setPieceColour(PieceColour colour) {
	pieceColour = colour;
}

void Component::printMoveHistory() {
	cout << "History" << endl;
	std::vector<std::vector<float>>::iterator it;
	for (it = moveHistory.begin(); it != moveHistory.end(); ++it) {
		cout << "x: " << (*it)[0]  << ", y: " << (*it)[1] << endl;

		/*
		std::vector<float>::iterator it2;
		for (it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
			cout << *it2 << endl;
		}
		*/

	}
}

void Component::addMoveToHistory(float x, float y) {
	moveHistory.push_back({ x, y });
}

void Component::drawMoveHistory() {
	cout << "Drawing move history" << endl;
	std::vector<std::vector<float>>::iterator it;
	if (!moveHistory.empty()) {
		for (it = moveHistory.begin(); it != moveHistory.end() - 1; ++it) {

			glColor3f(.0f, 0.0f, 0.0f);
			glBegin(GL_LINES);
			glVertex3f((*it)[0], (*it)[1], 0);
			auto nx = std::next(it);
			glVertex3f((*(nx))[0], (*(nx))[1], 0);
			glEnd();

			glutPostRedisplay();

		}
	}
	
}

std::vector<std::vector<int>> Component::getMoves() {
	return moves;
}

bool Component::canMoveToPosition(int x, int y) {
	std::vector<std::vector<int>>::iterator it;

	for (it = moves.begin(); it != moves.end(); ++it) {
		if ((*it)[0] == x && (*it)[1] == y) {
			return true;
		}
	}
	return false;
}



