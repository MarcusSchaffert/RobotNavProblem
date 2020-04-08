#include "Agent.h"

Agent::Agent(int c, int r, int sr, int sc, int intArray[], int arraySize, int g1c, int g1r, int g2c, int g2r) :  myAgentGrid(sr, sc, c, r, intArray, arraySize, g1c, g1r, g2c, g2r)
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
	
	DFSCounter = 0;


	counterToGoal = 0;
}

string Agent::DepthFirstSearch()
{
	cout << "DFS" << endl;
	cout << " " << endl;
	// always reset matrices before using them 
	row = myAgentGrid.getStartingRow();
	column = myAgentGrid.getStartingColumn();
	// mark inital location as visited 
	myAgentGrid.SetVisitedValue(true, column, row);
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
		if (myAgentGrid.getPositionValue(column, row) != 5)
		{
			myAgentGrid.SetPositionValue(1, column, row);
		}


		// cout the grid to show how the agent is moving through the matrix

		myAgentGrid.PrintMatrix();

		cout << "" << endl;
		DFSCounter = 0;
		MoveAgentDFS();
	}
	cout << "my current locaiton is " << column << row << endl;
	return "failure";

}

void Agent::MoveAgentDFS()
{
	moveMade = false;


	for (int i = 0; i < 4; i++)
	{
		if (GoalFound(cm, rm))
		{
			break;
		}

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
		if (!MatrixMove(column, row, i))
		{
			continue;
		}
		// Determine if the location has been visited or is a wall
		if (myAgentGrid.getVisitedValue(cm, rm) == true || myAgentGrid.getPositionValue(cm, rm) == 3)
		{
			// undo changes that were made 
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
		myAgentGrid.SetVisitedValue(true, cm, rm);
		stepsTaken++;
		if (moveMade)
		{
			if (GoalFound(cm, rm))
			{
				i = 4;
				break;
			}
			// we indicate movement by changing the value of the matrix position to 1 from 0
			if (myAgentGrid.getPositionValue(cm, rm) != 5)
			{
				myAgentGrid.SetPositionValue(1, cm, rm); 
			}
			myAgentGrid.PrintMatrix();
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



string Agent::GreedyBestFirstSearch()
{
	// always reset matrices before using them
	row = myAgentGrid.getStartingRow();
	column = myAgentGrid.getStartingColumn();
	// mark inital location as visited 

	myAgentGrid.SetVisitedValue(true, column, row);
	while (priorityQueueGFS.size() > 0)
	{
		
		

		// goal is found - goal state marked with integer value 1
		if (myAgentGrid.getPositionValue(column, row) == 9)
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
		if (myAgentGrid.getPositionValue(column, row) != 5)
		{
			myAgentGrid.SetPositionValue(1, column, row);
		}
		myAgentGrid.PrintMatrix();

		cout << "" << endl;
		MoveAgentGBFS();
	}
	cout << "my current locaiton is " << column << row << endl;
	return "failure";
}

void Agent::MoveAgentGBFS()
{
	moveMade = false;

	for (int i = 0; i < 4; i++)
	{
		// always set rm and cm to the current node of column and row
		// this allows the node to be used as a starting position to see which neighbouring nodes can be accessed
		rm = row;
		cm = column;
		// move up 

		// MatrixMove is a function which will potentially advance the agent one position. If it does, it returns true and if it doesn't it returns false
		if (!MatrixMove(column, row, i))
		{
			// if no valid move was able to be made then we skip to the next potential move
			continue;
		}

		// determines if the location of rm and cm is a wall. If so, continue and don't save that location 
		if (VisitedOrWall())
		{
			continue;
		}
		// moveMade means a valid move was made to progress the agent
		moveMade = true;

		// push the value of the coordinates of cm and rm
		priorityQueueGFS.push(myAgentGrid.getValueMatrix()[cm][rm]);
		rowQueueGFS->push_back(rm);
		columnQueueGFS->push_back(cm)

		myAgentGrid.SetVisitedValue(true, cm, rm);
		stepsTaken++;

	}
	// if a move was not made in the previous turn, then it is considered a dead end and marked with a 4
	if (!moveMade)
	{
		deadEnd = true;
		// because the current location didn't progess the player, it is considered a deadend and is set to 4 
		myAgentGrid.SetPositionValue(4, column, row);
		deadEnd = false;

	}
}




// week 3 
string Agent::BreadthFirstSearch()
{
	// always reset matrices before using them
	row = myAgentGrid.getStartingRow();
	column = myAgentGrid.getStartingColumn();
	// mark inital location as visited 

	myAgentGrid.SetVisitedValue(true, column, row);
	rowQueue.push(row);
	columnQueue.push(column);
	while (rowQueue.size() > 0)
	{
		row = rowQueue.front();
		rowQueue.pop();
		column = columnQueue.front();
		columnQueue.pop();

		// goal is found - goal state marked with integer value 1
		if (myAgentGrid.getPositionValue(column, row) == 9)
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
		if (myAgentGrid.getPositionValue(column, row) != 5)
		{
			myAgentGrid.SetPositionValue(1, column, row);
		}
		myAgentGrid.PrintMatrix();

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

		// MatrixMove is a function which will potentially advance the agent one position. If it does, it returns true and if it doesn't it returns false
		if (!MatrixMove(column, row, i))
		{
			// if no valid move was able to be made then we skip to the next potential move
			continue;
		}

		// determines if the location of rm and cm is a wall. If so, continue and don't save that location 
		if (VisitedOrWall())
		{
			continue;
		}
	
		moveMade = true;
		// method determines what search to use, hence what queue to use
			rowQueue.push(rm);
			columnQueue.push(cm);
		myAgentGrid.SetVisitedValue(true, cm, rm);
		stepsTaken++;
		
	}
	// if a move was not made in the previous turn, then it is considered a dead end and marked with a 4
	if (!moveMade)
	{
		deadEnd = true;
		// because the current location didn't progess the player, it is considered a deadend and is set to 4 
		myAgentGrid.SetPositionValue(4, column, row);
		deadEnd = false;

	}

}


// Week 5
// Used to determine if a valid move can be made within the matrix and, if so, the method will update rm and cm (row move and column move).
// rm and cm then might be put into the queue if they are not walls and if they are not already visited
bool Agent::MatrixMove(int column, int row, int i)
{

	// move up 
	if (i == 0)
	{
		if (row + Move[i] < 0)
		{

		}
		else
		{
			rm += Move[i];
			return true;
		}
	}
	// move left
	if (i == 1)
	{
		if (column + Move[i] < 0)
		{

		}
		else
		{
			cm += Move[i];
			return true;
		}
	}
	// move down 
	if (i == 2)
	{
		if (row + Move[i] > 4)
		{

		}
		else
		{
			rm += Move[i];
			return true;
		}
	}
	// move right 
	if (i == 3)
	{
		if (column + Move[i] > 10)
		{

		}
		else
		{
			cm += Move[i];
			return true;
		}
	}
	return false;

}





// week 4 
void Agent::PathToGoal()
{
	rm = startingRow;
	cm = startingColumn;

	while (!completePathFound)
	{
		myAgentGrid.ResetVisitedMatrix();
		// Starting position equals visited 
		myAgentGrid.SetVisitedValue(true, cm, rm);

		for (int i = 0; i < stepsTaken; i ++)
		{

			// move up
			if (rm != 0  && myAgentGrid.getVisitedValue(cm, rm - 1) == false)
			{
				if (myAgentGrid.getPositionValue(cm, rm - 1) == 1 || myAgentGrid.getPositionValue(cm, rm - 1)  == 9)
				{
					Path.push_back("UP");
					rm--;
					myAgentGrid.SetVisitedValue(true, cm, rm);
					moveMade = true;
				}
			}

			// move left
			if (cm != 0 && myAgentGrid.getVisitedValue(cm - 1, rm) == false)
			{
				if (myAgentGrid.getPositionValue(cm - 1, rm) == 1 || myAgentGrid.getPositionValue(cm - 1, rm) == 9)
				{
					Path.push_back("LEFT");
					cm--;
					myAgentGrid.SetVisitedValue(true, cm, rm);
					moveMade = true;
				}
			}

			// move down
			if (rm != 4 && myAgentGrid.getVisitedValue(cm, rm +1) == false)
			{
				if (myAgentGrid.getPositionValue(cm, rm + 1) == 1 || myAgentGrid.getPositionValue(cm, rm + 1) == 9)
				{
					Path.push_back("DOWN");
					rm++;
					myAgentGrid.SetVisitedValue(true, cm, rm);
					moveMade = true;
				}
			}

			// move right
			if (cm != 10 && myAgentGrid.getVisitedValue(cm + 1, rm) == false)
			{
				if (myAgentGrid.getPositionValue(cm + 1, rm) == 1 || myAgentGrid.getPositionValue(cm + 1, rm) == 9)
				{
					Path.push_back("RIGHT");
					cm++;
					myAgentGrid.SetVisitedValue(true, cm, rm);
					moveMade = true;
				}
			}

			if (myAgentGrid.getPositionValue(cm, rm) == 9)
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
				if (myAgentGrid.getPositionValue(cm, rm) != 5)
				{
						myAgentGrid.SetPositionValue(0, cm, rm);

				}

				myAgentGrid.PrintMatrix();
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
	myAgentGrid.ResetVisitedMatrix();
	// run a loop to get a path based off if a grid location is marked with one
	// this makes a string of moves (right, left, up, down ....)


	// make a int vector of vectors that keeps track of the move made and 
	// in this method we computer the coordinates based off the move and then check if those coordinates are a goal state 
	// 

	// mark 2 if we are getting closer to goal 
	// consider if there's walls: if so a move can be seen as neutral 
}
	
	//vector<vector<int>> Grid, int intArray[] (was added to constructor originally)

void Agent::PrintPath()
{
	for (int i = 0; i < Path.size(); i++)
	{
		cout << Path[i] << ", ";
	}
}

bool Agent::GoalFound(int column, int row)
{
	return myAgentGrid.getPositionValue(column, row) == 9;
}

bool Agent::VisitedOrWall()
{
	if (myAgentGrid.getVisitedValue(cm, rm) == true || myAgentGrid.getPositionValue(cm, rm) == 3)
	{
		return true;
	}
	return false;
}
