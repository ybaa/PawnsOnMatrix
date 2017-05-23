#include "Pawn.h"
#include <ncurses.h>
#include <iostream>
#include <vector>

using namespace std;

Pawn::Pawn() {
	initscr();
	collumn = -1;
	row = -1;
}

Pawn::~Pawn() {

}

int Pawn::getCollumn(){
	return collumn;
}

int Pawn::getRow(){
	return row;
}

void Pawn::drawPawn(int Y, int X){
	int rowToUpdate = Y;
	int collumnToUpdate = X;
	X *= 4;				//this 2 lines enable to type number of collumn and the program will draw it in correct place on the matrix
	X++;

	mvaddch(Y,X,'o');
//	getch();
	updatePosition(rowToUpdate,collumnToUpdate);
	endwin();


}

void Pawn::fillGapAfterPawnMove(int row, int collumn){
	collumn *= 4;
	collumn++;
	mvaddch(row,collumn, '_');
	endwin();
}

void Pawn::updatePosition(int row, int collumn){
	this -> row = row;
	this -> collumn = collumn;
}

void Pawn::turnLeft(int lastCollumn){
	fillGapAfterPawnMove(row,collumn);
	if(collumn != 0){
		collumn -= 1;
		drawPawn(row,collumn);
	}
	else{
		turnRight(lastCollumn);
	}
}

void Pawn::turnRight(int lastCollumn){
	fillGapAfterPawnMove(row,collumn);
	if( collumn != lastCollumn){
		collumn += 1;
		drawPawn(row,collumn);
	}
	else{
		turnLeft(lastCollumn);
	}
}

void Pawn::turnDown(int lastRow){
	fillGapAfterPawnMove(row,collumn);
	if(row != lastRow){
		row += 1;
		drawPawn(row,collumn);
	}
	else{
		turnUp(lastRow);
	}
}

void Pawn::turnUp(int lastRow){
	fillGapAfterPawnMove(row,collumn);
	if(row != 0){
		row -= 1;
		drawPawn(row,collumn);
	}
	else{
		turnDown(lastRow);
	}
}





