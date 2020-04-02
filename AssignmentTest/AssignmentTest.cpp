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
	


	// initialise agent with columns and rows
	Agent myAgent(intTest[1], intTest[0], intTest[3], intTest[2]);




	myAgent.InitialiseMatrix(intTest, sizeofarray);


	cout << "" << endl;

	string answer;

	answer = myAgent.BreadthFirstSearch();

	cout << answer << endl;
	cout << myAgent.stepsTaken;


	
	myAgent.ResetMatrix();
	myAgent.InitialiseMatrix(intTest, sizeofarray);
	myAgent.DepthFirstSearch();
	cout << answer << endl;
	cout << myAgent.stepsTaken;


	
	fileOpen.close();




	
}
