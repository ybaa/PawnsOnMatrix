#include "Pawn.h"
#include <ncurses.h>
#include <iostream>

Pawn::Pawn() {
	initscr();
}

Pawn::~Pawn() {

}

void Pawn::drawPawn(int row, int collumn){

	collumn *= 4;				//this 2 lines enable to type number of collumn and the program will draw it in correct place on the matrix
	collumn++;

	mvaddch(row,collumn,'o');
	getch();
	endwin();
}


