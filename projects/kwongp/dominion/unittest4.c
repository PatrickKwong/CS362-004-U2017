/* -----------------------------------------------------------------------
 * CS362-004 Summer 2017 Assignment 3
 * unittest4.c
 * 
 * Patrick Kwong
 * kwongp@oregonstate.edu
 *
 * Unit test for dominion function: supplyCount
 * supplyCount returns the correct number in supply piles 
 * -----------------------------------------------------------------------
 * Include the following lines in the makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
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
    int count, seed, expected, i;
    int bugCount = 0;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    seed = (rand() % 100); // random seed
 
    printf("Testing supplyCount function...\n");
    printf("Checking the supplyCount function returns correct number in supply\n");
    printf("------------------------------------------------------------------\n\n");

    for (i = 0; i < 3; i++)
    {
        printf("Testing with %d players \n", numPlayer);
        printf("------------------------\n\n");

        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game

        // test number of supply piles after initializing game
        count = supplyCount(adventurer, &G);
        printf ("supplyCount(adventurer, &G) = %d, expected: 10\n", count);
        if(count == 10)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }

        count = supplyCount(council_room, &G);
        printf ("supplyCount(council_room, &G) = %d, expected: 10\n", count);
        if(count == 10)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }
        
        count = supplyCount(feast, &G);
        printf ("supplyCount(feast, &G) = %d, expected: 10\n", count);
        if(count == 10)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }
        
        // rules = start supply for gardens 8 cards for 2 players, 12 for 3 or more players
        count = supplyCount(gardens, &G);
        if(numPlayer == 2) 
            expected = 8;
        else
            expected = 12;
        printf ("supplyCount(gardens, &G) = %d, expected: %d\n", count, expected);
        if(count == expected)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }
        
        count = supplyCount(mine, &G);
        printf ("supplyCount(mine, &G) = %d, expected: 10\n", count);
        if(count == 10)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }
        
        count = supplyCount(remodel, &G);
        printf ("supplyCount(remodel, &G) = %d, expected: 10\n", count);
        if(count == 10)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }
        
        count = supplyCount(smithy, &G);
        printf ("supplyCount(smithy, &G) = %d, expected: 10\n", count);
        if(count == 10)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }
        
        count = supplyCount(village, &G);
        printf ("supplyCount(village, &G) = %d, expected: 10\n", count);
        if(count == 10)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }
        
        count = supplyCount(baron, &G);
        printf ("supplyCount(baron, &G) = %d, expected: 10\n", count);
        if(count == 10)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }
        
        // rules = start supply for great_hall 8 cards for 2 players, 12 for 3 or more players
        count = supplyCount(great_hall, &G);
        if(numPlayer == 2) 
            expected = 8;
        else
            expected = 12;
        printf ("supplyCount(great_hall, &G) = %d, expected: %d\n", count, expected);
        if(count == expected)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }

        // rules = start supply for victory 8 cards for 2 players, 12 for 3 or more players
        count = supplyCount(estate, &G);
        if(numPlayer == 2) 
            expected = 8;
        else
            expected = 12;
        printf ("supplyCount(estate, &G) = %d, expected: %d\n", count, expected);
        if(count == expected)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }

        // rules = start supply for victory 8 cards for 2 players, 12 for 3 or more players
        count = supplyCount(duchy, &G);
        if(numPlayer == 2) 
            expected = 8;
        else
            expected = 12;
        printf ("supplyCount(duchy, &G) = %d, expected: %d\n", count, expected);
        if(count == expected)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }

        // rules = start supply for victory 8 cards for 2 players, 12 for 3 or more players
        count = supplyCount(province, &G);
        if(numPlayer == 2) 
            expected = 8;
        else
            expected = 12;
        printf ("supplyCount(province, &G) = %d, expected: %d\n", count, expected);
        if(count == expected)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }

        // rules = start supply for curse 10 cards for 2 players, 20 for 3 players, 30 for 4 players
        count = supplyCount(curse, &G);
        if(numPlayer == 2) 
            expected = 10;
        else if(numPlayer == 3) 
            expected = 20;
        else
            expected = 30;
        printf ("supplyCount(curse, &G) = %d, expected: %d\n", count, expected);
        if(count == expected)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }

        count = supplyCount(gold, &G);
        printf ("supplyCount(gold, &G) = %d, expected: 30\n", count);
        if(count == 30)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }

        count = supplyCount(silver, &G);
        printf ("supplyCount(silver, &G) = %d, expected: 40\n", count);
        if(count == 40)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }

        count = supplyCount(silver, &G);
        printf ("supplyCount(silver, &G) = %d, expected: 40\n", count);
        if(count == 40)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }


        // rules = start supply for coppers is whatever is leftover after giving 7 coppers to each player from 60 total coppers in gmae
        count = supplyCount(copper, &G);
        expected = 60 - (7 * numPlayer);
        printf ("supplyCount(copper, &G) = %d, expected: %d\n", count, expected);
        if(count == expected)
            printf("Great! supplyCount function returned the correct supply count.\n\n");
        else{
            printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
            bugCount++;
        }
        numPlayer++;
        // dang i've pretty much tested the initializeGame...
    }

    // some tests with manual changes to supplyCount
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    G.supplyCount[copper] = 5;
    count = supplyCount(copper, &G);
    printf ("supplyCount(copper, &G) = %d, expected: 5\n", count);
    if(count == 5)
        printf("Great! supplyCount function returned the correct supply count.\n\n");
    else{
        printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
        bugCount++;
    }

    G.supplyCount[silver] = 11;
    count = supplyCount(silver, &G);
    printf ("supplyCount(silver, &G) = %d, expected: 11\n", count);
    if(count == 11)
        printf("Great! supplyCount function returned the correct supply count.\n\n");
    else{
        printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
        bugCount++;
    }

    G.supplyCount[estate] = 3;
    count = supplyCount(estate, &G);
    printf ("supplyCount(estate, &G) = %d, expected: 3\n", count);
    if(count == 3)
        printf("Great! supplyCount function returned the correct supply count.\n\n");
    else{
        printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
        bugCount++;
    }

    G.supplyCount[adventurer] = 11;
    count = supplyCount(adventurer, &G);
    printf ("supplyCount(adventurer, &G) = %d, expected: 11\n", count);
    if(count == 11)
        printf("Great! supplyCount function returned the correct supply count.\n\n");
    else{
        printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
        bugCount++;
    }

    G.supplyCount[smithy] = 0;
    count = supplyCount(smithy, &G);
    printf ("supplyCount(smithy, &G) = %d, expected: 0\n", count);
    if(count == 0)
        printf("Great! supplyCount function returned the correct supply count.\n\n");
    else{
        printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
        bugCount++;
    }

    // probably shouldn't be able to set supply to -1
    G.supplyCount[curse] = -1;
    count = supplyCount(curse, &G);
    printf ("supplyCount(curse, &G) = %d, expected: -1\n", count);
    if(count == -1)
        printf("Great! supplyCount function returned the correct supply count.\n\n");
    else{
        printf("BUG!!! supplyCount function returned the wrong supply count.\n\n");
        bugCount++;
    }
    
    // output the test results overall
    printf("--------------------------------------------\n");
    printf("Final Testing results of supplyCount function\n");
    printf("-------------------------------------------\n");
    if(bugCount == 0)
        printf("All tests passed for the supplyCount function!\n\n");
    else
        printf("supplyCount returned wrong supply count for %d condition(s), check above for which ones.\n\n", bugCount);
    
    return 0;
}