/**
 * Francis Anjelo M. Andes
 * Miles B. Artiaga
 * CSElec1-BSCS3B: Artificial Intelligence
**/

#define BOARD_SIZE 3
typedef int State[BOARD_SIZE][BOARD_SIZE];

// this data structure represents a position on the board
typedef struct Position
{
    int row;
    int col;
}
Position;

/**
 * This function gets the position of a certain number in the board.
**/
Position getPosition(State state, int number)
{
    Position position;

    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (state[row][col] == number)
            {
                position.row = row;
                position.col = col;
            }
        }
    }
    return position;
}
