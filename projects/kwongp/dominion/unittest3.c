/* -----------------------------------------------------------------------
 * CS362-004 Summer 2017 Assignment 3
 * unittest3.c
 * 
 * Patrick Kwong
 * kwongp@oregonstate.edu
 *
 * Unit test for dominion function: updateCoins
 * calculate players coin count during turn by
 * adding treasure card(s) value in hand and bonus from cards played
 * -----------------------------------------------------------------------
 * Include the following lines in the makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
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
    int maxBonus = 10;
    int p, handCount;
    int gameStatus = 0;
    int bugCount = 0;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    int moreTests[10];
    seed = (rand() % 100); // random seed
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf("Testing updateCoins function...\n");
    printf("Checking the updateCoins function provides correct coin count\n");
    printf("---------------------------------------------------------------------\n\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand

                // all copper test
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(p, &G, bonus);
                printf("All Coopers = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
                gameStatus = (G.coins == handCount * 1 + bonus); // check if the number of coins is correct
                if(gameStatus == 1)
                    printf("Great! updateCoins function returned correct number of coins.\n\n");
                else
                {
                    printf("BUG!!! updateCoins function returned wrong number of coins.\n\n");
                    bugCount++;
                }

                // all silver test
                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(p, &G, bonus);
                printf("All Silvers = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
                gameStatus = (G.coins == handCount * 2 + bonus); // check if the number of coins is correct
                if(gameStatus == 1)
                    printf("Great! updateCoins function returned correct number of coins.\n\n");
                else
                {
                    printf("BUG!!! updateCoins function returned wrong number of coins.\n\n");
                    bugCount++;
                }

                // all gold test
                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(p, &G, bonus);
                printf("All Golds = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
                gameStatus = (G.coins == handCount * 3 + bonus); // check if the number of coins is correct
                if(gameStatus == 1)
                    printf("Great! updateCoins function returned correct number of coins.\n\n");
                else
                {
                    printf("BUG!!! updateCoins function returned wrong number of coins.\n\n");
                    bugCount++;
                }
            }
        }
    }


    // 5 card treasure mix test
    for(p = 0; p < numPlayer; p++)
    {
        for (bonus = 0; bonus <= maxBonus; bonus++)
        {

            
            printf("Test player %d with 5 treasure cards (1 gold, 2 silver, 2 copper) & %d bonus.\n", p, bonus);
            seed = (rand() % 100); // random seed
            memset(&G, 23, sizeof(struct gameState));   // clear the game state
            initializeGame(numPlayer, k, seed, &G); // initialize new game
            G.handCount[p] = 5;

            moreTests[0] = gold;
            moreTests[1] = silver;
            moreTests[2] = silver;
            moreTests[3] = copper;
            moreTests[4] = copper;

            memcpy(G.hand[p], moreTests, sizeof(int) * 5); 
            updateCoins(p, &G, bonus);
            printf("1 Gold, 2 Silvers, 2 Coppers = %d, expected = %d\n", G.coins, (handCount * 1) + 3 + bonus); // 5 treasure, +1 for each silver and +2 for the gold
            gameStatus = (G.coins == (handCount * 1) + 3 + bonus);
            
            if(gameStatus == 1)
                printf("Great! updateCoins function returned correct number of coins.\n\n");
            else
            {
                printf("BUG!!! updateCoins function returned wrong number of coins.\n\n");
                bugCount++;
            }
        }
    }

    // 4 treasure mix with 1 kingdom card test
    for(p = 0; p < numPlayer; p++)
    {
        for (bonus = 0; bonus <= maxBonus; bonus++)
        {        
            printf("Test player %d with 5 treasure cards (1 gold, 2 silver, 1 copper, 1 Smithy) & %d bonus.\n", p, bonus);
            seed = (rand() % 100); // random seed
            memset(&G, 23, sizeof(struct gameState));   // clear the game state
            initializeGame(numPlayer, k, seed, &G); // initialize new game
            G.handCount[p] = 5;

            moreTests[0] = gold;
            moreTests[1] = silver;
            moreTests[2] = silver;
            moreTests[3] = copper;
            moreTests[4] = smithy;

            memcpy(G.hand[p], moreTests, sizeof(int) * 5); 
            updateCoins(p, &G, bonus);
            printf("1 Gold, 2 Silvers, 1 Coppers, 1 Smithy = %d, expected = %d\n", G.coins, (handCount * 1) + 2 + bonus);
            gameStatus = (G.coins == (handCount * 1) + 2 + bonus);

            if(gameStatus == 1)
                printf("Great! updateCoins function returned correct number of coins.\n\n");
            else
            {
                printf("BUG!!! updateCoins function returned wrong number of coins.\n\n");
                bugCount++;
            }
        }
    }

    // 5 kingdom card test and no treasure
    for(p = 0; p < numPlayer; p++)
    {
        for (bonus = 0; bonus <= maxBonus; bonus++)
        {        
            printf("Test player %d with 5 kingdom cards) & %d bonus.\n", p, bonus);
            seed = (rand() % 100); // random seed
            memset(&G, 23, sizeof(struct gameState));   // clear the game state
            initializeGame(numPlayer, k, seed, &G); // initialize new game
            G.handCount[p] = 5;

            moreTests[0] = feast;
            moreTests[1] = gardens;
            moreTests[2] = village;
            moreTests[3] = baron;
            moreTests[4] = smithy;

            memcpy(G.hand[p], moreTests, sizeof(int) * 5); 
            updateCoins(p, &G, bonus);
            printf("5 kingdom cards = %d, expected = %d\n", G.coins, 0 + bonus);
            gameStatus = (G.coins == 0 + bonus);

            if(gameStatus == 1)
                printf("Great! updateCoins function returned correct number of coins.\n\n");
            else
            {
                printf("BUG!!! updateCoins function returned wrong number of coins.\n\n");
                bugCount++;
            }
        }
    }

    // output the test results overall
    printf("---------------------------------------------\n");
    printf("Final Testing results of updateCoins function\n");
    printf("---------------------------------------------\n");
    if(bugCount == 0)
        printf("All tests passed for the updateCoins function!\n\n");
    else
        printf("updateCoins failed provide correct number of coins for %d condition(s), check above for which ones.\n\n", bugCount);
    
    return 0;
}
