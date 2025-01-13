#include <iostream>

#define rows 6
#define cols 6

// Function prototypes

// Initialize the scanning wall array
// The scanning wall array is a 2D array of integers that used to scan the walls of the maze
// The scanning wall array is of size (2*rows + 1) x (cols + 1)
int** initScanWallArray(int r, int c);

// Initializing the flood fill array
// The flood fill array is a 2D array of integers that used to flood fill the maze
// The flood fill array is of size rows x cols
int** initFloodFillArray(int r, int c, int val);

// Define Wall array dimensions
const int wallRows = (2 * rows) + 1;
const int wallCols = cols + 1;

// Defining target positions
const int targetRows1 = 4, targetRows2 = 5;
const int targetCols1 = 4, targetCols2 = 5;

// User define Wall array
const int wallArray[wallRows][wallCols] = { { 1, 1, 1, 1, 1, 1, 0 },
                                            { 1, 0, 0, 0, 0, 0, 1 }, 
                                            { 0, 1, 1, 0, 1, 1, 0 }, 
                                            { 1, 1, 0, 1, 1, 0, 1 }, 
                                            { 0, 0, 0, 0, 0, 0, 0 }, 
                                            { 1, 1, 1, 0, 1, 0, 1 },
                                            { 0, 0, 0, 1, 0, 0, 0 }, 
                                            { 1, 1, 1, 1, 0, 1, 1 }, 
                                            { 0, 0, 0, 0, 0, 0, 0 }, 
                                            { 1, 1, 0, 1, 0, 1, 1 }, 
                                            { 1, 1, 0, 1, 1, 0, 0 }, 
                                            { 1, 0, 1, 0, 0, 0, 1 }, 
                                            { 1, 1, 1, 1, 1, 1, 0 } };

// User define Wall arrays that can be used to test the code
/*const int wallArray[wallRows][wallCols] = { { 1, 1, 1, 1, 1, 1, 0 },
                                            { 1, 0, 0, 0, 0, 0, 1 }, 
                                            { 0, 0, 0, 0, 0, 0, 0 }, 
                                            { 1, 0, 0, 0, 0, 0, 1 }, 
                                            { 0, 0, 0, 0, 0, 0, 0 }, 
                                            { 1, 0, 0, 0, 0, 0, 1 },
                                            { 0, 0, 0, 0, 0, 0, 0 }, 
                                            { 1, 0, 0, 0, 0, 0, 1 }, 
                                            { 0, 0, 0, 0, 0, 0, 0 }, 
                                            { 1, 0, 0, 0, 0, 0, 1 }, 
                                            { 0, 0, 0, 0, 0, 0, 0 }, 
                                            { 1, 0, 0, 0, 0, 0, 1 }, 
                                            { 1, 1, 1, 1, 1, 1, 0 } };*/

// Defining initial position
int micePosRow = 0, micePosCol = 0, miceDir = 0;

// Defining status of the maze solver
bool boolStatus = true;

using namespace std;

