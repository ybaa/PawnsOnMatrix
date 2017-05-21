#include <iostream>
#include "Matrix.h"
#include "Pawn.h"
#include <ncurses.h>

using namespace std;

int main() {
	Matrix m;
	m.DrawMatrix(5,9);
	Pawn p;
	p.drawPawn(1,0);
	p.drawPawn(1,1);
	p.drawPawn(1,2);
	p.drawPawn(1,3);

	return 0;
}
