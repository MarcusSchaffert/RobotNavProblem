#include "Agent.h"

Agent::Agent(int c, int r, int sr, int sc) : visited(c, vector<bool>(r)), Grid(c, vector<int>(r))
{

	//start
	startingColumn = sc;
	startingRow = sr;

	// row move and column move 
	rm = 0;
	cm = 0;
	// starting column 
	column = sc;
	// starting row
	row = sr;
	stepsTaken = 0;
	ResetVisitedMatrix();

	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			Grid[i][j] = 0;
		}
	}
	DFSCounter = 0;

	// 5 signifies the starting location 
	Grid[column][row] = 5;

	counterToGoal == 0;
}

string Agent::DepthFirstSearch()
{
	cout << "DFS" << endl;
	cout << " " << endl;
	// always reset matrices before using them 
	ResetGridMatrix();
	ResetVisitedMatrix();
	InitialiseCoordinates();
	// mark inital location as visited 

	visited[column][row] = true;
	rowQueueLIFO.push(row);
	columnQueueLIFO.push(column);

	rm = row;
	cm = column;
	while (rowQueueLIFO.size() > 0)
	{
		row = rowQueueLIFO.top();
		rowQueueLIFO.pop();
		column = columnQueueLIFO.top();
		columnQueueLIFO.pop();

		// goal is found - goal state marked with integer value 1
		if (GoalFound(column, row))
		{
			//result = "Goal found " + stepsTaken;
			//return result;

			cout << "Path to goal" << endl;
			cout << " " << endl;
			PathToGoal();
			PrintPath();
			return "Goal found ";
		}

		// we indicate movement by changing the value of the matrix position to 1 from 0
		if (Grid[column][row] != 5)
		{
			Grid[column][row] = 1;
		}


		// cout the grid to show how the agent is moving through the matrix

		PrintMatrix();

		cout << "" << endl;
		DFSCounter = 0;
		MoveAgentDFS();
	}
	cout << "my current locaiton is " << column << row << endl;
	return "failure";

}

void Agent::ResetVisitedMatrix()
{
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			visited[i][j] = false;
		}
	}
}

void Agent::ResetGridMatrix()
{
//	Grid = InitialiseMatrix(GridCopy);
}

void Agent::PrintMatrix()
{
	// cout the grid to show how the agent is moving through the matrix

	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			cout << Grid[i][j];

		}
		cout << "" << endl;
	}
}

void Agent::InitialiseCoordinates()
{
	row = startingRow;
	column = startingColumn;
}

void Agent::ResetMatrix()
{
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			Grid[i][j] = 0;
		}
	}
}

void Agent::PrintPath()
{
	for (int i = 0; i < Path.size(); i++)
	{
		cout << Path[i] << " ";
	}
}

void Agent::MoveAgentDFS()
{
	moveMade = false;


	for (int i = 0; i < 4; i++)
	{
		

		// for DFS we want to initially set the rm and cm variables to row and column respectively (the locations that were just popped off the stack). This means we are starting from a node to see if it will go any deeper.
		// However, if a move was made, this function is called recursively which means we are continuing on a path which goes deeper. This requires us to set the row and column to rm and cm respectively.
		if (DFSCounter < 1)
		{
			rm = row;
			cm = column;
		}
		else
		{
			row = rm;
			column = cm;
		}
		DFSCounter++;
		// move up 
		if (i == 0)
		{
			if (row + Move[i] < 0)
				continue;
			rm += Move[i];
		}
		// move left
		if (i == 1)
		{
			if (column + Move[i] < 0)
				continue;
			cm += Move[i];
		}
		// move down 
		if (i == 2)
		{
			if (row + Move[i] > 4)
				continue;
			rm += Move[i];
		}
		// move right 
		if (i == 3)
		{
			if (column + Move[i] > 10)
				continue;
			cm += Move[i];
		}

		if (visited[cm][rm] == true)
		{
			// undo changes that were made 
			cm = column;
			rm = row;
			continue;
		}
		// a 3 means a block which can't be entered
		if (Grid[cm][rm] == 3)
		{
			cm = column;
			rm = row;
			continue;
		}
		// moveMade means a valid move was made to progress the agent
		moveMade = true;
		/*
		rowQueue.push(rm);
		columnQueue.push(cm);
		*/
		rowQueueLIFO.push(rm);
		columnQueueLIFO.push(cm);
		visited[cm][rm] = true;
		stepsTaken++;
		if (moveMade)
		{
			if (GoalFound(cm, rm))
			{
				break;
			}
			// we indicate movement by changing the value of the matrix position to 1 from 0
			if (Grid[cm][rm] != 5)
			{
				Grid[cm][rm] = 1;
			}
			PrintMatrix();
			cout << "" << endl;
			// recursive call
			MoveAgentDFS();
		}

	}
	/*
	// if a move was not made in the previous turn, then it is considered a dead end and marked with a 4
	if (!moveMade)
	{
		deadEnd = true;
		// because the current location didn't progess the player, it is considered a deadend and is set to 4 
		Grid[column][row] = 4;
		deadEnd = false;

	}
	*/



}

