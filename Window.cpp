#define _USE_MATH_DEFINES

#include "Window.h"
#include<math.h>
#include<Math.h>
#include "Component.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


void Window::initGL(void) {

	
	boardXOffset = 1.0f;
	boardYOffset = 9.0f;
	setupBoard();
	printBoard();

	glClearColor(1.0, 1.0, 1.0, 1.0);

	panelHeight = 40;

	buttonWidth = 100;
	buttonHeight = 30;

	newBoardX = 10;
	initialSetupX = 130;
	movePiecesX = 250;
	buttonY = 10;

	squareHeight = 1.0;
	squareWidth = 1.0;


	initializeSquares();
	initializeComponents();

	canMovePieces = false;
	isDeleting = false;
	isShowingHistory = false;

	deletedComponent = NULL;

	squareColour = LIGHTBROWN;

	printBoard();

	
	writeDateFile("C:/Users/endez chavez/source/repos/1504603_Liam_Robetson_CM3115_Coursework/1504603_Liam_Robetson_CM3115_Coursework/res/boardData.txt");

}



void Window::MyReSizeGLScene(int fWidth, int fHeight) 
{
	//Store window size in class variable
	wWidth = fWidth;
	wHeight = fHeight - panelHeight;

	//Calculate aspect ratio of the window
	aspect_ratio = (float)fWidth / fHeight;

	//set camera so it can see a square area of space running from 0 to 10
	//in both directions, plus a little bit extra

	yMin = -1;
	yMax = 12;
	xMin = -1;

	//set xMax so that the aspet ratio of the projection is the same as the viewport ratio
	xMax = (int)(aspect_ratio * (yMax - yMin)) + xMin;

	glMatrixMode(GL_PROJECTION);	//select the projection stack
	glLoadIdentity();	//reset the projection matrix back to default
	glOrtho(xMin, xMax, yMin, yMax, -1.0, 1.0);		//multiply the projection matrix by camera coordinates

	glViewport(0, 0, wWidth, wHeight);	//Viewport fills the window

}

void Window::myMouseClick(int button, int state, int x, int y) {

	//check if clicked on component
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (onComponent(x, y)) {
			currentComponentPtr->printMoveHistory();

			squareDraggingP = true;
			xOld = x;
			yOld = y;
			componentXOld = currentComponentPtr->getX();
			componentYOld = currentComponentPtr->getY();

		}
		else {
			squareDraggingP = false;
		}
	}

	//On click up
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP ) {
		checkButtonClick(x, y);

		cout << "Dragging?:" << squareDraggingP << endl;
		if (squareDraggingP && canMovePieces) {

			int xDiff = componentXOld - squareX;
			int yDiff = componentYOld - squareY;

			cout << "XDiff: " << xDiff << ", YDiff: " << yDiff << endl;

			overlappingComponent(x, y);
			//If the player can move to this location or the piece selected is a pawn (which can only take diagonally)
			cout << "Is Piece Diagnol? " << isPieceDiagnol() << endl;
			cout << "Is piece in front:" << isPieceInfront() << endl;
			if (currentComponentPtr->canMoveToPosition(xDiff, yDiff) && isPieceInfront() == false || (((currentComponentPtr->getPiece() == 'P' || currentComponentPtr->getPiece() == 'p') && isPieceDiagnol() == true))) {
				
				if (deleteComponentPtr != NULL) {
					if ((deleteComponentPtr->getColour() == currentComponentPtr->getColour() && overlappingComponent(x,y))) {
						cout << "dletePieceComponentName: " << deleteComponentPtr->getColour() << endl;
						currentComponentPtr->setX(componentXOld);
						currentComponentPtr->setY(componentYOld);
						return;
					}
				}

		
				float initialComponentX = componentXOld - currentComponentPtr->getWidth() / 2;
				float initialComponentY = componentYOld + currentComponentPtr->getHeight() / 2;


				updateBoard(initialComponentX, initialComponentY, 'E');

				cout << "Can move here" << endl;

				if (overlappingComponent(x, y)) {
					deletedComponent = new Component(deleteComponentPtr->getPiece(), deleteComponentPtr->getX(), deleteComponentPtr->getY(), deleteComponentPtr->getColour());
					deletePiece(deleteComponentPtr);
					numComponents--;
					writeDateFile("C:/Users/endez chavez/source/repos/1504603_Liam_Robetson_CM3115_Coursework/1504603_Liam_Robetson_CM3115_Coursework/res/boardData.txt");
					cout << "on another piece" << endl;
					cout << "piece to be deleted:" << deleteComponentPtr->getPiece() << endl;
					deleteComponentPtr = NULL;
					
				}
				else {
					deletedComponent = NULL;
				}


				currentComponentPtr->addMoveToHistory(currentComponentPtr->getX(), currentComponentPtr->getY());
				updateBoard(squareX, squareY, currentComponentPtr->getPiece());
				onComponent(x, y);
				printBoard();
			}
			//If not on a valid spot, set component to old spot
			else {
				currentComponentPtr->setX(componentXOld);
				currentComponentPtr->setY(componentYOld);
			}
			
		}	
		
		squareDraggingP = false;
		glutPostRedisplay();
	}
}

