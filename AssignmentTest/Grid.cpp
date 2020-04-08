#include "Grid.h"


Grid::Grid(int sr, int sc, int sizeColumns, int sizeRows, int intArray[], int arraySize, int g1c, int g1r, int g2c, int g2r) : gridMatrix(sizeColumns, vector<int>(sizeRows)), visited(sizeColumns, vector<bool>(sizeRows)), valueGridMatrix(sizeColumns, vector<int>(sizeRows))
{


	// getting starting locations
	startingRow = sr;
	startingColumn = sc;
	// getting goal locations
	goal1C = g1c;
	goal1R = g1r;
	goal2C = g2c;
	goal2R = g2r;
	// setting the starting position to a 5
	SetPositionValue(5, sc, sr);
	// initialising the main gridMatrix 
	InitialiseMatrix(intArray, arraySize);

	// used for determining the value Matrix 
	distanceAwayRowG1 = 0; 
	distanceAwayColumnG1 = 0;
	distanceAwayRowG2 = 0;
	distanceAwayColumnG2 = 0;
	// copying the value of the main gridMatrix into the valueGridMatrix
	CopyMatrix(valueGridMatrix);


}


void Grid::ResetVisitedMatrix()
{
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			visited[i][j] = false;
		}
	}
}

void Grid::ResetGridMatrix()
{
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			gridMatrix[i][j] = 0;
		}
	}
}

void Grid::PrintMatrix()
{
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			cout << gridMatrix[i][j];

		}
		cout << "" << endl;
	}
}

void Grid::InitialiseMatrix(int intTest[], int arraySize)
{
	//gridMatrix[1][1] = 9;
	// set the inital location of the player, mark it with a 5
	gridMatrix[startingColumn][startingRow] = 5;
	// counter used for the second for loop
	int counter = 0;
	// Loop for determining where the walls are in the grid 
	for (int i = 0; i < 7; i++)
	{
		// setting goal state 
		if (i == 4)
		{
			gridMatrix[intTest[i]][intTest[i + 1]] = 9;
		}
		// setting goal state 
		if (i == 6)
		{
			gridMatrix[intTest[i]][intTest[i + 1]] = 9;
		}
	}
	// arraySize - 4 because my algorithm works with the first number of the wall line 
	// it uses the first number to determine the other three numbers in that line
	// counter starting at 5 is the inital state which allows the if statement to run from the beginning
	counter = 5;
	for (int i = 8; i < arraySize - 4; i++)
	{

		// counter is incremented 
		// every 4th index of the array corresponds to a different set of coordinates for walls
		counter++;
		if (counter > 4)
		{
			gridMatrix[intTest[i]][intTest[i + 1]] = 3;


			// we are accessing each element in the array by a fixed amount such as i + 2 and i + 3 because the file format should always be the same which means these indexes should correspond to the information we want
			// e.g we are at i = 8, so i + 2 = 10. This means we are looking at the value of index 10 of intTest
			if (intTest[i + 2] > 1)
			{
				for (int j = 1; j < intTest[i + 2]; j++)
				{
					gridMatrix[intTest[i] + intTest[i + 2] - j][intTest[i + 1]] = 3;
				}
			}
			if (intTest[i + 3] > 1)
			{
				for (int j = 1; j < intTest[i + 3]; j++)
				{
					gridMatrix[intTest[i]][intTest[i + 1] + intTest[i + 3] - j] = 3;
				}
			}

			// Need a nested for loop to determine if a wall exists when the row and column locations of the wall are greater than 1 
			// with the for loops, we are saying that we want either k or j to be used for the location that has greater coordinates in either the x or y direction 
			// for example, if we have (2,1) we know that the column is 2 and row is 1, therefore the column requires more steps to get to and hence needs a bigger number (the nested for loop number will be bigger than the outer for loop's number)
			if (intTest[i + 3] > 1 && intTest[i + 2] > 1)
			{
				if (intTest[i + 3] >= intTest[i + 2])
				{
					for (int j = 1; j < intTest[i + 2]; j++)
					{
						for (int k = 1; k < intTest[i + 3]; k++)
						{
							gridMatrix[intTest[i] + intTest[i + 2] - j][intTest[i + 1] + intTest[i + 3] - k] = 3;
						}
					}
				}
				if (intTest[i + 3] <= intTest[i + 2])
				{
					for (int j = 1; j < intTest[i + 3]; j++)
					{
						for (int k = 1; k < intTest[i + 2]; k++)
						{
							gridMatrix[intTest[i] + intTest[i + 2] - k][intTest[i + 1] + intTest[i + 3] - j] = 3;
						}
					}
				}
				//Grid[intTest[i] + intTest[i + 2] - 1][intTest[i + 1] + intTest[i + 3] - 1] = 3;
			}
			counter = 1;
		}
	}

}

