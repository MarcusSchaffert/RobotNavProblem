#pragma 
#include <iostream>
#include <fstream>
#include <string>
#include <cctype> // check if char is an integer
#include <sstream>
#include <queue>
using namespace std;
class Grid
{
public:
	Grid();
	struct geography {
		int x, y;
		string information;
	};
	vector<vector<int>> wholeGrid;
	queue<geography> newQueue;
	void ProccessFile(int* intArray);
	int gridRows, gridColumns, initialLocation, goalState1, goalState2;
	unsigned char fileLetters;
	int counter, iteratorTest;


private:
	
};
