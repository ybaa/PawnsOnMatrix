#include "Matrix.h"
#include <ncurses.h>
#include <iostream>

Matrix::Matrix() {
	initscr();

}

Matrix::~Matrix() {

}

void Matrix::DrawMatrix(int width, int height){

	int collumn = 0;
	int row = 0;

	for(int i = 0; i < height; i++){			//double for because I need to create matrix
		for(int j = 0; j < width; j++){
			for(int k = 0; k < 3; k++){			//one more for because every cell consists of 3 '_'
			mvaddch(row, collumn, '_');
			collumn++;
			}
			mvaddch(row, collumn, '|');
			collumn++;
		}
		row++;
		collumn=0;
	}
	getch();



}

