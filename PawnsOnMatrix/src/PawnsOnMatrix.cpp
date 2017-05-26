#include "Matrix.h"
#include "Pawn.h"
#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <chrono>
#include <unistd.h>	//sleep
#include <thread>
#include <mutex>


using namespace std;

vector<int> XCoordinates;
vector<int> YCoordinates;
vector<Pawn> pawns;

void addRandomCoordinatesToQueues(vector<int> *Xx, vector<int> *Yy, int numberOfCollumns, int numberOfRows){
	vector<int> &X = *Xx;
	vector<int> &Y = *Yy;
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

void DrawPawnAndMoveOthers(vector<int> *Xx, vector<int> *Yy, int numberOfCollumns, int numberOfRows){
	vector<int> &X = *Xx;
	vector<int> &Y = *Yy;

	Pawn p = Pawn();
	bool canDraw = true;

	for(int i = 0; i < pawns.size(); i++){
		if(pawns[i].getCollumn() == X[0] && pawns[i].getRow() == Y[0])
			canDraw = false;
		else
			canDraw = true;
	}

	if(canDraw){
	p.drawPawn(Y[0], X[0]);
	pawns.push_back(p);
	X.erase(X.begin());
	Y.erase(Y.begin());
	}

	for(int i = 0; i < pawns.size()-1; i++){
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(0,3);
		int direction = dis(gen);

		switch (direction) {
			case 0:
				pawns[i].turnLeft(numberOfCollumns-1);
				break;
			case 1:
				pawns[i].turnUp(numberOfRows-1);
				break;
			case 2:
				pawns[i].turnRight(numberOfCollumns-1);
				break;
			case 3:
				pawns[i].turnDown(numberOfRows-1);
				break;
			default:
				break;
		}
	}



	refresh();
	sleep(3);
	endwin();
}

int main(){
	mutex mx;

	//------------------------------- Create Range -------------------------------------------
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(4,16);

	int numberOfCollumns = dis(gen);
	int numberOfRows = dis(gen);

	//------------------------------- Draw Matrix -------------------------------------------
	Matrix m;
	m.DrawMatrix(numberOfCollumns,numberOfRows);



	// how to eliminate this for? (important only when I use do while belowe)
//	for(int i = 0; i < 1; i++){
//		addRandomCoordinatesToQueues(&XCoordinates,&YCoordinates,numberOfCollumns,numberOfRows);
//	}

	for(int i = 0; i < 1000 ; i++){
	//do{
	thread fillQueues(addRandomCoordinatesToQueues,&XCoordinates,&YCoordinates,numberOfCollumns,numberOfRows);

	mx.lock();
	fillQueues.join();
	mx.unlock();

	thread DrawAndMovePawns(DrawPawnAndMoveOthers, &XCoordinates, &YCoordinates, numberOfCollumns, numberOfRows);
	DrawAndMovePawns.join();
	}; //while(XCoordinates.empty()==false && YCoordinates.empty() ==false);

	return 0;
}
