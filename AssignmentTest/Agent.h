#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <cstdlib>
#include <stack>
using namespace std;
class Agent
{
public: 
	int column, row, v, w, rm, cm, startingRow, startingColumn, pathCounter;
	string result;

	int randomNum = 0;
	bool completePathFound = false;
	bool deadEnd = false;
	bool moveMade = false;
	// 0 equals not visited and 1 equals visited
	vector<vector<bool>> visited;
	vector<vector<int>> Grid;
	vector<vector<int>> GridCopy;
	vector<string> Path; 
	int counterToGoal;
	// For moving up or down a row in the matrix
	// up, left, down, right
	int Move[4] = { -1, -1, 1, 1 };
	// for moving left or right between columns in the matrix 
	int moveColumn[4] = { -1 , 1, 0, 0 };
	queue<int> rowQueue;
	queue<int> columnQueue;

	// Stacks used as LIFO queues
	stack<int> rowQueueLIFO;
	stack<int> columnQueueLIFO;



	int stepsTaken;
	Agent(int c, int r, int sr, int sc);
	void moveAgent();
	void InitialiseMatrix(int intArray[], int arraySize);
	void PathToGoal();

	string BreadthFirstSearch();
	string DepthFirstSearch();
	void ResetVisitedMatrix();
	void ResetGridMatrix();
	void PrintMatrix();
	void InitialiseCoordinates();
	void ResetMatrix();

};
