/* -----------------------------------------------------------------------
 * CS362-004 Summer 2017 Assignment 3
 * unittest2.c
 * 
 * Unit test for dominion function: isGameOver
 * isGameOver checks the number of provinces or if three supply piles are 
 * empty to determine if the game is over.
 * it returns 1 if game is over or a 0 if game is not over
 * http://wiki.dominionstrategy.com/index.php/Endgame
 * game over when any of following are true:
 * - province pile is empty
 * - three of the supply piles run out (for 2 to 4 players, 4 piles if there are 5+ players) 
 *    (kingdom cards, treasures cards, victory cards, curse cards all count are all supply)
 * Used some of the provided testUpdateCoins.c
 * -----------------------------------------------------------------------
 * Include the following lines in the makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() 
{
    int gameStatus, seed;
    int bugCount = 0;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf("Testing isGameOver function...\n");
    printf("Checking the isGameOver function correct tells us if game is over\n");
    printf("---------------------------------------------------------------------\n\n");

    // no empty test - game should not be over
    seed = (rand() % 100); // random seed
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    printf("Test: Checking isGameOver if all supply piles are not empty.\n");

    gameStatus = isGameOver(&G);
    if(gameStatus == 0)
        printf("Great! isGameOver function returned that game is not over.\n\n");
    else{
        printf("BUG!!! isGameOver function returned that game is over.\n\n");
        bugCount++;
    }
    
    // no provinces test - game should be over
    seed = (rand() % 100); // random seed
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    printf("Test: Checking isGameOver if there are no more provinces.\n");
    G.supplyCount[province] = 0; // setting # of province in pile to 0

    gameStatus = isGameOver(&G);
    if(gameStatus == 1)
        printf("Great! isGameOver function returned that game is over.\n\n");
    else{
        printf("BUG!!! isGameOver function returned that game is not over.\n\n");
        bugCount++;
    }

    // 1 empty supply piles (not province) test with 2 players - game should not be over
    numPlayer = 2;
    seed = (rand() % 100); // random seed
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game    
    printf("Test: Checking isGameOver if there are 1 empty supply pile (silver) test with 2 players.\n");
    G.supplyCount[silver] = 0; // setting # of silver in pile to 0

    gameStatus = isGameOver(&G);
    if(gameStatus == 0)
        printf("Great! isGameOver function returned that game is not over.\n\n");
    else{
        printf("BUG!!! isGameOver function returned that game is over.\n\n");
        bugCount++;
    }

    // 2 empty supply piles (not province) test with 2 players - game should not be over
    numPlayer = 2;
    seed = (rand() % 100); // random seed
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game    
    printf("Test: Checking isGameOver if there are 2 empty supply piles (gold, curse) test with 2 players.\n");
    G.supplyCount[gold] = 0; // setting # of gold in pile to 0
    G.supplyCount[curse] = 0; // setting # of curse in pile to 0

    gameStatus = isGameOver(&G);
    if(gameStatus == 0)
        printf("Great! isGameOver function returned that game is not over.\n\n");
    else{
        printf("BUG!!! isGameOver function returned that game is over.\n\n");
        bugCount++;
    }

    // 2 empty supply piles (1 is province) test with 2 players - game should not be over
    numPlayer = 2;
    seed = (rand() % 100); // random seed
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game    
    printf("Test: Checking isGameOver if there are 2 empty supply piles (great_hall, province) test with 2 players.\n");
    G.supplyCount[great_hall] = 0; // setting # of great_hall in pile to 0
    G.supplyCount[province] = 0; // setting # of province in pile to 0

    gameStatus = isGameOver(&G);
    if(gameStatus == 1)
        printf("Great! isGameOver function returned that game is over.\n\n");
    else{
        printf("BUG!!! isGameOver function returned that game is not over.\n\n");
        bugCount++;
    }

    // 1 empty treasure supply pile and 2 empty kingdom supply piles test with 2 players - game should be over
    numPlayer = 2;
    seed = (rand() % 100); // random seed
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game    
    printf("Test: Checking isGameOver if there are 3 empty supply piles (copper, remodel, smithy) test with 2 players.\n");
    G.supplyCount[copper] = 0; // setting # of copper in pile to 0
    G.supplyCount[remodel] = 0; // setting # of remodel in pile to 0
    G.supplyCount[smithy] = 0; // setting # of smithy in pile to 0

    gameStatus = isGameOver(&G);
    if(gameStatus == 1)
        printf("Great! isGameOver function returned that game is over.\n\n");
    else{
        printf("BUG!!! isGameOver function returned that game is not over.\n\n");
        bugCount++;
    }

    // 3 empty treasure supply piles test with 2 players - game should be over
    numPlayer = 2;
    seed = (rand() % 100); // random seed
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game    
    printf("Test: Checking isGameOver if there are 3 empty treasure supply piles test with 2 players.\n");
    G.supplyCount[copper] = 0; // setting # of copper in pile to 0
    G.supplyCount[silver] = 0; // setting # of silver in pile to 0
    G.supplyCount[gold] = 0; // setting # of gold in pile to 0

    gameStatus = isGameOver(&G);
    if(gameStatus == 1)
        printf("Great! isGameOver function returned that game is over.\n\n");
    else{
        printf("BUG!!! isGameOver function returned that game is not over.\n\n");
        bugCount++;
    }

    // 3 empty kingdom supply piles test with 2 players - game should be over
    numPlayer = 2;
    seed = (rand() % 100); // random seed
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game    
    printf("Test: Checking isGameOver if there are 3 empty supply piles test with 2 players.\n");
    G.supplyCount[adventurer] = 0; // setting # of adventurer in pile to 0
    G.supplyCount[council_room] = 0; // setting # of council_room in pile to 0
    G.supplyCount[feast] = 0; // setting # of feast in pile to 0

    gameStatus = isGameOver(&G);
    if(gameStatus == 1)
        printf("Great! isGameOver function returned that game is over.\n\n");
    else{
        printf("BUG!!! isGameOver function returned that game is not over.\n\n");
        bugCount++;
    }

    // 3 empty supply piles (1 is province) test with 2 players - game should not be over
    numPlayer = 2;
    seed = (rand() % 100); // random seed
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game    
    printf("Test: Checking isGameOver if there are 3 empty supply piles (gardens, copper, province) test with 2 players.\n");
    G.supplyCount[gardens] = 0; // setting # of great_hall in pile to 0
    G.supplyCount[copper] = 0; // setting # of great_hall in pile to 0 
    G.supplyCount[province] = 0; // setting # of province in pile to 0

    gameStatus = isGameOver(&G);
    if(gameStatus == 1)
        printf("Great! isGameOver function returned that game is over.\n\n");
    else{
        printf("BUG!!! isGameOver function returned that game is not over.\n\n");
        bugCount++;
    }

    // 4 empty kingdom supply piles test with 5 players - game should not be over
    numPlayer = 5;
    seed = (rand() % 100); // random seed
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game   
    printf("Test: Checking isGameOver if there are 4 empty kingdom supply piles test with 5 players.\n");
    G.supplyCount[gardens] = 0; // setting # of adventurer in pile to 0
    G.supplyCount[mine] = 0; // setting # of council_room in pile to 0
    G.supplyCount[remodel] = 0; // setting # of feast in pile to 0

    gameStatus = isGameOver(&G);
    if(gameStatus == 0)
        printf("Great! isGameOver function returned that game is not over.\n\n");
    else{
        printf("BUG!!! isGameOver function returned that game is over.\n\n");
        bugCount++;
    }

    // testing 3 empty kingdom cards piles that weren't part of 10 that we're using
    numPlayer = 2;
    seed = (rand() % 100); // random seed
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game    
    printf("Test: Checking isGameOver if there are 3 empty supply piles (gardens, copper, province) test with 2 players.\n");
    G.supplyCount[minion] = 0; // setting # of minion in pile to 0
    G.supplyCount[sea_hag] = 0; // setting # of sea_hag in pile to 0 
    G.supplyCount[cutpurse] = 0; // setting # of cutpurse in pile to 0

    gameStatus = isGameOver(&G);
    if(gameStatus == 0)
        printf("Great! isGameOver function returned that game is not over.\n\n");
    else{
        printf("BUG!!! isGameOver function returned that game is over.\n\n");
        bugCount++;
    }


    // output the test results overall
    printf("--------------------------------------------\n");
    printf("Final Testing results of isGameOver function\n");
    printf("-------------------------------------------\n");
    if(bugCount == 0)
        printf("All tests passed for the isGameOver function!\n\n");
    else
        printf("isGameOver failed to say if game was over for %d condition(s), check above for which ones.\n\n", bugCount);
    
    return 0;
}
