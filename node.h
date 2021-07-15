/**
 * Francis Anjelo M. Andes
 * Miles B. Artiaga
 * CSElec1-BSCS3B: Artificial Intelligence
**/

// forward declarations
typedef struct StackNode StackNode;
int fValue(State state, int heuristic);
void copyState(State destination, const State source);

// enum variable to store the moves
typedef enum Move
{
    UP, DOWN, LEFT, RIGHT,  // values for each of the move
    NOT_APPLICABLE          // value for the initial state
}
Move;

// the node that represents each state of the puzzle
typedef struct Node
{
    State state;            // state (current board configuration)
    Move action;            // action that led to this state
    struct Node *parent;    // pointer to its parent node
    unsigned int depth;     // the depth of this node in the search tree
    unsigned int fValue;    // the fValue of this state
}
Node;

// forward declaration
void push(StackNode **top, Node *node);

/**
 * This function creates a Node that represents a state in the puzzle.
**/
Node* createNode(State state, Node *parent, unsigned int depth, unsigned int fValue, Move action)
{
    // allocate memory space for the node
    Node *newNode = malloc(sizeof(Node));

    // if the memory allocation for the node is succesful, continue to store the details
    if (newNode)
    {
        copyState(newNode->state, state);
        newNode->action = action;
        newNode->parent = parent;
        newNode->depth = depth;
        newNode->fValue = fValue;
    }

    // return the newly created node
    return newNode;
}

/**
 * This function creates the successor node of the parent, given the move.
 * If there is no succesor node created, NULL is returned.
 ***
 * This function is adapted from Christian (C-Collamar on GitHub) but is modified to suit
 * this program.
 * https://github.com/C-Collamar/8-Puzzle-Solver
**/
Node* createSuccessorNode(Node *parent, Move action, int heuristic)
{
    // allocate memory for newNode
    Node *newNode = malloc(sizeof(Node));

    // copy the state of the parent to this newNode
    copyState(newNode->state, parent->state);

    // get the position of the blank tile in the board
    Position blank = getPosition(newNode->state, 0);

    // generate the succesor node of the parent if there is one
    if (action == UP && blank.row - 1 >= 0)
    {
        // swap the blank tile with the tile above it
        int temp = newNode->state[blank.row - 1][blank.col];
        newNode->state[blank.row - 1][blank.col] = 0;
        newNode->state[blank.row][blank.col] = temp;

        newNode->action = UP;                               // store the move that resulted to this state
        newNode->parent = parent;                           // store the pointer to its parent
        newNode->depth = parent->depth + 1;                 // store the depth
        newNode->fValue = newNode->depth + fValue(newNode->state, heuristic);   // calculate for the fValue
        return newNode;
    }
    else if (action == DOWN && blank.row + 1 < 3)
    {
        // swap the blank tile with the tile below it
        int temp = newNode->state[blank.row + 1][blank.col];
        newNode->state[blank.row + 1][blank.col] = 0;
        newNode->state[blank.row][blank.col] = temp;

        newNode->action = DOWN;                             // store the move that resulted to this state
        newNode->parent = parent;                           // store the pointer to its parent
        newNode->depth = parent->depth + 1;                 // store the depth
        newNode->fValue = newNode->depth + fValue(newNode->state, heuristic);   // calculate for the fValue
        return newNode;
    }
    else if (action == LEFT && blank.col - 1 >= 0)
    {
        // swap the blank tile with the tile on its left
        int temp = newNode->state[blank.row][blank.col - 1];
        newNode->state[blank.row][blank.col - 1] = 0;
        newNode->state[blank.row][blank.col] = temp;

        newNode->action = LEFT;                             // store the move that resulted to this state
        newNode->parent = parent;                           // store the pointer to its parent
        newNode->depth = parent->depth + 1;                 // store the depth
        newNode->fValue = newNode->depth + fValue(newNode->state, heuristic);   // calculate for the fValue
        return newNode;
    }
    else if (action == RIGHT && blank.col + 1 < 3)
    {
        // swap the blank tile with the tile on its right
        int temp = newNode->state[blank.row][blank.col + 1];
        newNode->state[blank.row][blank.col + 1] = 0;
        newNode->state[blank.row][blank.col] = temp;

        newNode->action = RIGHT;                                // store the move that resulted to this state
        newNode->parent = parent;                           // store the pointer to its parent
        newNode->depth = parent->depth + 1;                 // store the depth
        newNode->fValue = newNode->depth + fValue(newNode->state, heuristic);   // calculate for the fValue
        return newNode;
    }
    // free the newNode
    free(newNode);
    // return NULL
    return NULL;
}

/**
 * This function generates all the succesor nodes of a node. A linked list of succesor
 * nodes is returned by this function.
 ***
 * This function is adapted from Christian (C-Collamar on GitHub) but is modified to suit
 * this program.
 * https://github.com/C-Collamar/8-Puzzle-Solver
**/
StackNode* generateSuccesors(Node *parent, int heuristic)
{
    StackNode *succesors = NULL;
    Node *child = NULL;

    if(parent->action != DOWN && (child = createSuccessorNode(parent, UP, heuristic)))
    {
        nodesGenerated++;           // increment the numbers of nodes generated
        push(&succesors, child);    // push the generated succesor node to the stack
    }

    if(parent->action != UP && (child = createSuccessorNode(parent, DOWN, heuristic)))
    {
        nodesGenerated++;           // increment the numbers of nodes generated
        push(&succesors, child);    // push the generated succesor node to the stack
    }

    if(parent->action != LEFT && (child = createSuccessorNode(parent, RIGHT, heuristic)))
    {
        nodesGenerated++;           // increment the numbers of nodes generated
        push(&succesors, child);    // push the generated succesor node to the stack
    }

    if(parent->action != RIGHT && (child = createSuccessorNode(parent, LEFT, heuristic)))
    {
        nodesGenerated++;           // increment the numbers of nodes generated
        push(&succesors, child);    // push the generated succesor node to the stack
    }

    // return the list of succesor nodes
    return succesors;
}
