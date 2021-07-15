/**
 * Francis Anjelo M. Andes
 * Miles B. Artiaga
 * CSElec1-BSCS3B: Artificial Intelligence
**/

// define ANSI escape sequences
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define BOLD    "\033[1m"       /* Bold */
#define CLEAR    "\33[2K"       /* clear */
#define HIDE    "\e[?25l"       /* hide cursor */

// forward declaration
void setBoardConfiguration(State state);

void printInstructions()
{
    // ASCII art from http://patorjk.com/software/taag/#p=display&f=Computer&t=8-Puzzle%0A%20%20Solver
    printf(BOLD GREEN
        "\n eeeee       8\"\"\"\"8\n"
        " 8   8       8    8 e   e eeeee eeeee e     eeee\n"
        " 8eee8       8eeee8 8   8 \"   8 \"   8 8     8\n"
        "88   88 eeee 88     8e  8 eeee8 eeee8 8e    8eee\n"
        "88   88      88     88  8 88    88    88    88\n"
        "88eee88      88     88ee8 88ee8 88ee8 88eee 88ee\n\n"
        "    8\"\"\"\"8\n"
        "    8      eeeee e    ee   e eeee eeeee\n"
        "    8eeeee 8  88 8    88   8 8    8   8\n"
        "        88 8   8 8e   88  e8 8eee 8eee8e\n"
        "    e   88 8   8 88    8  8  88   88   8\n"
        "    8eee88 8eee8 88eee 8ee8  88ee 88   8\n\n" RESET);

    printf(
        "This program finds the optimal solution to an 8-puzzle using A* search algorithm.\n"
        "Two heuristics can be used to in the A* search, being the Hamming Distance and\n"
        "the Manhattan Distance.\n\n");
    return;
}

/**
 * This function gets the initial board configuration determined by the user.
 * There are four pre-determined board configurations that the user can choose
 * from, ranging in different diificulties. However, the user is also free to
 * input any configuration they want.
**/
void getInitialState(State initialState)
{
    int initialBoardConfiguration;

    // print the instruction
    printf(
        "Choose the initial state of the 8-puzzle.\n"
        "\t1. Easy\n"
        "\t2. Medium\n"
        "\t3. Hard\n"
        "\t4. Worst\n"
        "\t5. Input your own configuration.\n\n" CLEAR);

    // scan the user's choice and repeat if the choice is invalid.
    do
    {
        printf(BOLD BLUE "\033[1A" CLEAR "\rEnter your choice: ");
        scanf("%d", &initialBoardConfiguration);
        printf(RESET);
        if (initialBoardConfiguration < 1 || initialBoardConfiguration > 5)
            printf(BOLD RED "ERROR: Invalid input. Choices are 1 to 5 only.\033[2B" RESET);
    }
    while(initialBoardConfiguration < 1 || initialBoardConfiguration > 5);

    printf(CLEAR "\n");

    // set the initial board configuration according to the user's choice
    if (initialBoardConfiguration == 1)
    {
        copyState(initialState, easyConfiguration);
        printf(BOLD "Initial board configuration:\n\n\n\n\n\n\n\n\n" RESET);
        printState(initialState, -1, -1);
        return;
    }
    else if (initialBoardConfiguration == 2)
    {
        copyState(initialState, mediumConfiguration);
        printf(BOLD "Initial board configuration:\n\n\n\n\n\n\n\n\n" RESET);
        printState(initialState, -1, -1);
        return;
    }
    else if (initialBoardConfiguration == 3)
    {
        copyState(initialState, hardConfiguration);
        printf(BOLD "Initial board configuration:\n\n\n\n\n\n\n\n\n" RESET);
        printState(initialState, -1, -1);
        return;
    }
    else if (initialBoardConfiguration == 4)
    {
        copyState(initialState, worstConfiguration);
        printf(BOLD "Initial board configuration:\n\n\n\n\n\n\n\n\n" RESET);
        printState(initialState, -1, -1);
        return;
    }
    else if (initialBoardConfiguration == 5)
    {
        setBoardConfiguration(initialState);
        // printf(BOLD RED "Not yet implemented." RESET);
        return;
    }
}