void Window::myMouseMotion(int x, int y) {
	if (squareDraggingP) {
		if (onSquare(x, y)) {
			squareX = currentSquarePtr->getX() + currentComponentPtr->getWidth() / 2;
			squareY = currentSquarePtr->getY() - currentComponentPtr->getHeight() / 2;

			
			if (canMovePieces) {
				//only set the pieces position if it has moved a square 
				if (squareX != currentComponentPtr->getX()) {
	
					currentComponentPtr->setX(squareX);

				}

				if (squareY != currentComponentPtr->getY()) {
					currentComponentPtr->setY(squareY);
				}

				glutPostRedisplay();
			}
		}
	}
}

void Window::myPassiveMouseMotion(int x, int y) {
	//cout << "x:" << x << " , y:" << y << endl;
	if (onSquare(x, y)) {
		//cout << currentSquarePtr->getY() << endl;
	}
}

void Window::myDrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//clear the drawing area

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xMin, xMax, yMin, yMax, -1.0, 1.0);
	glViewport(0, 0, wWidth, wHeight);

	Window::myDrawModel();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, wWidth, 0, panelHeight, -1.0, 1.0);
	glViewport(0, wHeight, wWidth, panelHeight);		// Button area

	drawButtonArea();

	glutSwapBuffers();	//Needed if we're running animation
	glFlush();
}

void Window::myDrawModel(GLvoid) {

	std::vector<Component>::iterator it;
	
	for (it = pieces.begin(); it != pieces.end(); ++it) {
	
		if (isShowingHistory) {
			glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
			it->drawMoveHistory();
		}
		it->drawPiece();
	}

	std::vector<Square>::iterator SqIt;
	for (SqIt = squares.begin(); SqIt != squares.end(); ++SqIt) {
		SqIt->drawSquare();
	}

	
	
}

//set up board starting position
void Window::setupBoard(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = startup[i][j];
		}
	}
}

//clear board 
void Window::clearBoard(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = 0;
		}
	}
}

int Window::getBoardPos(float x, float y) {
	int boardX = x - boardXOffset;
	int boardY = boardYOffset - y;
	return board[boardY][boardX];
}


void Window::updateBoard(float x, float y, char value) {
	int piece = 0;

	int boardX = x - boardXOffset;
	int boardY = boardYOffset - y ;

	cout << "boardXPos:" << boardX << ", boardYPos: " << boardY << endl;
	
	switch (value) {
	case 'E':
		piece = 0;
		break;
	case 'P':
		piece = 1;
		break;
	case 'N':
		piece = 3;
		break;
	case 'B':
		piece = 2;
		break;
	case 'R':
		piece = 4;
		break;
	case 'Q':
		piece = 5;
		break;
	case 'K':
		piece = 6;
		break;
	case 'p':
		piece = -1;
		break;
	case 'n':
		piece = -3;
		break;
	case 'b':
		piece = -2;
		break;
	case 'r':
		piece = -4;
		break;
	case -'q':
		piece = -5;
		break;
	case 'k':
		piece = -6;
		break;
	}
	
	board[boardY][boardX] = piece;
}

