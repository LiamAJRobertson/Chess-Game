#ifndef OGWINDOW_H
#define OGWINDOW_H

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeGlut\freeglut.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Component.h"
#include "Square.h"



class Window 
{
	private:
		int wWidth, wHeight;	//width and height of openGL window in screen units
		double aspect_ratio;	//aspect ratio of viewport
		int xMin, xMax, yMin, yMax;		//parameters of orthographic projection

		int panelHeight;
		
		//Control Panel Titles


		char *GenerateBoardText = "Generate Board";
		char *ClearBoardText = "Clear Board";
		char *EditPiecesText = "Edit Pieces";

		int buttonWidth, buttonHeight;

		bool isClear = false;
		bool squareDraggingP;
		bool isDeleting;
		bool canMovePieces;
		bool isShowingHistory;
		
		//Buttons
		int buttonY;
		int newBoardX;
		int movePiecesX;
		int initialSetupX;

		const int pawn = 1;
		const int bishop = 2;
		const int knight = 3;
		const int rook = 4;
		const int queen = 5;
		const int king = 6;

		int board[8][8];

		int startup[8][8] = { rook,knight,bishop,king,queen,bishop,knight,rook,
							1,1,1,1,1,1,1,1,
							0,0,0,0,0,0,0,0,
							0,0,0,0,0,0,0,0,
							0,0,0,0,0,0,0,0,
							0,0,0,0,0,0,0,0,
							-1,-1,-1,-1,-1,-1,-1,-1,
							-rook,-knight,-bishop,-queen,-king,-bishop,-knight,-rook};
		
				
		std::vector<Component> pieces;
		std::vector<Square> squares;

		int numComponents;

		Colour squareColour;
		float squareX, squareY, squareWidth, squareHeight;
		float boardXOffset;
		float boardYOffset;
		float xOld, yOld;
		float componentXOld, componentYOld;


		Component *deletedComponent;

		Component *currentComponentPtr;
		Component *deleteComponentPtr;
		Square *currentSquarePtr;
		Square *linkSquPtr1, *linkSquPtr2;

		Component *readComponentPtr;
		


		void setupBoard(void);
		void clearBoard(void);
		void printBoard(void);
		void drawCircle(float x, float y, float radius);
		
		void screen2World(int screenX, int screenY, double & worldX, double & worldY);
		//void addPiece(int piece, int x, int y);
		void initializeComponents(void);
		void initializeSquares(void);
		bool onComponent(int screenX, int screenY);
		bool overlappingComponent(int screenX, int screenY);
		bool onSquare(int screenX, int ScreenY);
		//void snapToGrid(double x, double y);
		bool squareOnScreenP(double x, double y);
		//void onSquare(double x, double y);
		void updateBoard(float x, float y, char value);
		void setComponentPosFromBoard(int x, int y, Component *c);
		int getBoardPos(float x, float y);
		//float getBoardXOffset();
		void deletePiece(Component *component);
		void writeDateFile(char *datafile);

		bool isPieceDiagnol();
		bool isPieceInfront();
		

	public:

		void initGL(void);
		void MyReSizeGLScene(int fWidth, int fHeight);
		void drawButtonArea(GLvoid);
		void myDrawGLScene(GLvoid);
		void myDrawModel(GLvoid);
		void myMouseClick(int button, int state, int x, int y);
		void myMouseMotion(int x, int y);
		void myPassiveMouseMotion(int x, int y);
		void checkButtonClick(int x, int y);
		void myMenuFunction1(int option);
		static void write(char *text, float x, float y, void *font);

};

#endif