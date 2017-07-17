
/* -----------------------------------------------------------------------
 * CS362-004 Summer 2017 Assignment 3
 * cardtest3.c
 * 
 * Patrick Kwong
 * kwongp@oregonstate.edu
 *
 * Unit test for my refactored council_room card function: council_room_func
 * player that plays council_room draws 4 cards, other players draw 1 card
 * player gets a extra buy
 * Used provided cardtest4.c and testUpdateCoins.c examples
 * -----------------------------------------------------------------------
 * Include the following lines in the makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
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

    printf("\nTesting refactored Council Room card function\n");
    printf("-----------------------------------------------\n");
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    gainCard(council_room, &G, 2, 0); // add council_room card to player 1's hand
    memcpy(&prevG, &G, sizeof(struct gameState)); //create clone of game state to run tests on

    council_room_func(G.handCount[0], &G);

    // check if hand count correct after Council Room 
    printf("\nChecking hand count is correct after using refactored Council Room card.\n");
    printf("Previous hand count: %d, After Council Room: %d\n", prevG.handCount[0], G.handCount[0]);
    printf("Expected hand count after Council Room: 9 (+3 = +4 drawn from Council Room and -1 from discarding Council Room.\n");
    if(prevG.handCount[0]+3 != G.handCount[0]){
        printf("Bug!!! Ended with the incorrect number of cards in hand after Council Room.\n");
        bugCount++;
    }
    else
        printf("Great! Ended with the correct number of cards in hand after Council Room.\n");

    // check if Council Room drew the correct cards from deck
    printf("\nChecking if refactored Council Room card drew enough cards to hand.\n");
    printf("Previous deck count: %d, After Council Room: %d\n", prevG.deckCount[0], G.deckCount[0]);
    printf("Council Room drew: %d cards. Expected to draw 4 cards.\n", prevG.deckCount[0] - G.deckCount[0]);
    if((prevG.deckCount[0] - G.deckCount[0]) != 4){
        printf("Bug!!! Council Room didn't draw correct nunmber of cards from the deck.\n");
        bugCount++;
    }
    else
        printf("Great! Council Room drew correct number of cards from deck.\n");

    // check if Council Room gave player another buy
    printf("\nChecking if refactored Council Room card gave player another buy.\n");
    printf("Previous buy count: %d, After Council Room: %d\n", prevG.numBuys, G.numBuys);
    printf("Expected to get +1 buys.\n");
    if((G.numBuys - prevG.numBuys) != 1){
        printf("Bug!!! Council Room didn't add a buy for player.\n");
        bugCount++;
    }
    else
        printf("Great! Council Room did add a buy for player.\n");

    // check if Council Room altered other player's correctly: +1 draw, -1 in deck, same discard 
    printf("\nChecking if refactored Council Room card altered other player's hand.\n");
    if(prevG.handCount[1] != G.handCount[1] - 1){
        printf("Bug!!! Other player add card to hand.\n");
        bugCount++;
    }
    else if(prevG.deckCount[1] != G.deckCount[1] + 1){
        printf("Bug!!! Other player didn't draw a card.\n");
        bugCount++;
    }
    else if(prevG.discardCount[1] != G.discardCount[1]){
        printf("Bug!!! Council Room altered other player's discard pile.\n");
        bugCount++;
    }
    else
        printf("Great! Other player correctly drew a card.\n");
    
    // check if Council Room altered the victory and kingdom piles
    printf("\nChecking if refactored Council Room card altered the Victory and Kingdom piles.\n");
    int arraySize = sizeof(G.supplyCount) / sizeof(int);
    for(i = 0; i < arraySize; i++){
        if(G.supplyCount[i] != prevG.supplyCount[i]){
            flag = 1;
        }
    }
    if(flag == 0)
        printf("Great! Council Room didn't alter the Victory and Kingdom piles.\n");
    else
    {
        printf("Bug!!! Kingdom/Victory supplied have been altered!\n");
        bugCount++;
    }

    // output the test results overall
    printf("---------------------------------------------------\n");
    printf("Final Testing results of refactored Council Room card\n");
    printf("---------------------------------------------------\n");

    if(bugCount == 0)
        printf("All tests passed for the refactored Council Room card!\n\n");
    else
        printf("Refactored Council Room card failed for %d condition(s), check above for which ones.\n\n", bugCount);

    return 0;
}