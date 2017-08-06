/* -----------------------------------------------------------------------
 * CS362-004 Summer 2017 Assignment 5
 * randomtestadventurer.c
 *
 * Patrick Kwong
 * kwongp@oregonstate.edu
 * 
 * Random test generator for Adventurer using teammate(cuddhys)'s dominion code
 * - reveal cards from deck until you reveal 2 treasure cards
 * - put 2 treasure cards in hand and discarded other revealed cards
 * 
 * Used provided cardtest4.c, dominion.c, and testUpdateCoins.c provided code
 * -----------------------------------------------------------------------
 * Include the following lines in the makefile:
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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

// prototype
int adventurerFunc(int currentPlayer, struct gameState *state);

int main() {
    int i, j, r, z;
    int numPlayer;
    int bugCount = 0;
    int flag = 0; // flag for other player piles
    int prevCount, afterCount;
	struct gameState G, prevG;
	int seed = 1000;
	srand(time(NULL));
	int k[10]; // for kingdom cards
	int numKingdomCards;
	bool haveCard;
	int treasureNum, treasureDraw;
	int pass = 0; // track the number of passes
	int fail = 0; // track the number of fails
	
	printf("----------------------------------------------\n");		
	printf(" Testing Random Test Generator for Adventurer\n");
	printf("----------------------------------------------\n");	
	
	for(z = 1; z <= TEST_RUNS; z++) // test for loop
	{
		// random kingdom cards set (9 random with adventurer card)
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
		// now with random set, we have to make sure adventurer card is in the kingdom pile
		// if not we'll randomly replace one of the 10 kindgom cards with an adventurer.
		haveCard = false;
		// check 10 kingdom pile for adventurer
		for(i = 0; i < 10; i++)
		{
			if(k[i] == adventurer)
			{
				haveCard = true;
			}
		}
		// no adventurer found, have to randomly add it.
		if(!haveCard)
		{
			r = (rand() % 10); // random position
			k[r] = adventurer;
		}
		
		// random number of players from 2 to 5
		numPlayer = ((rand() % 3) + 2);

		printf("------------------------------------\n");
		printf(" Starting Test #%d for Adventurer\n", z);
		printf("------------------------------------\n");
		
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
		treasureNum = 0; 
		treasureDraw = 0;
		bugCount = 0;
		
		// get the number of treasures in deck
		for(i = 0; i < G.deckCount[0]; i++)
			if(G.deck[0][i] == copper || G.deck[0][i] == silver || G.deck[0][i] == gold)
				treasureNum++;
			
		printf("\nNumber of treasures in deck: %d.\n", treasureNum);
		
		// calculated expected treasure to draw from adventure card
		if(treasureNum == 0)
			treasureDraw = 0;
		else if(treasureNum == 1)
			treasureDraw = 1;
		else
			treasureDraw = 2;	
		
		memcpy(&prevG, &G, sizeof(struct gameState)); //create clone of game state to run tests on
		
		// adventurer_func(&G); // my previous code
		// modifications to be able to use teammates's adventurer function
		int currentPlayer = 0;
		adventurerFunc(currentPlayer, &G);
		
		/* tried cardEffect instead of my refactored function
		int handPos, choice1, choice2, choice3, bonus;
		choice1 = choice2 = choice3 = bonus = 0;
		
		// find hand position of adventurer card
		for(i = 0; i < G.handCount[0]; i++)
		{
			if(G.hand[0][i] == adventurer)
			{
				handPos = i;
			}
		}
		
		cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);
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
		
		// get hand counts
		prevCount = prevG.handCount[0];
		afterCount = G.handCount[0];
				
		// check if correct number of cards after adventurer card
		printf("\nChecking if correct number of cards after using Adventurer.\n");
		printf("Previous hand count: %d, After Adventurer: %d\n", prevCount, afterCount);
		printf("Expected hand count after Adventurer: %d\n", (prevCount + (treasureDraw - 1)));
		if((prevCount + (treasureDraw - 1)) != G.handCount[0])
		{
			printf("Bug!!! Ended with the incorrect number of cards in hand after Adventurer.\n");
			bugCount++;
		}
		else
			printf("Great! Ended with the correct number of cards in hand after Adventurer.\n");

		// check if adventurer added the only treasure cards to hand 
		printf("\nChecking if Adventurer adds only treasure cards to hand.\n");
		if(G.hand[0][G.handCount[0]-2] != copper && G.hand[0][G.handCount[0]-2] != silver && G.hand[0][G.handCount[0]-2] != gold)
		{
			printf("Bug!!! Adventurer added a card beside a treasure.\n");
			bugCount++;
		}
		else if(G.hand[0][G.handCount[0]-1] != copper && G.hand[0][G.handCount[0]-1] != silver && G.hand[0][G.handCount[0]-1] != gold)
		{
			printf("Bug!!! Adventurer added a card beside a treasure.\n");
			bugCount++;
		}
		else
			printf("Great! Adventurer added only treasure cards to hand.\n");

		// check if adventurer drew enough cards from deck 
		printf("\nChecking if Adventurer drew enough cards to hand.\n");
		if(prevG.deckCount[0] - treasureDraw < G.deckCount[0])
		{
			printf("Bug!!! Adventurer didn't draw enough cards from the deck.\n");
			bugCount++;
		}
		else
			printf("Great! Adventurer drew enough cards from deck.\n");

		// check if adventurer discarded the correct number cards to hand 
		printf("\nChecking if Adventurer card discarded correct number of cards to hand.\n");
		printf("Previous deck count: %d cards, After Adventurer: %d cards\n", prevG.deckCount[0], G.deckCount[0]);    
		printf("Previous discard count: %d cards, After Adventurer: %d cards\n", prevG.discardCount[0], G.discardCount[0]);
		printf("Expected deck count after Adventurer: %d card.\n", (prevG.deckCount[0] - treasureDraw));
		if((prevG.deckCount[0] - G.deckCount[0]) == (G.deckCount[0] - prevG.deckCount[0] + 1))
		{
			printf("Bug!!! Adventurer discarded the incorrect number of cards to hand.\n");
			bugCount++;
		}
		else
			printf("Great! Adventurer discarded the correct number of cards to hand.\n");

		// check if adventurer altered other player's cards
		printf("\nChecking if adventurer card altered other player's hand.\n");
		if(prevG.handCount[1] != G.handCount[1])
		{
			printf("Bug!!! Adventurer altered other player's cards\n");
			bugCount++;
		}
		else if(prevG.deckCount[1] != G.deckCount[1])
		{
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
		printf("\nChecking if Adventurer altered the Victory and Kingdom piles.\n");
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
			printf("Bug!!! Kingdom/Victory supplies have been altered!\n");
			bugCount++;
		}
		
		// output the test results overall
		printf("--------------------------------------------------\n");
		printf("Test #%d results for Adventurer\n", z);
		printf("--------------------------------------------------\n");

		if(bugCount == 0)
		{
			printf("All tests passed for the Adventurer!\n\n");
			pass++;
		}
		else
		{
			printf("Adventurer failed for %d condition(s), check above for which ones.\n\n", bugCount);
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
	printf("Final Testing results for Adventurer\n");
	printf("---------------------------------------------------\n");

	if(fail == 0)
		printf("All tests passed for the Adventurer! Amazing!\n\n");
	else
		printf("Adventurer passed %d tests and failed %d tests, check above for which ones.\n\n", pass, fail);
		
	return 0;
}