bool Agent::GoalFound(int column, int row)
{
	return Grid[column][row] == 9;
}

// week 3 
string Agent::BreadthFirstSearch()
{
	// always reset matrices before using them 
	ResetGridMatrix();
	ResetVisitedMatrix();
	InitialiseCoordinates();
	// mark inital location as visited 

	visited[column][row] = true;
	rowQueue.push(row);
	columnQueue.push(column);
	while (rowQueue.size() > 0)
	{
		row = rowQueue.front();
		rowQueue.pop();
		column = columnQueue.front();
		columnQueue.pop();

		// goal is found - goal state marked with integer value 1
		if (Grid[column][row] == 9)
		{
			//result = "Goal found " + stepsTaken;
			//return result;

			cout << "Path to goal" << endl;
			cout << " " << endl;
			PathToGoal();
			PrintPath();
			return "Goal found ";
		}
		// we indicate movement by changing the value of the matrix position to 1 from 0
		if (Grid[column][row] != 5)
		{
			Grid[column][row] = 1;
		}
		PrintMatrix();

		cout << "" << endl;
		moveAgent();
	}
	cout << "my current locaiton is " << column << row << endl;
	return "failure";
}
// week 3
void Agent::moveAgent()
{
	moveMade = false;

	for (int i = 0; i < 4; i++)
	{
		// always set rm and cm to the current node of column and row
		// this allows the node to be used as a starting position to see which neighbouring nodes can be accessed
		rm = row;
		cm = column;
		// move up 
		if (i == 0)
		{
			if (row + Move[i] < 0)
				continue;
			rm +=  Move[i];
		}
		// move left
		if (i == 1)
		{
			if (column + Move[i] < 0)
				continue;
			cm+= Move[i];
		}
		// move down 
		if (i == 2)
		{
			if (row + Move[i] > 4)
				continue;
			rm += Move[i];
		}
		// move right 
		if (i == 3)
		{
			if (column + Move[i] > 10)
				continue;
			cm += Move[i];
		}

		if (visited[cm][rm] == true)
			continue;
		// a 3 means a block which can't be entered
		if (Grid[cm][rm] == 3)
			continue;
		// moveMade means a valid move was made to progress the agent
		moveMade = true;
		rowQueue.push(rm);
		columnQueue.push(cm);
	
		visited[cm][rm] = true;
		stepsTaken++;
		
	}
	// if a move was not made in the previous turn, then it is considered a dead end and marked with a 4
	if (!moveMade)
	{
		deadEnd = true;
		// because the current location didn't progess the player, it is considered a deadend and is set to 4 
		Grid[column][row] = 4;
		deadEnd = false;

	}

}


// week 3
void Agent::InitialiseMatrix(int intTest[], int arraySize)
{
	// set the inital location of the player, mark it with a 5
	Grid[startingColumn][startingRow] = 5;
	// counter used for the second for loop
	int counter = 0; 
	// Loop for determining where the walls are in the grid 
	for (int i = 0; i < 7; i++)
	{
		// setting goal state 
		if (i == 4)
		{
			Grid[intTest[i]][intTest[i + 1]] = 9;
		}
		// setting goal state 
		if (i == 6)
		{
			Grid[intTest[i]][intTest[i + 1]] = 9;
		}
	}
	// arraySize - 4 because my algorithm works with the first number of the wall line 
	// it uses the first number to determine the other three numbers in that line
	// counter starting at 5 is the inital state which allows the if statement to run from the beginning
	counter = 5;
		for(int i = 8; i < arraySize - 4; i++)
		{

		// counter is incremented 
		// every 4th index of the array corresponds to a different set of coordinates for walls
		counter++;
		if (counter > 4)
		{
			Grid[intTest[i]][intTest[i + 1]] = 3;


			// we are accessing each element in the array by a fixed amount such as i + 2 and i + 3 because the file format should always be the same which means these indexes should correspond to the information we want
			// e.g we are at i = 8, so i + 2 = 10. This means we are looking at the value of index 10 of intTest
			if (intTest[i + 2] > 1)
			{
				for (int j = 1; j < intTest[i + 2]; j++)
				{
					Grid[intTest[i] + intTest[i + 2] - j][intTest[i + 1]] = 3;
				}
			}
			if (intTest[i + 3] > 1)
			{
				for (int j = 1; j < intTest[i + 3]; j++)
				{
					Grid[intTest[i]][intTest[i + 1] + intTest[i + 3] - j] = 3;
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
							Grid[intTest[i] + intTest[i + 2] - j][intTest[i + 1] + intTest[i + 3] - k] = 3;
						}
					}
				}
				if (intTest[i + 3] <= intTest[i + 2])
				{
					for (int j = 1; j < intTest[i + 3]; j++)
					{
						for (int k = 1; k < intTest[i + 2]; k++)
						{
							Grid[intTest[i] + intTest[i + 2] - k][intTest[i + 1] + intTest[i + 3] - j] = 3;
						}
					}
				}
				//Grid[intTest[i] + intTest[i + 2] - 1][intTest[i + 1] + intTest[i + 3] - 1] = 3;
			}
			counter = 1;
			}
		}

		GridCopy = Grid;

}

