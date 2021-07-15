/**
 * Francis Anjelo M. Andes
 * Miles B. Artiaga
 * CSElec1-BSCS3B: Artificial Intelligence
**/

//forward declarations
typedef struct Node Node;
void printState(State state, int row, int col);

// this data structure represents a node in a singly linked list, particulary
// implemented as a stack
typedef struct StackNode
{
    Node *node;                 // pointer to a node that represents a state in the puzzle
    struct StackNode *next;     // pointer to the next node in the list
}
StackNode;

/**
 * This function pushes the input StackNode on the top of the stack.
**/
void push(StackNode **top, Node *node)
{
    StackNode *newStackNode = malloc(sizeof(StackNode));
    newStackNode->node = node;

    // if the stack is not empty, point the 'next' to the current node on top
    if (top)
    {
        newStackNode->next = *top;
    }

    // if the stack is empty, point the 'next' to null
    else
    {
        newStackNode->next = NULL;
    }

    // point the top of the stack to the new node
    (*top) = newStackNode;

    return;
}

/**
 * This function pops the StackNode from top of the stack and return the Node it holds.
**/
Node* pop(StackNode **top)
{
    // if the stack is not empty
    if (top)
    {
        Node *popped = (*top)->node;    // get the Node on top of the stack
        StackNode *temp = *top;         // store the current top StackNode to a temporary variable
        (*top) = (*top)->next;          // point the top to the new StackNode on top
        free(temp);                     // free the StackNode on top of the stack
        return popped;                  // return the popped Node
    }

    // if the stack is empty, return a 'NULL'
    else
    {
        return NULL;
    }
}

/**
 * This function takes a Node as an input and inserts it to the stack in ascending
 * order of its fValues.
**/
void sortedInsert(StackNode **stack, Node *node)
{
    StackNode *current = *stack;

    // if the stack is empty or the node to be inserted has a lower fValue than the
    // top of the stack, push it to the stack
    if (!(*stack) || (current->node)->fValue >= node->fValue)
    {
        push(&(*stack), node);
    }
    else
    {
        // traverse the stack until it finds the proper position of node to be inserted
        while(current->next && ((current->next)->node)->fValue < node->fValue)
        {
            current = current->next;
        }

        StackNode *newStackNode = malloc(sizeof(StackNode));    // allocate memory to a new StackNode
        newStackNode->node = node;                              // store the Node to the new StackNode

        // fix the pointers
        newStackNode->next = current->next;
        current->next = newStackNode;
    }
    return;
}

/**
 * This function performs the steps 6 and 7 of the pseudocode.
 ***
 * This function checks whether the state is already in the stack and if it is,
 * it compares the fValues of the two. If the input has a lower fValue, it returns
 * 1. otherwise, it returns 0.
**/
int associate (StackNode **stack, Node *node)
{
    // create a pointer and point it to the stack
    StackNode *current = *stack;

    // if stack is empty, return 1
    if (!(*stack))
    {
        return true;
    }

    // if the first node of the stack is identical to the child node and it has
    // a higher fValue, remove it from the stack and return 1, otherwise return 0
    else if (isIdentical((current->node)->state, node->state))
    {
        if ((current->node)->fValue >= node->fValue)
        {
            pop(stack);
            return true;
        }
        else
            return false;
    }

    else
    {
        // traverse the stack until it finds a node with an identical state
        // to the child node, or until it reaches the end
        while(current->next && !isIdentical(((current->next)->node)->state, node->state))
            current = current->next;

        // if there is no identical state in the stack with the child node, return 1
        if (!(current->next))
            return true;

        // if a node with an identical state to the child node is found
        // and its fValue is higher than the child node, then remove it
        // from the stack and return 1, otherwise return 0
        if (isIdentical(((current->next)->node)->state, node->state))
        {
            if (((current->next)->node)->fValue >= node->fValue)
            {
                StackNode *temp = current->next;
                current->next = (current->next)->next;
                free(temp);
                return true;
            }
            else
                return false;
        }

        return true;
    }
}

/**
 * This function deallocates all the StackNodes and Nodes used in the search.
**/
void destroyStack(StackNode **top)
{
    while (*top)
    {
        free(pop(*&top));
    }
}
