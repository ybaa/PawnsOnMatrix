#pragma once

class Pawn {
public:
	Pawn();
	~Pawn();

	int getCollumn();
	int getRow();

	void drawPawn(int,int);
	void fillGapAfterPawnMove(int,int);
	void updatePosition(int,int);
	void turnLeft();

private:
	int collumn;
	int row;
};