// week 4 
void Agent::PathToGoal()
{
	rm = startingRow;
	cm = startingColumn;

	while (!completePathFound)
	{
		ResetVisitedMatrix();
		// Starting position equals visited 
		visited[cm][rm] = true;

		for (int i = 0; i < stepsTaken; i ++)
		{

			// move up
			if (rm != 0  && visited[cm][rm - 1] == false)
			{
				if (Grid[cm][rm - 1] == 1 || Grid[cm][rm - 1] == 9)
				{
					Path.push_back("UP");
					rm--;
					visited[cm][rm] = true;
					moveMade = true;
				}
			}

			// move left
			if (cm != 0 && visited[cm - 1][rm] == false)
			{
				if (Grid[cm - 1][rm] == 1 || Grid[cm - 1][rm] == 9)
				{
					Path.push_back("LEFT");
					cm--;
					visited[cm][rm] = true;
					moveMade = true;
				}
			}

			// move down
			if (rm != 4 && visited[cm][rm + 1] == false)
			{
				if (Grid[cm][rm + 1] == 1 || Grid[cm][rm + 1] == 9)
				{
					Path.push_back("DOWN");
					rm++;
					visited[cm][rm] = true;
					moveMade = true;
				}
			}

			// move right
			if (cm != 10 && visited[cm +1][rm] == false)
			{
				if (Grid[cm + 1][rm] == 1 || Grid[cm + 1][rm] == 9)
				{
					Path.push_back("RIGHT");
					cm++;
					visited[cm][rm] = true;
					moveMade = true;
				}
			}

			if (Grid[cm][rm] == 9)
			{
				// if we have reached the goal then break so the for loop no longer continues. 
				// since completePathFound is now true, the while loop will stop 
				completePathFound = true;
				break;
			}
			
			// if there's a deadend then mark that end with a 0
			if (!moveMade)
			{
			
					if (!completePathFound)
					{
						Path.clear();
					}
		

				// if there was no move made and the column and row is not the starting position, then mark that space with a zero
				// 5 signifies the starting position 
				if (Grid[cm][rm] != 5)
				{
						Grid[cm][rm] = 0;

				}

				PrintMatrix();
				cout << "" << endl;
					break;
			}

			moveMade = false;
		}

		rm = startingRow;
		cm = startingColumn;
		/*
		if (!completePathFound)
		{
			for (int i = 0; i < Path.size(); i++)
			{
				// remove all elements from vector because the path was not valid
				cout << Path[i] << " ";
				Path.pop_back();
			}
		}
		else
		{
			for (int i = 0; i < Path.size(); i++)
			{
				// remove all elements from vector because the path was not valid
				cout << Path[i] << " ";
			}
		}

		*/
		/*
		for (int j = startingRow; j < 5; j++)
		{
			for (int i = startingColumn; i < 11; i++)
			{
				if (rm < 0)
					break;
				if (cm < 0)
					break;
				if (cm > 10)
					break;
				if (rm > 4)
					break;
				// ignore all spaces that aren't valid 
				if (Grid[i][j] != 1)
					continue;
				// ignore all spaces that aren't valid 
				if (Grid[i][j] != 1)
					continue;


				// gives a random number from 1 - 4
				randomNum = (rand() % 4) + 1;

				// move down
				if (Grid[i + 1][j] == 1 && randomNum == 1)
				{
					Path.push_back("UP");
					rm--;
				}
				
			}
		}
		*/
	}
	ResetVisitedMatrix();

	// run a loop to get a path based off if a grid location is marked with one
	// this makes a string of moves (right, left, up, down ....)


	// make a int vector of vectors that keeps track of the move made and 
	// in this method we computer the coordinates based off the move and then check if those coordinates are a goal state 
	// 

	// mark 2 if we are getting closer to goal 
	// consider if there's walls: if so a move can be seen as neutral 
}
	
	//vector<vector<int>> Grid, int intArray[] (was added to constructor originally)