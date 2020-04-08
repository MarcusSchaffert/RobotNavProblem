#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <cstdlib>
#include <stack>
#include "Grid.h"
using namespace std;
class Agent
{
public: 
	int column, row, v, w, rm, cm, startingRow, startingColumn, pathCounter, DFSCounter;
	string result;

	int randomNum = 0;
	bool completePathFound = false;
	bool deadEnd = false;
	bool moveMade = false;
	// 0 equals not visited and 1 equals visited
	vector<vector<bool>> visited;
	//vector<vector<int>> Grid;
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

	// Priority Queue 
	priority_queue<int> priorityQueueGFS;
	vector<vector<int>> rowQueueGFS[50];
	vector<vector<int>> columnQueueGFS[50];

	


	int stepsTaken;
	Agent(int c, int r, int sr, int sc, int intArray[], int arraySize, int g1c, int g1r, int g2c, int g2r);
	void moveAgent();
	//void InitialiseMatrix(int intArray[], int arraySize);
	void PathToGoal();

	string BreadthFirstSearch();
	string DepthFirstSearch();
	string GreedyBestFirstSearch();
	bool MatrixMove(int column, int row, int index);
	void PrintPath();
	void MoveAgentDFS();
	void MoveAgentGBFS();
	bool GoalFound(int column, int row);
	bool VisitedOrWall();
	//Grid GetGrid();
	//void setGrid() {};
	Grid myAgentGrid;

private:
	//Grid myAgentGrid;
};