int main(void) {

	// Initialize the scanning wall array
	int** scanWallArray = initScanWallArray(wallRows, wallCols);
	if (scanWallArray == NULL) 
	{
		cout << "Memory allocation failed for Scan Wall Array" << endl;
		return 1;
	}

	while (boolStatus == true) {

		// defining and re defining access array
		int** accArray = initFloodFillArray(rows, cols, 0);
		if (accArray == NULL) 
		{
			cout << "Memory allocation failed for Access Array" << endl;
			return 1;
		}

		// defining and re defining edit array
		int** editArray = initFloodFillArray(rows, cols, -1);
		if (editArray == NULL) 
		{
			cout << "Memory allocation failed for Edit Array" << endl;
			return 1;
		}

		// Filling the scan wall array with the wall array data
		// Only the walls around the mice position are filled
		// Stored wall data is not changed
		scanWallArray[(micePosRow * 2) + 1][micePosCol + 1] = wallArray[(micePosRow * 2) + 1][micePosCol + 1];
		scanWallArray[(micePosRow * 2) + 2][micePosCol] = wallArray[(micePosRow * 2) + 2][micePosCol];
		scanWallArray[(micePosRow * 2) + 1][micePosCol] = wallArray[(micePosRow * 2) + 1][micePosCol];
		scanWallArray[(micePosRow * 2)][micePosCol] = wallArray[(micePosRow * 2)][micePosCol];

		// Flood fill the maze
		// The flood fill array is filled with the number of steps to reach the target
		int steps = 0;
		int prevSteps = 0;
		do {
			prevSteps = steps;
			for (int i = 0; i < rows; i++) 
			{
				for (int j = 0; j < cols; j++) 
				{
					if (accArray[i][j] == 1) // If the position is accessed
					{
						if (scanWallArray[(i * 2) + 1][j + 1] == 0 && accArray[i][j + 1] == 0) // If the right position is not coverd by a wall and not accessed
						{
							accArray[i][j + 1] = 1; // Set the position as accessed
							editArray[i][j + 1] = editArray[i][j] + 1; // Set the number of steps to reach the position
							steps ++;
						}
						if (scanWallArray[(i * 2) + 2][j] == 0 && accArray[i + 1][j] == 0) // If the bottom position is not coverd by a wall and not accessed
						{
							accArray[i + 1][j] = 1;
							editArray[i + 1][j] = editArray[i][j] + 1;
							steps ++;
						}
						if (scanWallArray[(i * 2) + 1][j] == 0 && accArray[i][j - 1] == 0) // If the left position is not coverd by a wall and not accessed
						{
							accArray[i][j - 1] = 1;
							editArray[i][j - 1] = editArray[i][j] + 1;
							steps ++;
						}
						if (scanWallArray[(i * 2)][j] == 0 && accArray[i - 1][j] == 0) // If the top position is not coverd by a wall and not accessed
						{
							accArray[i - 1][j] = 1;
							editArray[i - 1][j] = editArray[i][j] + 1;
							steps ++;
						}
					}
				}
			}
		}
		while (steps != prevSteps); // If the number of steps is not changed, the maze is fully accessed

		// Jumping to the next position
		// The position with the least number of steps is selected
		// If the position is not accessible (not covered by awall), the position with the next least number of steps is selected
		if (scanWallArray[(micePosRow * 2) + 1][micePosCol + 1] == 0 && editArray[micePosRow][micePosCol + 1] < editArray[micePosRow][micePosCol])
		{
			micePosCol += 1;
		} 
		else if (scanWallArray[(micePosRow * 2) + 2][micePosCol] == 0 && editArray[micePosRow + 1][micePosCol] < editArray[micePosRow][micePosCol]) 
		{
			micePosRow += 1;
		} 
		else if (scanWallArray[(micePosRow * 2) + 1][micePosCol] == 0 && editArray[micePosRow][micePosCol - 1] < editArray[micePosRow][micePosCol]) 
		{
			micePosCol -= 1;
		} 
		else if (scanWallArray[(micePosRow * 2)][micePosCol] == 0 && editArray[micePosRow - 1][micePosCol] < editArray[micePosRow][micePosCol]) 
		{
			micePosRow -= 1;
		}

		// Printing the path
		cout << "Mice Position: " << micePosRow << " " << micePosCol << endl;

		// Checking if the mice has reached the target
		if (editArray[micePosRow][micePosCol] != 0) {
			boolStatus = true;
		} else {
			boolStatus = false;
		}

		// Freeing the allocated memory
		free(accArray);
		free(editArray);
	}
}

int** initScanWallArray(int r, int c) 
{
	// Allocate memory for the scanning wall array
	int **array = (int**)malloc(r * sizeof(int *));
	if (array == NULL) 
	{
		return array;
	}
	for (int i = 0; i < r; i++) 
	{
		array[i] = (int*)malloc(c * sizeof(int));
		if (array[i] == NULL) 
		{
			for (int k = 0; k < i; ++k) 
			{
				// Free allocated rows before returning
				free(array[k]);
			}
			free(array);
			return array;
		}
	}

	// Defining boundry walls in the array
	for (int i = 0; i < ((2 * rows) + 1); i++) 
	{
		for (int j = 0; j < cols + 1; j++) 
		{
			if (i == 0 || i == 2 * rows) 
			{
				if (j == cols) 
				{
					array[i][j] = 0;
				} 
				else
				{
					array[i][j] = 1;
				}
			}
			else if (i % 2 != 0) 
			{
				if (j == 0 || j == cols) 
				{
					array[i][j] = 1;
				} 
				else
				{
					array[i][j] = 0;
				}
			} 
			else 
			{
				array[i][j] = 0;
			}
		}
	}

	return array;
}

int** initFloodFillArray(int r, int c, int val) 
{
	// Allocate memory for the flood fill array
	int **array = (int**)malloc(r * sizeof(int *));
	if (array == NULL) 
	{
		return array;
	}
	for (int i = 0; i < r; i++) 
	{
		array[i] = (int*)malloc(c * sizeof(int));
		if (array[i] == NULL) 
		{
			for (int k = 0; k < i; ++k) 
			{
				// Free allocated rows before returning
				free(array[k]);
			}
			free(array);
			return array;
		}
	}

	// Initialize the flood fill array with zeros
	for (int i = 0; i < r; i++) 
	{
		for (int j = 0; j < c; j++) 
		{
			array[i][j] = val;
		}
	}

	array[targetRows1 - 1][targetCols1 - 1] += 1;
	array[targetRows1 - 1][targetCols2 - 1] += 1;
	array[targetRows2 - 1][targetCols1 - 1] += 1;
	array[targetRows2 - 1][targetCols2 - 1] += 1;
	
	return array;
}