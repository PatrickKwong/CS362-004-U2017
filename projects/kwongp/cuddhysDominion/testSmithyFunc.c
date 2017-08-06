/************************
 *
 *testSmithyFunc.c
*************************/



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main (int argc, char* argv[]){
	int i;
	int seed = 1000;
	int numPlayer = 2;
	int currentPlayer = 1;
	int k[10] ={adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron,
		great_hall};
	struct gameState * state = newGame();
	initializeGame(numPlayer, k, 1000, state);
	
	printf("Executing the smithyFunc test...\n");
	printf("Handcount before function: %d\n", state->handCount[currentPlayer]);
	int before = state->handCount[currentPlayer];
	
	
	
	smithyFunc(currentPlayer, state, 1);
	printf("Handcount after function: %d\n", state->handCount[currentPlayer]);
	int after = state->handCount[currentPlayer];
	int sum = after - before;

	if(sum == 2){
		printf("SmithyFunc test passed!\n");
	}
	else{
		printf("SmithyFunc test has failed!\n");
	}

	return 0;
}
