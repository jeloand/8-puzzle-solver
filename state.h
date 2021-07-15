/**
 * Francis Anjelo M. Andes
 * Miles B. Artiaga
 * CSElec1-BSCS3B: Artificial Intelligence
**/

// typedef int[3][3] to State
typedef int State[BOARD_SIZE][BOARD_SIZE];

// boolean variables
const int true = 1, false = 0;

// states definitions
const State goalState = {
    {1, 2, 3},
    {8, 0, 4},
    {7, 6, 5}
};

const State blankState = {
    {-1, -1, -1},
    {-1, -1, -1},
    {-1, -1, -1}
};

const State easyConfiguration = {
    {1, 3, 4},
    {8, 6, 2},
    {7, 0, 5}
};

const State mediumConfiguration = {
    {2, 8, 1},
    {0, 4, 3},
    {7, 6, 5}
};

const State hardConfiguration = {
    {2, 8, 1},
    {4, 6, 3},
    {7, 5, 0}
};

const State worstConfiguration = {
    {5, 6, 7},
    {4, 0, 8},
    {3, 2, 1}
};

/**
 * This function computes for the Hamming Distance of a given state. Basically,
 * it compares the current state and the goal state. Every tile in the wrong position
 * is counted and is returned.
**/
int hammingDistance(State state)
{
    int counter = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (state[i][j] != goalState[i][j])
                counter++;
        }
    }
    return counter;
}

/**
 * This function computes for the Manhattan Distance of a given state.
 ***
 * This function is adapted from Christian (C-Collamar on GitHub) and is modified
 * to suit this program.
 * https://github.com/C-Collamar/8-Puzzle-Solver
**/
int manhattanDistance(State state)
{
    int x0, y0;
    int x1, y1;
    int sum = 0;

    for(y0 = 0; y0 < BOARD_SIZE; ++y0) {
        for(x0 = 0; x0 < BOARD_SIZE; ++x0) {
            for(y1 = 0; y1 < BOARD_SIZE; ++y1) {
                for(x1 = 0; x1 < BOARD_SIZE; ++x1) {
                    if(state[x0][y0] == goalState[x1][y1]) {
                        sum += abs(x0 - x1) + abs(y0 - y1);
                    }
                }
            }
        }
    }

    return sum;
}

/**
 *  This function returns the fValue of the current state.
**/
int fValue(State state, int heuristic)
{
    if (heuristic == 1)
        return hammingDistance(state);

    else
        return manhattanDistance(state);
}

/**
 * This function compares whether the two states inputted are identical.
**/
int isIdentical(State state1, const State state2)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (state1[i][j] != state2[i][j])
                return false;
        }
    }
    return true;
}

/**
 * This function copies the state from the source to the destination.
**/
void copyState(State destination, const State source)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            destination[i][j] = source[i][j];
        }
    }

    return;
}

/**
 * This function returns the number of inversions in a state.
 ***
 * This function is adapted from GeeksForGeeks.
 * https://www.geeksforgeeks.org/check-instance-8-puzzle-solvable/
**/
int getInvCount(int arr[])
{
    int inv_count = 0;
    for (int i = 0; i < 9 - 1; i++)
        for (int j = i+1; j < 9; j++)
             // Value 0 is used for empty space
             if (arr[j] && arr[i] &&  arr[i] > arr[j])
                  inv_count++;
    return inv_count;
}

/**
 * This function returns true if given 8 puzzle is solvable.
 ***
 * This function is adapted from GeeksForGeeks and is modified to suit the problem.
 * https://www.geeksforgeeks.org/check-instance-8-puzzle-solvable/
**/
int isSolvable(State state)
{

    int invCount = getInvCount((int *)state);

    // return true if inversion count is even.
    return (invCount % 2 == 1);
}