void Grid::CopyMatrix(vector<vector<int>>& CopyMatrix)
{
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			CopyMatrix[i][j] = gridMatrix[i][j];
		}
		cout << "" << endl;
	}
	// once the values are copied from the main grid matrix, such as start position, goals etc. we initialise the value matrix based off of those coordinates
	InitaliseValueMatrix();
}

void Grid::PrintValueMatrix()
{
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			cout << valueGridMatrix[i][j];

		}
		cout << "" << endl;
	}
}

void Grid::InitaliseValueMatrix()
{
	int counter = 0;
	// have an or if statement to check how far away from the goal a certain location is. Based off that if statement we assign that position a number 
	for (int j = 0; j < 5; j++)
	{
		// Because there's two goal states, we need to calculate the distance of our current position to both of the goal states to see which one is smaller
		// (7, 1)
		// 1-0 = 1
		// 3-2 = 1
		distanceAwayRowG1 = DetermineDistance(j, goal1R);
		distanceAwayRowG2 = DetermineDistance(j, goal2R);
		for (int i = 0; i < 11; i++)
		{
			// 7-7 = 0
			// 10 - 7 = 3
			// 0+1 = 1
			// 1+3 = 4
			distanceAwayColumnG1 = DetermineDistance(i, goal1C);
			distanceAwayColumnG2 = DetermineDistance(i, goal2C);

			if (gridMatrix[i][j] == 9)
			{
				// if i and j are a goal state then we assign that position the highest rating
				valueGridMatrix[i][j] = 15;
			}
			// we evaluate the distance of a location based off if its closer to either goal 1 or goal 2. 
			else if (distanceAwayRowG1 + distanceAwayColumnG1 >= distanceAwayRowG2 + distanceAwayColumnG2)
			{
				valueGridMatrix[i][j] = DetermineDistanceValue(distanceAwayRowG2 + distanceAwayColumnG2);
			}
			else if (distanceAwayRowG1 + distanceAwayColumnG1 <= distanceAwayRowG1 + distanceAwayColumnG1)
			{
				valueGridMatrix[i][j] = DetermineDistanceValue(distanceAwayRowG1 + distanceAwayColumnG1);
			}
			//cout << valueGridMatrix[i][j];
		}

		cout << "" << endl;
	}
}

int Grid::ReturnValueMatrixValue()
{
	return 0;
}

int Grid::DetermineDistance(int rc, int goal)
{
	if (rc > goal)
	{
		// determining how far this row is from the goal 
		return rc - goal;
	}
	if (rc < goal)
	{
		return goal - rc;
	}
	if (rc == goal)
	{
		return 0;
	}
}

int Grid::DetermineDistanceValue(int d)
{
	switch (d)
	{
	case 0:
	{
		return 15;
	}
	case 1:
	{
		return 14;
	}
	case 2:
	{
		return 13;
	}
	case 3:
	{
		return 12;
	}
	case 4:
	{
		return 11;
	}
	case 5:
	{
		return 10;
	}
	case 6:
	{
		return 9;
	}
	case 7:
	{
		return 8;
	}
	case 8:
	{
		return 7;
	}
	case 9:
	{
		return 6;
	}
	case 10:
	{
		return 5;
	}
	case 11:
	{
		return 4;
	}
	case 12:
	{
		return 3;
	}
	case 13:
	{
		return 2;
	}
	case 14:
	{
		return 1;
	}
	case 15:
	{
		return 0;
	}

	}
	return 0;
}

int Grid::getPositionValue(int column, int row)
{
	return gridMatrix[column][row];
}

void Grid::SetPositionValue(int value, int column, int row)
{
	gridMatrix[column][row] = value;
}

bool Grid::getVisitedValue(int column, int row)
{
	return visited[column][row];
}

void Grid::SetVisitedValue(bool value, int column, int row)
{
	visited[column][row] = value;
}

vector<vector<int>> Grid::getValueMatrix()
{
	return valueGridMatrix;
}


