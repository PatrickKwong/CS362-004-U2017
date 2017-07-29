/* -----------------------------------------------------------------------
 * CS362-004 Summer 2017 Assignment 4
 * randomtestcard1.c
 * 
 * Patrick Kwong
 * kwongp@oregonstate.edu
 *
 * Random test generator for Smithy 
 * - draws 3 cards
 *
 * Used provided cardtest4.c, dominion.c, and testUpdateCoins.c provided code
 * -----------------------------------------------------------------------
 * Include the following lines in the makefile:
 *
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
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
#include <stdbool.h>

#define TEST_RUNS 1000

int main() {
    int i, j, r, z;
    int numPlayer;
    int bugCount = 0;
    int flag = 0; // flag for other player piles
	struct gameState G, prevG;
	int seed = 1000;
	srand(time(NULL));
	int k[10]; // for kingdom cards
	int numKingdomCards;
	bool haveCard;
	int numDraw;
	int pass = 0; // track the number of passes
	int fail = 0; // track the number of fails

	printf("------------------------------------------\n");		
	printf(" Testing Random Test Generator for Smithy\n");
	printf("------------------------------------------\n");	
    
	for(z = 1; z <= TEST_RUNS; z++) // test for loop
	{
		// random kingdom cards set (9 random with smithy card)
		numKingdomCards = 0;
		while(numKingdomCards < 10)
		{
			haveCard = false;
			r = (rand() % 20 + 7); // gets a random kingdom card
			
			// check if already have card in kingdom set k
			for(i = 0; i < numKingdomCards; i++)
				if(k[i] == r)
					haveCard = true;
			
			// if we don't have it, add it to k set and increment the numKingdomCards
			if(!haveCard)
			{
				k[numKingdomCards] = r;
				numKingdomCards++;
			}
		}
		// now with random set, we have to make sure smithy card is in the kingdom pile
		// if not we'll randomly replace one of the 10 kindgom cards with an smithy.
		haveCard = false;
		// check 10 kingdom pile for smithy
		for(i = 0; i < 10; i++)
		{
			if(k[i] == smithy)
			{
				haveCard = true;
			}
		}
		// no smithy found, have to randomly add it.
		if(!haveCard)
		{
			r = (rand() % 10); // random position
			k[r] = smithy;
		}
		
		// random number of players from 2 to 5
		numPlayer = ((rand() % 3) + 2);
		
		printf("--------------------------------\n");
		printf(" Starting Test #%d for Smithy\n", z);
		printf("--------------------------------\n");
		
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayer, k, seed, &G); // initialize a new game
		
		// set random deck count for each player
		for(i = 0; i < numPlayer; i++)
			G.deckCount[i] = (rand() % (MAX_DECK/numPlayer));
		
		// fill each players' decks with random cards
		for(i = 0; i < numPlayer; i++)
		{
			for(j = 0; j < G.deckCount[i]; j++) 
			{
				r = rand() % 3;
				switch(r) 
				{
					case 0: G.deck[i][j] = (rand() % 4); // victory card 
						break;
					case 1: G.deck[i][j] = (rand() % 3) + 4; // treasuer card 
						break;
					case 2: G.deck[i][j] = k[(rand() % 10)]; // kingdom card 
						break;
				}
			}
		}
		
		// initialize counters
		bugCount = 0;
		
		memcpy(&prevG, &G, sizeof(struct gameState)); //create clone of game state to run tests on
		smithy_func(G.handCount[0],&G);
		
		/* tried cardEffect instead of my refactored function
		int handPos, choice1, choice2, choice3, bonus;
		choice1 = choice2 = choice3 = bonus = 0;
		
		// find hand position of smithy card
		for(i = 0; i < G.handCount[0]; i++)
		{
			if(G.hand[0][i] == smithy)
			{
				handPos = i;
			}
		}
		
		cardEffect(smithy, choice1, choice2, choice3, &G, handPos, &bonus);
		*/
		// printf("Deck Count: %d\n", G.deckCount[0]);
		/* check that deck, discard, hand contents are random
		printf("Deck Contents\n");
		for(i = 0; i < G.deckCount[0]; i++)
			printf("Position %d, Card: %d\n", i, G.deck[0][i]);
		
		printf("Discard Contents\n");
		for(i = 0; i < G.discardCount[0]; i++)
			printf("Position %d, Card: %d\n", i, G.discard[0][i]);

		printf("Hand Contents\n");
		for(i = 0; i < G.handCount[0]; i++)
			printf("Position %d, Card: %d\n", i, G.hand[0][i]);
		*/
		
		printf("Deck Count before Smithy: %d\n", prevG.deckCount[0]);
		printf("Deck Count after Smithy: %d\n", G.deckCount[0]);
		
		// if there are less than 3 cards, smithy can only draw what is available
		// figure out how much should be drawn
		numDraw = 3;
		
		if (prevG.deckCount[0] < 3)		
			numDraw = prevG.deckCount[0] - G.deckCount[0];
		
		// check if hand count correct after Smithy 
		printf("\nChecking hand count is correct after using refactored Smithy.\n");
		printf("Previous hand count: %d, After Smithy: %d\n", prevG.handCount[0], G.handCount[0]);
		printf("Expected hand count after Smithy: %d\n", (prevG.handCount[0] + numDraw - 1));
		if((prevG.handCount[0] + numDraw - 1) != G.handCount[0]){
			printf("Bug!!! Ended with the incorrect number of cards in hand after Smithy.\n");
			bugCount++;
		}
		else
			printf("Great! Ended with the correct number of cards in hand after Smithy.\n");

		// check if Smithy drew the correct cards from deck
		printf("\nChecking if refactored Smithy drew enough cards to hand.\n");
		printf("Previous deck count: %d, After Smithy: %d\n", prevG.deckCount[0], G.deckCount[0]);
		printf("Smithy drew: %d cards. Expected to draw %d cards.\n", (prevG.deckCount[0] - G.deckCount[0]), numDraw);
		if((prevG.deckCount[0] - G.deckCount[0]) != numDraw){
			printf("Bug!!! Smithy didn't draw correct nunmber of cards from the deck.\n");
			bugCount++;
		}
		else
			printf("Great! Smithy drew correct number of cards from deck.\n");

		// check if smithy altered other player's cards
		printf("\nChecking if refactored Smithy altered other player's hand.\n");
		if(prevG.handCount[1] != G.handCount[1]){
			printf("Bug!!! Smithy altered other player's cards\n");
			bugCount++;
		}
		else if(prevG.deckCount[1] != G.deckCount[1]){
			printf("Bug!!! Smithy altered other player's cards\n");
			bugCount++;
		}
		else if(prevG.discardCount[1] != G.discardCount[1]){
			printf("Bug!!! Smithy altered other player's cards\n");
			bugCount++;
		}
		else
			printf("Great! Smithy didn't alter other player's cards.\n");
		
		// check if Smithy altered the victory and kingdom piles
		printf("\nChecking if refactored Smithy altered the Victory and Kingdom piles.\n");
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
		printf("------------------------------------------\n");
		printf(" Test #%d results for Smithy\n", z);
		printf("------------------------------------------\n");

		if(bugCount == 0)
		{
			printf("All tests passed for the Smithy!\n\n");
			pass++;
		}
		else
		{
			printf("Smithy failed for %d condition(s), check above for which ones.\n\n", bugCount);
			fail++;
		}
		
		/* checking deck, discard, hand contents
		printf("Deck Contents\n");
		for(i = 0; i < G.deckCount[0]; i++)
			printf("Position %d, Card: %d\n", i, G.deck[0][i]);
		
		printf("Discard Contents\n");
		for(i = 0; i < G.discardCount[0]; i++)
			printf("Position %d, Card: %d\n", i, G.discard[0][i]);

		printf("Hand Contents\n");
		for(i = 0; i < G.handCount[0]; i++)
			printf("Position %d, Card: %d\n", i, G.hand[0][i]);
		*/
		
	}
	
	// output the final test results overall
	printf("---------------------------------------------------\n");
	printf(" Final Testing results for Smithy\n");
	printf("---------------------------------------------------\n");

	if(fail == 0)
		printf("All tests passed for the Smithy! Amazing!\n\n");
	else
		printf("Smithy passed %d tests and failed %d tests, check above for which ones.\n\n", pass, fail);
		
	return 0;
}