const float DEG2RAD = (float)M_PI / 180;

void Window::drawCircle(float x, float y, float radius) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float degInRad = i*DEG2RAD;
		glVertex2f(cos(degInRad)* radius + x ,sin(degInRad)*radius + y);

	}
	glEnd();
	
}


void Window::printBoard(void) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << board[i][j] << ", ";
		}

		cout << endl;
	}
}

void Window::drawButtonArea(GLvoid) {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(wWidth, 0, 0);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	Window::write(ClearBoardText, newBoardX, buttonY + buttonHeight/2, GLUT_BITMAP_HELVETICA_12);
	Window::write(GenerateBoardText, initialSetupX, buttonY + buttonHeight / 2, GLUT_BITMAP_HELVETICA_12);
	Window::write(EditPiecesText, movePiecesX, buttonY + buttonHeight / 2, GLUT_BITMAP_HELVETICA_12);

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		glVertex3f(newBoardX, buttonY, 0);
		glVertex3f(newBoardX + buttonWidth, buttonY, 0);
		glVertex3f(newBoardX + buttonWidth, buttonY + buttonHeight, 0);
		glVertex3f(newBoardX, buttonY + buttonHeight, 0);

		glVertex3f(initialSetupX, buttonY, 0);
		glVertex3f(initialSetupX + buttonWidth, buttonY, 0);
		glVertex3f(initialSetupX + buttonWidth, buttonY + buttonHeight, 0);
		glVertex3f(initialSetupX, buttonY + buttonHeight, 0);

		glVertex3f(movePiecesX, buttonY, 0);
		glVertex3f(movePiecesX + buttonWidth, buttonY, 0);
		glVertex3f(movePiecesX + buttonWidth, buttonY + buttonHeight, 0);
		glVertex3f(movePiecesX, buttonY + buttonHeight, 0);
		
		
	glEnd();
}

void Window::screen2World(int screenX, int screenY, double & worldX, double & worldY) {
	//Dimensions of rectangle viewd by camera projection
	double projWidth = xMax - xMin;
	double projHeight = yMax - yMin;

	//Screen coords with origin at bottom left
	int screenLeft = screenX;
	int screenUp = wHeight + panelHeight - screenY;

	worldX = xMin + screenLeft * projWidth / wWidth;
	worldY = yMin + screenUp * projHeight / wHeight;
}

void Window::initializeComponents() {

	pieces.reserve(32);

	char piece = ' ';
	PieceColour colour;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != 0) {
				switch (board[i][j]) {
				case 0:
					piece = ' ';
					break;
				case 1:
					piece = 'P';
					break;
				case 2:
					piece = 'B';
					break;
				case 3:
					piece = 'N';
					break;
				case 4:
					piece = 'R';
					break;
				case 5:
					piece = 'Q';
					break;
				case 6:
					piece = 'K';
					break;
				case -1:
					piece = 'p';
					break;
				case -2:
					piece = 'b';
					break;
				case -3:
					piece = 'n';
					break;
				case -4:
					piece = 'r';
					break;
				case -5:
					piece = 'q';
					break;
				case -6:
					piece = 'k';
					break;
				}
				if (board[i][j] < 0) {
					colour = BLACK;
				}
				else {
					colour = WHITE;
				}

				Component *component = new Component(piece, j + boardXOffset + squareWidth / 2, boardYOffset - i - squareHeight / 2, colour);
				
				pieces.push_back(*component);
				numComponents++;
			}
		}
	}
}

