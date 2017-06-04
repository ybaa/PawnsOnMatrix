#include "Matrix.h"
#include "Pawn.h"
#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

vector<Pawn> pawns;
mutex mx1;
mutex mx2;

void addRandomCoordinatesToQueues(vector<int> *Xx, vector<int> *Yy, int numberOfCollumns, int numberOfRows){
	while(true){
		vector<int> &X = *Xx;
		vector<int> &Y = *Yy;

		mt19937 mt;
		mt.seed(std::chrono::system_clock::now().time_since_epoch().count());
		uniform_int_distribution<int> *fixedDist;

		int maxValue = numberOfCollumns-1;
		fixedDist = new uniform_int_distribution<int>(0, maxValue);
		int num = (*fixedDist)(mt);

		mx1.lock();
		X.push_back(num);

		maxValue = numberOfRows -1;
		fixedDist = new uniform_int_distribution<int>(0,maxValue );
		num = (*fixedDist)(mt);

		Y.push_back(num);
		mx1.unlock();

		delete fixedDist;
	}
}

void addPawn(vector<int> *Xx, vector<int> *Yy, int numberOfCollumns, int numberOfRows){
	while(true){
		vector<int> &X = *Xx;
		vector<int> &Y = *Yy;
		bool canAddPawn = true;

		Pawn p = Pawn();

		mx2.lock();
		for(int i = 0; i < pawns.size(); i++){
			if(pawns[i].getCollumn() == X[0] && pawns[i].getRow() == Y[0])
				canAddPawn = false;
			else
				canAddPawn = true;
		}

		mx2.unlock();

		if(canAddPawn){
			mx2.lock();
			p.updatePosition(Y[0],X[0]);
			pawns.push_back(p);
			mx2.unlock();

			mx1.lock();
			X.erase(X.begin());
			Y.erase(Y.begin());
			mx1.unlock();
		}

		this_thread::sleep_for(chrono::seconds(1));
	}

}

void draw(vector<int> *Xx, vector<int> *Yy, int numberOfCollumns, int numberOfRows){
	while(true){
		vector<int> &X = *Xx;
		vector<int> &Y = *Yy;

		mx2.lock();
		int last = pawns.size()-1;

		pawns[last].drawPawn(pawns[last].getRow(), pawns[last].getCollumn());
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

		mx2.unlock();
			refresh();
			this_thread::sleep_for(chrono::seconds(1));
			endwin();
	}

}


int main(){


	vector<int> XCoordinates;
	vector<int> YCoordinates;
	//------------------------------- Create Range -------------------------------------------
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(6,16);

	int numberOfCollumns = dis(gen);
	int numberOfRows = dis(gen);

	//------------------------------- Draw Matrix -------------------------------------------
	Matrix m;
	m.DrawMatrix(numberOfCollumns,numberOfRows);


	//------------------------------- Start threads -----------------------------------------
	thread fillQueuesThread(addRandomCoordinatesToQueues,&XCoordinates,&YCoordinates,numberOfCollumns,numberOfRows);
	thread addPawnThread(addPawn,&XCoordinates,&YCoordinates,numberOfCollumns,numberOfRows);
	thread drawThread(draw,&XCoordinates,&YCoordinates,numberOfCollumns,numberOfRows);

	fillQueuesThread.join();
	addPawnThread.join();
	drawThread.join();

	return 0;
}
