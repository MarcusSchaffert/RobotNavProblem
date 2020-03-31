// AssignmentTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cctype> // check if char is an integer
#include <sstream>
#include "Grid.h"
#include <vector>
#include "Agent.h"
#include <ctime>
using namespace std;

struct Test
{
	int x, y, width, height;
	string description;
};

int main()
{
	srand(time(NULL));
	ifstream fileOpen("AssignmentGrid.txt");
	 unsigned char fileLetters;
	int intTest[38];
	int counter = 0;
	int iteratorTest = 0;
	Grid myGrid;

	// week 1 
	if (!fileOpen.good())
	{
		cout << "Can't open file" << endl;
		return 2;
	}

	while (fileOpen >> fileLetters)
	{
		// Checking if the file character is an integer
		if (isdigit(fileLetters))
		{
			// If the counter is greater than 1 it must mean that the integer is double digits 
			if (counter >= 1)
			{
				// Times the previous number by ten then add the current number in the file
				intTest[iteratorTest - 1] = intTest[iteratorTest - 1] * 10;
				intTest[iteratorTest - 1] += (int)fileLetters - 48;

				counter = 0;
			}
			else
			{
				// minus 48 because integer characters start from 48 in ASCII
				intTest[iteratorTest] = (int)fileLetters - 48;
				//cout << intTest[iteratorTest] << endl;
				counter++;
				iteratorTest++;
			}
		}
		else
		{
			// If the character isn't a digit then the counter sets back to zero
			// Ensures that double digit numbers are assessed as well
			counter = 0;
		}

	}

	int sizeofarray = 0;
	// Algorithm i found for getting the size of an index 
	sizeofarray = *(&intTest + 1) - intTest;
	
	// Creates a vector of vectors 
	vector<vector<int>> wholeGrid(intTest[1], vector<int>(intTest[0]));

	// Sets all the values of the array 
	// i = columns 
	// j = rows
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			wholeGrid[i][j] += 0;

		}

	}

	// initialise agent with columns and rows
	Agent myAgent(intTest[1], intTest[0], intTest[3], intTest[2]);



	cout << intTest[1] << endl;
	cout << intTest[2] << endl;
	cout << intTest[3] << endl;
	cout << intTest[4] << endl;
	cout << intTest[5] << endl;

	// Players initial location 
	wholeGrid[intTest[2]][intTest[3]] = 6;

	// Goal states 
	wholeGrid[intTest[4]][intTest[5]] = 7;
	wholeGrid[intTest[6]][intTest[7]] = 7;


	// week 2 

	/*
	// Loop for determining where the walls are in the grid 
	for (int i = 0; i < 36; i++)
	{
		if (i == 8)
		{
			wholeGrid[intTest[i]][intTest[i + 1]] = 3;
			// intTest10 stands for width 
			if (intTest[10] > 1)
			{
				cout << intTest[10] << endl;
				// intTest[9] = 0
				// + intTest[10] = 2
				// - 1
				// = 1
				// This means that the position (2, 1) should now equal 3 which means it is a blocked path
				wholeGrid[intTest[i] + intTest[10] - 1][intTest[i + 1]] = 3;
			}
			if (intTest[11] > 1)
			{
				wholeGrid[intTest[i]][intTest[i + 1] + intTest[11] - 1] = 3;
			}
			if (intTest[11] > 1 && intTest[10] > 1)
			{
				wholeGrid[intTest[i] + intTest[10] - 1][intTest[i + 1] + intTest[11] - 1] = 3;
			}
		}
		if (i == 12)
		{
			wholeGrid[intTest[i]][intTest[i + 1]] = 3;

			// inttest14 = 1
			if (intTest[14] > 1)
			{
				wholeGrid[intTest[i] + intTest[14] - 1][intTest[i + 1]] = 3;
			}
			// inttest15 = 2 
			cout << intTest[12] << endl;
			if (intTest[15] > 1)
			{
				wholeGrid[intTest[i]][intTest[i + 1] + intTest[15] - 1] = 3;
			}

			if (intTest[14] > 1 && intTest[15] > 1)
			{
				wholeGrid[intTest[i] + intTest[15] - 1][intTest[i + 1] + intTest[14] - 1] = 3;
			}
			

		}

		if (i == 16)
		{
			wholeGrid[intTest[i]][intTest[i + 1]] = 3;
			// inttest14 = 1
			if (intTest[18] > 1)
			{
				wholeGrid[intTest[i] + intTest[18] - 1][intTest[i + 1]] = 3;
			}
			// inttest15 = 2 
			cout << intTest[12] << endl;
			if (intTest[19] > 1)
			{
				wholeGrid[intTest[i]][intTest[i + 1] + intTest[19] - 1] = 3;
			}

			if (intTest[18] > 1 && intTest[19] > 1)
			{
				wholeGrid[intTest[i] + intTest[18] - 1][intTest[i + 1] + intTest[19] - 1] = 3;
			}

		}

		if (i == 20)
		{
			wholeGrid[intTest[i]][intTest[i + 1]] = 3;
			// inttest14 = 1
			if (intTest[22] > 1)
			{
				wholeGrid[intTest[i] + intTest[22] - 1][intTest[i + 1]] = 3;
			}
			// inttest15 = 2 
			if (intTest[23] > 1)
			{
				wholeGrid[intTest[i]][intTest[i + 1] + intTest[23] - 1] = 3;
			}

			if (intTest[22] > 1 && intTest[23] > 1)
			{
				wholeGrid[intTest[i] + intTest[22] - 1][intTest[i + 1] + intTest[23] - 1] = 3;
			}
		}

		if (i == 24)
		{
			wholeGrid[intTest[i]][intTest[i + 1]] = 3;
			// inttest14 = 1
			if (intTest[26] > 1)
			{
				wholeGrid[intTest[i] + intTest[26] - 1][intTest[i + 1]] = 3;

				// Special consideration because this wall has a width of 3
				wholeGrid[intTest[i] + intTest[26] - 2][intTest[i + 1]] = 3;
			}
			// inttest15 = 2 
			if (intTest[27] > 1)
			{
				wholeGrid[intTest[i]][intTest[i + 1] + intTest[27] - 1] = 3;
			}

			if (intTest[26] > 1 && intTest[27] > 1)
			{
				wholeGrid[intTest[i] + intTest[26] - 1][intTest[i + 1] + intTest[27] - 1] = 3;
			}
		}

		if (i == 28)
		{
			wholeGrid[intTest[i]][intTest[i + 1]] = 3;
			// inttest14 = 1
			if (intTest[30] > 1)
			{
				wholeGrid[intTest[i] + intTest[30] - 1][intTest[i + 1]] = 3;
			}
			// inttest15 = 2 
			if (intTest[31] > 1)
			{
				wholeGrid[intTest[i]][intTest[i + 1] + intTest[31] - 1] = 3;
			}

			if (intTest[30] > 1 && intTest[31] > 1)
			{
				wholeGrid[intTest[i] + intTest[30] - 1][intTest[i + 1] + intTest[31] - 1] = 3;
			}
		}

		if (i == 32)
		{
			wholeGrid[intTest[i]][intTest[i + 1]] = 3;
			// inttest14 = 1
			if (intTest[34] > 1)
			{
				wholeGrid[intTest[i] + intTest[34] - 1][intTest[i + 1]] = 3;
			}
			// inttest15 = 2 
			if (intTest[35] > 1)
			{
				wholeGrid[intTest[i]][intTest[i + 1] + intTest[35] - 1] = 3;
			}

			if (intTest[34] > 1 && intTest[35] > 1)
			{
				wholeGrid[intTest[i] + intTest[34] - 1][intTest[i + 1] + intTest[35] - 1] = 3;
			}
		}
	}
	*/
	// Determining walls 


	myAgent.InitialiseMatrix(intTest, sizeofarray);

	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			cout << myAgent.Grid[i][j];

		}
		cout << "" << endl;
	}

	cout << "" << endl;

	string answer;

	answer = myAgent.BreadthFirstSearch();

	cout << answer << endl;
	cout << myAgent.stepsTaken;

	// Setting the values of the array and cout to see if they are in the right spot 
	/*
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i <11; i++)
		{
			cout << myAgent.Grid[i][j];
			
		}
		cout <<"" << endl;
		
	}


	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			cout << myAgent.visited[i][j];

		}
		cout << "" << endl;

	}
	*/

	// Determining the digits in the intTest[] array
	/*
	for (int i = 0; i < 36; i++)
	{
		cout << intTest[i];
	}
	*/

	for (int i = 0; i < myAgent.Path.size(); i++)
	{
		cout << myAgent.Path[i] << " ";
	}


	
	fileOpen.close();




	
}