void Window::initializeSquares() {
	Colour colour;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int index2d = i + j;
			if (index2d % 2 == 0) {
				colour = LIGHTBROWN;
			}
			else {
				colour = DARKBROWN;
			}
			Square *square = new Square(j + boardXOffset , boardYOffset - i, colour);
			squares.push_back(*square);
		}
	}
}

void Window::checkButtonClick(int x, int y)
{
	if (y < buttonY || y > 30) // Above or below buttons
		return;

	//clearBoard
	if (x >= newBoardX && x <= newBoardX + buttonWidth) {
		clearBoard();
		//cout << pieces.size();
		pieces.clear();
		//cout << pieces.size();
		isClear = true;
	}

	//initialize board
	if (x >= initialSetupX && x <= initialSetupX + buttonWidth && isClear) {
		setupBoard();
		//printBoard();
		initializeComponents();
		isClear = false;

	}

	//edit pieces
	if (x >= movePiecesX && x <= movePiecesX + buttonWidth) {
		cout << "Edit Tool:" << canMovePieces << endl;
		if (canMovePieces == false) {
			canMovePieces = true;
		}
		else {
			canMovePieces = false;
		}
	}
}


void Window::deletePiece(Component *component) {
	auto it = std::find(pieces.begin(), pieces.end(), *component);
	if (it != pieces.end()) { 
		pieces.erase(it); 
	}
}


bool Window::onComponent(int screenX, int screenY) {
	double worldX, worldY;

	screen2World(screenX, screenY, worldX, worldY);
	std::vector<Component>::iterator it;
	for (it = pieces.begin(); it != pieces.end(); ++it) {
		//cout << it->getY() << endl;
		if (worldX >= it->getX() - it->getWidth()/2 && worldX <= it->getX() + it->getWidth()/2
			&& worldY >= it->getY() - it->getHeight()/2 && worldY <= it->getY() + it->getHeight()/2) {
			//cout << "x: " << it->getX() << ", y: " << it->getY() << endl;
			currentComponentPtr = & (*it);
			return true;
		}
	}
	return false;
}

bool Window::overlappingComponent(int screenX, int screenY) {
	double worldX, worldY;

	screen2World(screenX, screenY, worldX, worldY);
	std::vector<Component>::iterator it;
	for (it = pieces.begin(); it != pieces.end(); ++it) {
		//cout << it->getY() << endl;
		if (worldX >= it->getX() - it->getWidth() / 2 && worldX <= it->getX() + it->getWidth() / 2
			&& worldY >= it->getY() - it->getHeight() / 2 && worldY <= it->getY() + it->getHeight() / 2) {
			//cout << "x: " << it->getX() << ", y: " << it->getY() << endl;
			//cout << "Is on a component to be deleted" << endl;
			if (&(*it) != currentComponentPtr) {
				cout << "Is on a component to be deleted" << endl;
				deleteComponentPtr = &(*it);
				return true;
			}
		}
	}
	return false;
}

bool Window::onSquare(int screenX, int screenY) {
	double worldX, worldY;

	screen2World(screenX, screenY, worldX, worldY);
	std::vector<Square>::iterator it;
	for (it = squares.begin(); it != squares.end(); ++it) {
		//cout << it->getY() << endl;
		if (worldX >= it->getX() && worldX <= it->getX() + it->getWidth()
			&& worldY >= it->getY() - it->getHeight() && worldY <= it->getY()) {
			currentSquarePtr = &(*it);
			return true;
		}
	}
	return false;
}

bool Window::squareOnScreenP(double x, double y) {
	return(
		x >= xMin &&
		x + squareWidth <= xMax &&
		y >= yMin &&
		y + squareHeight <= yMax
		);
}



