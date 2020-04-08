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
	Grid(int sr, int sc, int sizeRows, int sizeColumns, int intArray[], int arraySize, int g1c, int g1r, int g2c, int g2r);

	void ResetVisitedMatrix();
	void ResetGridMatrix();
	void PrintMatrix();
	void InitialiseMatrix(int intArray[], int arraySize);
	void CopyMatrix(vector<vector<int>>& CopyMatrix);
	void PrintValueMatrix();
	void InitaliseValueMatrix();
	int ReturnValueMatrixValue();
	int DetermineDistance(int rc, int goal);
	int DetermineDistanceValue(int d);
	int getStartingRow() { return startingRow; }
	int getStartingColumn() { return startingColumn; }
	int getPositionValue(int column, int row);
	void SetPositionValue(int value, int column, int row);
	bool getVisitedValue(int column, int row);
	void SetVisitedValue(bool value, int column, int row);
	vector<vector<int>> getValueMatrix();


private:
	int goal1C, goal1R, goal2C, goal2R, distanceAwayRowG1, distanceAwayColumnG1, distanceAwayRowG2, distanceAwayColumnG2;
	// 0 equals not visited and 1 equals visited
	vector<vector<bool>> visited;
	vector<vector<int>> gridMatrix;
	vector<vector<int>> valueGridMatrix;
	int startingRow, startingColumn;
	
};
