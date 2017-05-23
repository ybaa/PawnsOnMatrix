#include "Matrix.h"
#include "Pawn.h"
#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <chrono>
#include <unistd.h>	//sleep


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


int main(){
	vector<int> XCoordinates;
	vector<int> YCoordinates;
	vector<Pawn> pawns;
	vector<int> freePlacesRow;
	vector<vector<int>> freePlaces;				//free place = -1

	//------------------------------- Create Range -------------------------------------------
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(4,16);

	int numberOfCollumns = dis(gen);
	int numberOfRows = dis(gen);

	//------------------------------- Draw Matrix -------------------------------------------
	Matrix m;
	m.DrawMatrix(numberOfCollumns,numberOfRows);

	//------------------------------- Fill matrix of free places-------------------------------
	for(int i = 0; i < numberOfCollumns; i++){
		for(int i = 0; i < numberOfRows; i++){
			freePlacesRow.push_back(-1);
		}
		freePlaces.push_back(freePlacesRow);
	}

	for(int i = 0; i < 5; i++){
		AddRandomCoordinatesToQueues(XCoordinates,YCoordinates,numberOfCollumns,numberOfRows);
	}


	for(int i = 0; i < 5; i++){
		Pawn p = Pawn();
		cout<< p.getCollumn() << " asd " << p.getRow()<<endl;
		int PawnCollumn = XCoordinates[i];
		int PawnRow = YCoordinates[i];
		p.drawPawn(PawnRow,PawnCollumn);
		pawns.push_back(p);
		cout<<pawns[i].getCollumn() << " " << pawns[i].getRow()<<endl;
		refresh();

		sleep(1);

		pawns[0].turnLeft();


	}



	getch();
	endwin();
	return 0;
}
