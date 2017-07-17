
/* -----------------------------------------------------------------------
 * CS362-004 Summer 2017 Assignment 3
 * cardtest4.c
 * 
 * Patrick Kwong
 * kwongp@oregonstate.edu
 *
 * Unit test for my refactored Village card function: council_room_func
 * player that plays Village draws 1 card
 * player gets two extra actions
 * Used provided cardtest4.c and testUpdateCoins.c examples
 * -----------------------------------------------------------------------
 * Include the following lines in the makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
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

    printf("\nTesting refactored Village card function\n");
    printf("-----------------------------------------------\n");
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    gainCard(village, &G, 2, 0); // add Village card to player 1's hand
    memcpy(&prevG, &G, sizeof(struct gameState)); //create clone of game state to run tests on

    village_func(G.handCount[0], &G);

    // check if hand count correct after Village
    printf("\nChecking hand count is correct after using refactored Village card.\n");
    printf("Previous hand count: %d cards, After Village: %d cards\n", prevG.handCount[0], G.handCount[0]);
    printf("Expected hand count be same after using Village. (0 = +1 drawn from Village and -1 from discarding Village.\n");
    if(prevG.handCount[0] != G.handCount[0]){
        printf("Bug!!! Ended with the incorrect number of cards in hand after Village.\n");
        bugCount++;
    }
    else
        printf("Great! Ended with the correct number of cards in hand after Village.\n");

    // check if Village drew the correct cards from deck
    printf("\nChecking if refactored Village card drew enough cards to hand.\n");
    printf("Previous deck count: %d cards, After Village: %d cards\n", prevG.deckCount[0], G.deckCount[0]);
    printf("Village drew: %d card. Expected to draw 1 card\n", prevG.deckCount[0] - G.deckCount[0]);
    if((prevG.deckCount[0] - G.deckCount[0]) != 1){
        printf("Bug!!! Village didn't draw correct nunmber of cards from the deck.\n");
        bugCount++;
    }
    else
        printf("Great! Village drew correct number of cards from deck.\n");

    // check if Village gave player +2 actions
    printf("\nChecking if refactored Village card gave player +2 actions.\n");
    printf("Previous actions count: %d, After Village: %d\n", prevG.numActions, G.numActions);
    printf("Expected to get +2 actions.\n");
    if((G.numActions - prevG.numActions) != 2){
        printf("Bug!!! Village didn't add +2 actions for player.\n");
        bugCount++;
    }
    else
        printf("Great! Village did add +2 actions for player.\n");

    // check if Village altered other player's piles 
    printf("\nChecking if refactored Village card altered other player's hand.\n");
    if(prevG.handCount[1] != G.handCount[1]){
        printf("Bug!!! Village altered other player's hand pile.\n");
        bugCount++;
    }
    else if(prevG.deckCount[1] != G.deckCount[1]){
        printf("Bug!!! Village altered other player's deck pile.\n");
        bugCount++;
    }
    else if(prevG.discardCount[1] != G.discardCount[1]){
        printf("Bug!!! Village altered other player's discard pile.\n");
        bugCount++;
    }
    else
        printf("Great! Village didn't altered other player's piles.\n");
    
    // check if Village altered the victory and kingdom piles
    printf("\nChecking if refactored Village card altered the Victory and Kingdom piles.\n");
    int arraySize = sizeof(G.supplyCount) / sizeof(int);
    for(i = 0; i < arraySize; i++){
        if(G.supplyCount[i] != prevG.supplyCount[i]){
            flag = 1;
        }
    }
    if(flag == 0)
        printf("Great! Village didn't alter the Victory and Kingdom piles.\n");
    else
    {
        printf("Bug!!! Kingdom/Victory supplied have been altered!\n");
        bugCount++;
    }

    // output the test results overall
    printf("---------------------------------------------------\n");
    printf("Final Testing results of refactored Village card\n");
    printf("---------------------------------------------------\n");

    if(bugCount == 0)
        printf("All tests passed for the refactored Village card!\n\n");
    else
        printf("Refactored Village card failed for %d condition(s), check above for which ones.\n\n", bugCount);

    return 0;
}