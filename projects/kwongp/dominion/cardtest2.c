
/* -----------------------------------------------------------------------
 * CS362-004 Summer 2017 Assignment 3
 * cardtest2.c
 * 
 * Patrick Kwong
 * kwongp@oregonstate.edu
 *
 * Unit test for my refactored smithy card function: smithy_func
 * draws 3 cards
 *
 * Used provided cardtest4.c and testUpdateCoins.c examples
 * -----------------------------------------------------------------------
 * Include the following lines in the makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
    int i;
    int seed;
    int numPlayer = 2;
    int bugCount = 0;
    int flag = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, prevG;
    seed = (rand() % 100);

    printf("\nTesting refactored Smithy card function\n");
    printf("-----------------------------------------\n");
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    gainCard(smithy, &G, 2, 0); // add smithy card to player 1's hand
    memcpy(&prevG, &G, sizeof(struct gameState)); //create clone of game state to run tests on

    smithy_func(G.handCount[0], &G);

    // check if hand count correct after Smithy 
    printf("\nChecking hand count is correct after using refactored Smithy card.\n");
    printf("Previous hand count: %d, After Smithy: %d\n", prevG.handCount[0], G.handCount[0]);
    printf("Expected hand count after Smithy: 8 (+2 = +3 drawn from smithy and -1 from discarding smithy.\n");
    if(prevG.handCount[0]+2 != G.handCount[0]){
        printf("Bug!!! Ended with the incorrect number of cards in hand after Smithy.\n");
        bugCount++;
    }
    else
        printf("Great! Ended with the correct number of cards in hand after Smithy.\n");

    // check if Smithy drew the correct cards from deck
    printf("\nChecking if refactored Smithy card drew enough cards to hand.\n");
    printf("Previous deck count: %d, After Smithy: %d\n", prevG.deckCount[0], G.deckCount[0]);
    printf("Smithy drew: %d cards. Expected to draw 3 cards.\n", prevG.deckCount[0] - G.deckCount[0]);
    if((prevG.deckCount[0] - G.deckCount[0]) != 3){
        printf("Bug!!! Smithy didn't draw correct nunmber of cards from the deck.\n");
        bugCount++;
    }
    else
        printf("Great! Smithy drew correct number of cards from deck.\n");

    // check if smithy altered other player's cards
    printf("\nChecking if refactored Smithy card altered other player's hand.\n");
    if(prevG.handCount[1] != G.handCount[1]){
        printf("Bug!!! Smithy altered other player's cards\n");
        bugCount++;
    }
    else if(prevG.deckCount[1] != G.deckCount[1]){
        printf("Bug!!! Ssmithy altered other player's cards\n");
        bugCount++;
    }
    else if(prevG.discardCount[1] != G.discardCount[1]){
        printf("Bug!!! Smithy altered other player's cards\n");
        bugCount++;
    }
    else
        printf("Great! Smithy didn't alter other player's cards.\n");
    
    // check if Smithy altered the victory and kingdom piles
    printf("\nChecking if refactored Smithy card altered the Victory and Kingdom piles.\n");
    int arraySize = sizeof(G.supplyCount) / sizeof(int);
    for(i = 0; i < arraySize; i++){
        if(G.supplyCount[i] != prevG.supplyCount[i]){
            flag = 1;
        }
    }
    if(flag == 0)
        printf("Great! Smithy didn't alter the Victory and Kingdom piles.\n");
    else
    {
        printf("Bug!!! Kingdom/Victory supplied have been altered\n");
        bugCount++;
    }

    // output the test results overall
    printf("---------------------------------------------------\n");
    printf("Final Testing results of refactored smithy card\n");
    printf("---------------------------------------------------\n");

    if(bugCount == 0)
        printf("All tests passed for the refactored smithy card!\n\n");
    else
        printf("refactored smithy card failed for %d condition(s), check above for which ones.\n\n", bugCount);

    return 0;
}