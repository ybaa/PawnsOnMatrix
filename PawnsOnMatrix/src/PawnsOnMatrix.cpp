#include <iostream>
#include "Matrix.h"
#include "Pawn.h"
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <chrono>


using namespace std;

void AddRandomCoordinatesToQueues(vector<int> &X, vector<int> &Y, int numberOfCollumns, int numberOfRows){
	mt19937 mt;
	mt.seed(std::chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> *fixedDist;

	int maxValue = numberOfCollumns-1;
	fixedDist = new uniform_int_distribution<int>(0, maxValue);
	int num = (*fixedDist)(mt);
	X.push_back(num);

	maxValue = numberOfRows -1;
	fixedDist = new uniform_int_distribution<int>(0,maxValue );
	num = (*fixedDist)(mt);
	Y.push_back(num);

	delete fixedDist;
}


int main() {
	vector<int> XCoordinates;
	vector<int> YCoordinates;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(4,16);

	int numberOfCollumns = dis(gen);
	int numberOfRows = dis(gen);

	Matrix m;
	m.DrawMatrix(numberOfCollumns,numberOfRows);

	for(int i = 0; i < 5; i++){
		AddRandomCoordinatesToQueues(XCoordinates,YCoordinates,numberOfCollumns,numberOfRows);
	}

	Pawn p;
	for(int i = 0; i < 5; i++){
		int PawnCollumn = XCoordinates[i];
		int PawnRow = YCoordinates[i];
		p.drawPawn(PawnRow,PawnCollumn);

	}

	return 0;
}
