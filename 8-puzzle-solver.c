// FILE:            8-puzzle-solver.c
// TITLE:           8 Puzzle Solver
// SUBMITTED BY:    Francis Anjelo M. Andes
//                  Miles B. Artiaga
//
//                  All code is our own except where credited to others.
// FOR COURSE:      CSElec1 Sem 1 2020
//
// INCLUDED FILES:
//    position.h
//    node.h
//    state.h
//    stack.h
//    io.h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// global variables initialization
unsigned int nodesExpanded = 0;     // number of expanded nodes
unsigned int nodesGenerated = 0;    // number of generated nodes
double runtime;                     // runtime of the search algorithm

#include "position.h"
#include "node.h"
#include "state.h"
#include "stack.h"
#include "io.h"

// forward declaration of aStarSearch function
StackNode* aStarSearch(State initialState, int heuristic);

// main function
int main()
{
    // variable declarations
    State initialState;     // initial board configuration
    int heuristic;          // heuristic to be used

    printInstructions();            // display instructions
    getInitialState(initialState);  // get the initial board configuration from the user

    // chech if the initial state inputted is solvable
    // if it is solvable, perform the search, otherwise, exit
    if (isSolvable(initialState))
    {
        // get the heuristic to be used
        heuristic = getHeuristic();

        // perform A star search and print the solution
        printSolution(aStarSearch(initialState, heuristic));
    }
    else
    {
        // notify the user that tne input board configuration is not solvable
        printf(CLEAR BOLD RED "ERROR: The board configuration you entered is not solvable.\n\n");
    }
}

// A star search function
StackNode* aStarSearch(State initialState, int heuristic)
{
    // initialize OPEN and CLOSED lists
    StackNode *topOpenList = NULL;      // OPEN list
    StackNode *topClosedList = NULL;    // CLOSED list

    Node *node = NULL;

    // start timer
    clock_t start = clock();

    // Step 1. Put the start node s on a list called OPEN and compute f(s).
    push(&topOpenList, createNode(initialState, NULL, 0, fValue(initialState, heuristic), NOT_APPLICABLE));

    // Step 2. If OPEN is empty, exit with failure; otherwise continue.
    while (topOpenList)
    {
        printf(BOLD YELLOW CLEAR"\rSolving%.*s" HIDE RESET, nodesExpanded % 5, ".....");
        fflush(stdout);

        // Step 3. Remove from OPEN that node whose f value is smallest and put it on a list called CLOSED. Call it n.
        node = pop(&topOpenList);
        push(&topClosedList, node);

        // Step 4. If n is a goal node, exit with the solution path obtained by tracing back the pointers, otherwise continue.
        if (isIdentical(node->state, goalState))
            break;

        // Step 5. Expand node n, generating all its successors. If there are no successors, go immediately to 2.
        StackNode *children = generateSuccesors(node, heuristic);
        nodesExpanded++;    // increment number of nodes expanded

        // Step 5 (cont.). For each successor ni, compute f(n).
        while (children)
        {
            Node *child = pop(&children);

            // Steps 6 and 7.
            //
            // Associate with the successors not already on either OPEN or CLOSED the f values just computed.
            // Put these nodes on OPEN and direct pointers from them back to n
            //
            // Associate with those successors that were already on OPEN or CLOSED the smaller of the f values
            // just computed and their previous f values. Put on OPEN those successors on CLOSED whose f values were
            // thus lowered, and redirect to n the pointers from a nodes whose f values were lowered.
            if (associate(&topOpenList, child) || associate(&topClosedList, child))
                sortedInsert(&topOpenList, child);
            else
                free(child); // free the child node if it is not supposed to be added to the OPEN list
        }
    }
    // determine the runtime
    runtime = (double)(clock() - start) / CLOCKS_PER_SEC;

    // destroy or deallocate the lists used
    destroyStack(&topOpenList);
    destroyStack(&topClosedList);

    StackNode* solutionHead = NULL;     // variable to hold the solution
    StackNode* current = NULL;          // temporary variable to hold the nodes

    // trace back the steps taken to reach the goal
    while (node)
    {
        current = malloc(sizeof(StackNode));
        current->node = node;
        current->next = solutionHead;
        solutionHead = current;

        node = node->parent;
    }

    // return the solution
    return solutionHead;
}
