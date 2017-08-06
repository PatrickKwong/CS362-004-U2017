
/* -----------------------------------------------------------------------
 * CS362-004 Summer 2017 Assignment 5
 * cardtest1.c
 *
 * Patrick Kwong
 * kwongp@oregonstate.edu
 * 
 * Unit test for Adventurer using teammate (cuddhys)'s code
 * - put 2 treasure cards in hand and discarded other revealed cards
 * 
 * Used provided cardtest4.c and testUpdateCoins.c examples
 * -----------------------------------------------------------------------
 * Include the following lines in the makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
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

// prototype
int adventurerFunc(int currentPlayer, struct gameState *state);

int main() {
    int i;
    int seed;
    int numPlayer = 2;
    int bugCount = 0;
    int flag = 0;
    int prevCount, afterCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, prevG;
    seed = (rand() % 100);
	
	
    printf("\nTesting refactored adventurer card function\n");
    printf("-------------------------------------------\n");
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    gainCard(adventurer, &G, 2, 0); // add adventurer card to player 1's hand
    
    memcpy(&prevG, &G, sizeof(struct gameState)); //create clone of game state to run tests on
    
    // get hand counts
    prevCount = prevG.handCount[0];
	
    // adventurer_func(&G); // my previous code
	// modifications to be able to use teammates's adventurer function
	int currentPlayer = 0;
	adventurerFunc(currentPlayer, &G);
	
	afterCount = G.handCount[0];

    // check if correct number of cards after refactored adventurer card
    printf("\nChecking if correct number of cards after using refactored adventurer card .\n");
    printf("Previous hand count: %d, After Adventurer: %d\n", prevCount, afterCount);
    printf("Expected hand count after Adventurer: 7 (+1 = +2 drawn from Adventurer and -1 from discarding Adventurer.\n");
    if(prevG.handCount[0]+1 != G.handCount[0]){
        printf("Bug!!! Ended with the incorrect number of cards in hand after Adventurer.\n");
        bugCount++;
    }
    else
        printf("Great! Ended with the correct number of cards in hand after Adventurer.\n");

    // check if adventurer added the only treasure cards to hand 
    printf("\nChecking if refactored adventurer card adds only treasure cards to hand.\n");
    if(G.hand[0][G.handCount[0]-2] != copper && G.hand[0][G.handCount[0]-2] != silver && G.hand[0][G.handCount[0]-2] != gold){
        printf("Bug!!! Adventurer added a card beside a treasure.\n");
        bugCount++;
    }
    else if(G.hand[0][G.handCount[0]-1] != copper && G.hand[0][G.handCount[0]-1] != silver && G.hand[0][G.handCount[0]-1] != gold){
        printf("Bug!!! Adventurer added a card beside a treasure.\n");
        bugCount++;
    }
    else
        printf("Great! Adventurer added only treasure cards to hand.\n");

    // check if adventurer drew enough cards from deck 
    printf("\nChecking if refactored adventurer card drew enough cards to hand.\n");
    if(prevG.deckCount[0]-2 < G.deckCount[0]){
        printf("Bug!!! Adventurer didn't draw enough cards from the deck.\n");
        bugCount++;
    }
    else
        printf("Great! Adventurer drew enough cards from deck.\n");

    // check if adventurer discarded the correct number cards to hand 
    printf("\nChecking if refactored adventurer card discarded correct number of cards to hand.\n");
    printf("Previous deck count: %d cards, After Adventurer: %d cards\n", prevG.deckCount[0], G.deckCount[0]);    
    printf("Previous discard count: %d cards, After Adventurer: %d cards\n", prevG.discardCount[0], G.discardCount[0]);
    printf("Expected deck count after Adventurer: %d card.\n", (prevG.deckCount[0] - 2));
    if((prevG.deckCount[0] - G.deckCount[0]) == (G.deckCount[0] - prevG.deckCount[0] + 1)){
        printf("Bug!!! Adventurer discarded the incorrect number of cards to hand.\n");
        bugCount++;
    }
    else
        printf("Great! Adventurer discarded the correct number of cards to hand.\n");


    // check if Adventurer altered other player's cards
    printf("\nChecking if refactored adventurer card altered other player's hand.\n");
    if(prevG.handCount[1] != G.handCount[1]){
        printf("Bug!!! Adventurer altered other player's cards\n");
        bugCount++;
    }
    else if(prevG.deckCount[1] != G.deckCount[1]){
        printf("Bug!!! Adventurer altered other player's cards\n");
        bugCount++;
    }
    else if(prevG.discardCount[1] != G.discardCount[1]){
        printf("Bug!!! Adventurer altered other player's cards\n");
        bugCount++;
    }
    else
        printf("Great! Adventurer didn't alter other player's cards.\n");
    
    // check if Adventurer altered the victory and kingdom piles
    printf("\nChecking if refactored adventurer card altered the Victory and Kingdom piles.\n");
    int arraySize = sizeof(G.supplyCount) / sizeof(int);
    for(i = 0; i < arraySize; i++){
        if(G.supplyCount[i] != prevG.supplyCount[i]){
            flag = 1;
        }
    }
    if(flag == 0)
        printf("Great! Adventurer didn't alter the Victory and Kingdom piles.\n");
    else
    {
        printf("Bug!!! Kingdom/Victory supplied have been altered\n");
        bugCount++;
    }

    // output the test results overall
    printf("---------------------------------------------------\n");
    printf("Final Testing results of refactored adventurer card\n");
    printf("---------------------------------------------------\n");

    if(bugCount == 0)
        printf("All tests passed for the refactored adventurer card!\n\n");
    else
        printf("refactored adventurer card failed for %d condition(s), check above for which ones.\n\n", bugCount);
    
    return 0;
}