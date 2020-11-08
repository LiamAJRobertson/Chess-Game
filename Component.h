#ifndef Component_H
#define Component_H

#include <vector>
#include "Square.h"

enum PieceColour { BLACK, WHITE };

class Component 
{
private:

	int index;
	
	std::vector<std::vector<int>> moves;
	std::vector<std::vector<float>> moveHistory;
	static int nextIndex;
	float x, y;
	float width = 1.0f;
	float height = 1.0f;
	PieceColour pieceColour;

	char piece;

	static int leftIndex;
	static int rightIndex;

	

	void switchColour();

public:

	

	Component(char piece, float x, float y, PieceColour colour);
	Component();

	void setPiece(char piece);
	void setIndex(int n);
	int getIndex(void);


	bool Component::operator==(Component right);
	bool Component::operator!=(Component right);

	void drawPiece();

	void drawCircle(float x, float y, float radius, char piece);

	

	void setWidth(float w);
	void setHeight(float h);

	void setY(float newY);
	void setX(float newX);

	void setPieceColour(PieceColour colour);

	float getX();
	float getY();

	float getWidth();
	float getHeight();

	std::vector<std::vector<int>> getMoves();

	char getPiece();

	PieceColour getColour();

	std::vector<std::vector<float>> getMoveHistory();

	void printMoveHistory();
	void addMoveToHistory(float x, float y);
	void drawMoveHistory();
	void switchHistory();
	bool canMoveToPosition(int x, int y);
	bool pawnTakesPiece();


	void assignKnightMoves()
	{
		moves.push_back({ 2, -1 });
		moves.push_back({ 1, -2 });
		moves.push_back({ -1, -2 });
		moves.push_back({ -2, -1 });
		moves.push_back({ -2, 1 });
		moves.push_back({ -1, 2 });
		moves.push_back({ 1, 2 });
		moves.push_back({ 2, 1 });

	}

	void assignPawnMoves()
	{
		moves.push_back({ 0, -1 });
		moves.push_back({ 0, 1 });

	}

	void assignBishopMoves() {
		moves.push_back({ 1, -1 });
		moves.push_back({ 1, 1 });
		moves.push_back({ -1, 1 });
		moves.push_back({ -1, -1 });

		moves.push_back({ 2, -2 });
		moves.push_back({ 2, 2 });
		moves.push_back({ -2, 2 });
		moves.push_back({ -2, -2 });

		moves.push_back({ 3, -3 });
		moves.push_back({ 3, 3 });
		moves.push_back({ -3, 3 });
		moves.push_back({ -3, -3 });

		moves.push_back({ 4, -4 });
		moves.push_back({ 4, 4 });
		moves.push_back({ -4, 4 });
		moves.push_back({ -4, -4 });

		moves.push_back({ 5, -5 });
		moves.push_back({ 5, 5 });
		moves.push_back({ -5, 5 });
		moves.push_back({ -5, -5 });

		moves.push_back({ 6, -6 });
		moves.push_back({ 6, 6 });
		moves.push_back({ -6, 6 });
		moves.push_back({ -6, -6 });

		moves.push_back({ 7, -7 });
		moves.push_back({ 7, 7 });
		moves.push_back({ -7, 7 });
		moves.push_back({ -7, -7 });

	}

	void assignRookMoves() {
		moves.push_back({ 0, -1 });
		moves.push_back({ 0, -2 });
		moves.push_back({ 0, -3 });
		moves.push_back({ 0, -4 });
		moves.push_back({ 0, -5 });
		moves.push_back({ 0, -6 });
		moves.push_back({ 0, -7 });
		
		moves.push_back({ 0, 1 });
		moves.push_back({ 0, 2 });
		moves.push_back({ 0, 3 });
		moves.push_back({ 0, 4 });
		moves.push_back({ 0, 5 });
		moves.push_back({ 0, 6 });
		moves.push_back({ 0, 7 });

		moves.push_back({ 1, 0 });
		moves.push_back({ 2, 0 });
		moves.push_back({ 3, 0 });
		moves.push_back({ 4, 0 });
		moves.push_back({ 5, 0 });
		moves.push_back({ 6, 0 });
		moves.push_back({ 7, 0 });

		moves.push_back({ -1, 0 });
		moves.push_back({ -2, 0 });
		moves.push_back({ -3, 0 });
		moves.push_back({ -4, 0 });
		moves.push_back({ -5, 0 });
		moves.push_back({ -6, 0 });
		moves.push_back({ -7, 0 });
	}

	void assignKingMoves() {
		moves.push_back({ 1, 1 });
		moves.push_back({ -1, -1 });
		moves.push_back({ 1, -1 });
		moves.push_back({ -1, 1 });

		moves.push_back({ 0, 1 });
		moves.push_back({ 0, -1 });
		moves.push_back({ 1, 0 });
		moves.push_back({ -1, 0 });

	}

	void assignQueenMoves() {
		assignBishopMoves();
		assignRookMoves();
	}


};

#endif 


