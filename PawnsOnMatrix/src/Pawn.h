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
	void turnLeft(int);
	void turnRight(int);
	void turnUp(int);
	void turnDown(int);

private:
	int collumn;
	int row;
};