/**
 * This function gets from the user the custom initial board configuration they want
**/
void setBoardConfiguration(State state)
{
    // variable declarations
    char row, col;
    int number;

    // flags for input validation
    int isNumUsed[9] = { 0 };

    // set the state to a blank state first
    copyState(state, blankState);

    // prompt the user
    printf(BOLD "Enter your desired board configuration. (Represent the blank tile with a '0'):\n\n\n\n\n\n\n\n\n" RESET);

    // scan the custom board configuration
    for (row = 0; row < BOARD_SIZE; row++)
    {
        for (col = 0; col < BOARD_SIZE; col++)
        {
            printState(state, row, col);
            printf(BOLD BLUE CLEAR"\rboard[%i][%i]: ", row, col);

            scanf("%i", &number);
            printf(RESET);

            if(number >= 0 && number < 9)
            {
                // check if input is repeated
                if(!isNumUsed[number])
                {
                    state[row][col] = number;
                    isNumUsed[number] = 1;
                    printf(CLEAR"\r");
                }
                else
                {
                    printf(BOLD RED "ERROR: Number %c is already used. Try again with different input.\033[2B" RESET, number);
                    col--;
                }
            }
            else {
                printf(BOLD RED CLEAR "\rERROR: Invalid input. Enter a number from 0 to 8.\033[2B" RESET);
                col--;
            }
        }
    }
    // print the initial state
    printState(state, -1, -1);
    printf("\033[1A\r\n");
}

/**
 * This function gets from the user the heuristic to be used in performing the A*
 * algorithm. There are two choices: Hamming Distance and Manhattan Distance.
**/
int getHeuristic()
{
    int heuristic;      // variable to store the choice of the user

    // print the instruction
    printf(
        "Choose the heuristic to be used in solving the 8-puzzle.\n"
        "\t1. Hamming Distance heuristic (Number of tiles in the wrong position)\n"
        "\t2. Manhattan Distance heuristic (Sum of the distances of each tile from their goal position)\n\n");

    // get the choice of the user and repeat if the input is invalid
    do
    {
        printf(BOLD BLUE "\033[1A" CLEAR "\rEnter your choice: ");
        scanf("%d", &heuristic);
        printf(RESET);
        if (heuristic < 1 || heuristic > 2)
            printf(BOLD RED "ERROR: Invalid input. The choices are 1 and 2 only.\033[1B" RESET);

    }
    while(heuristic < 1 || heuristic > 2);

    printf(CLEAR"\n");

    // return the user's choice of heuristic
    return heuristic;
}

/**
 * This function prints the state inputted to it.
**/
void printState(State state, int row, int col)
{
    printf("\r\033[8A\n" BOLD YELLOW);

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("\r");
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (i == row && j == col)
                printf(BLUE " _ " YELLOW);
            else if (state[i][j] == 0 || state[i][j] == -1)
                printf("   ");
            else
                printf(" %d ", state[i][j]);

            if (j < 2)
                printf("|");
            else
                printf("\n");
        }
        if (i < 2)
            printf("\r---+---+---\n");
    }
    printf("\n" RESET);
}

/**
 * This function prints the solution to the puzzle. The solution is the series of
 * moves needed to perform to the initial state to reach the goal state. The details
 * about the process of the search are also printed.
**/
void printSolution(struct StackNode *path) {
	// check if solution exists
    if(!path) {
        printf(BOLD RED "No solution found.\n\n");
        return;
    }

	// if the initial state is already the goal state
	if(!path->next) {
		printf(BOLD GREEN "\rNo moves needed. The initial state is already the goal state.\n\n");
		return;
	}

    printf(
        BOLD GREEN "\rSOLUTION FOUND!\n\n" RESET
        BOLD "SOLUTION" RESET " (Relative to the space character):\n");

    // hash map to store the moves
    char *move[4] = { "UP", "DOWN", "LEFT", "RIGHT" };

    // initialize counter to 1
    int counter = 1;

    // print the series of moves
    // skip the first node since it represents the initial state with no action
    for(path = path->next; path; path = path->next, ++counter) {
        printf("%2i. Move %s\n", counter, move[(path->node)->action]);
    }

    // print the details of the process
    printf(
        BOLD
        "\nSolution length : %i\n"
        "Nodes expanded  : %i\n"
        "Nodes generated : %i\n"
        "Runtime         : %g seconds\n"
        "Memory used     : %li bytes\n\n", //only counting allocated `Node`s
        counter - 1, nodesExpanded, nodesGenerated, runtime, (nodesGenerated * sizeof(Node)) + (nodesGenerated * sizeof(StackNode)));
}