void Window::writeDateFile(char *datafile) {
	ofstream boardFile(datafile, ios::out);
	boardFile << "ITEMS " << numComponents << endl;

	Component *ptr = &(pieces[0]);
	for (int i = 0; i < numComponents; ++i) {
		boardFile << ptr->getPiece();

		// Set output precision to one place of decimals
		boardFile.precision(1);
		// Always print the digits after the decimal point even if they're 0
		// Use fixed point notation, not scientific (exponential) notation
		boardFile << showpoint << fixed;
		boardFile << " ";
		boardFile << ptr->getX();
		boardFile << " ";
		boardFile << ptr->getY();
		boardFile << endl;

		ptr++;
	}
	boardFile.close();
}

void Window::setComponentPosFromBoard(int x, int y, Component *c) {

	int componentX = x + boardXOffset;
	int componentY = boardYOffset + y;

	c->setX(componentX);
	c->setY(componentY);
}

void Window::myMenuFunction1(int Option)
{
	std::vector<Component>::iterator it;
	std::vector<std::vector<float>>::iterator it2;
	switch (Option) {
		//Switch Players
		
	case 1:
		cout << "Option 1 selected\n";
		
		cout << "before swap" << endl;
		printBoard();
		//update board
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				swap(board[i][j], board[7 - i][7 - j]);

			}
		}

		//Update components positions

		
		for (it = pieces.begin(); it != pieces.end(); ++it) {
			it->setY(boardYOffset - it->getY() + 1);
			it->setX(boardXOffset + 8 - it->getX() + 1);
	
		}


		if (componentXOld != NULL && componentYOld != NULL) {
			componentXOld = boardXOffset + 8 - componentXOld + 1;
			componentYOld = boardYOffset - componentYOld + 1;
		}
		
		
		//pieces.clear();
		//initializeComponents();
		glutPostRedisplay();

		//update components

		cout << "after swap" << endl;
		printBoard();
	
		break;
	case 2:
		cout << "Option 2 selected\n";
		if (componentXOld != NULL && componentXOld != NULL) {
			cout << "OldX: " << componentXOld << ", oldY: " << componentYOld << endl;
			if (deletedComponent == NULL) {
				updateBoard(currentComponentPtr->getX(), currentComponentPtr->getY(), 'E');
			}
			else {
				updateBoard(deletedComponent->getX(), deletedComponent->getY(), deletedComponent->getPiece());
				pieces.push_back(*deletedComponent);
				deletedComponent = NULL;
			}
			
			currentComponentPtr->setX(componentXOld);
			currentComponentPtr->setY(componentYOld);
			updateBoard(componentXOld, componentYOld, currentComponentPtr->getPiece());
			printBoard();
			glutPostRedisplay();
		}
		break;
	case 3:
		//Draw Moving History
		if (isShowingHistory == false) {
			isShowingHistory = true;
			
		}
		else {
			isShowingHistory = false;
		}
		glutPostRedisplay();
		
		//exit(0);
	}

}

void Window::write(char *text, float x, float y, void *font) {
	glRasterPos2f(x, y);
	
	for (char *c = text; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
		
	}
}

bool Window::isPieceDiagnol() {
	if (currentComponentPtr != NULL && deleteComponentPtr != NULL) {
		int xDiff = componentXOld - deleteComponentPtr->getX();
		int yDiff = componentYOld - deleteComponentPtr->getY();

		cout << "Difference from current cpmponent to delete component x: " << xDiff << endl;
		cout << "Difference from current cpmponent to delete component y: " << yDiff << endl;
		if (xDiff == 1 && yDiff == 1) {
			return true;
		}
		else if (xDiff == -1 && yDiff == -1) {
			return true;
		}
		else if (xDiff == -1 && yDiff == 1) {
			return true;
		}
		else if (xDiff == 1 && yDiff == -1) {
			return true;
		}
	}
	return false;
}

bool Window::isPieceInfront() {
	if (currentComponentPtr != NULL && deleteComponentPtr != NULL) {
		int xDiff = componentXOld - deleteComponentPtr->getX();
		int yDiff = componentYOld - deleteComponentPtr->getY();

		if (xDiff == 0 && yDiff == 1) {
			return true;
		}
		else if (xDiff == 0 && yDiff == -1) {
			return true;
		}
	}
	return false;
}


