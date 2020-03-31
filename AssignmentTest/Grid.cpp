#include "Grid.h"


Grid::Grid()
{
	counter = 0;
	newQueue.push({ 1, 2, "Hello" });

}


void Grid::ProccessFile(int* intArray)
{
	// Initialising the Grid variables
	gridRows = intArray[0];
	gridColumns = intArray[1];
	// Initial state of the player 
	wholeGrid[intArray[2]][intArray[3]] = 1;

	// Goal states for the agent 
	wholeGrid[intArray[4]][intArray[5]] = 7;
	wholeGrid[intArray[6]][intArray[7]] = 7;
}