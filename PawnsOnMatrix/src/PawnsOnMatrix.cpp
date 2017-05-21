#include <iostream>
#include "Matrix.h"
#include <ncurses.h>

using namespace std;

int main() {
	Matrix m;
	m.DrawMatrix(5,9);

	return 0;
}
