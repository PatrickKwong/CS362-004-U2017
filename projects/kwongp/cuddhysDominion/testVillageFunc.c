/*********************
 *villageTestFunc
 *
 *
 *
*********************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main(){
	int i;
	int seed = 1000;
	int numPlayer = 2;
	int passed = 1;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
	    smithy, village, baron, great_hall};
	struct gameState* state = newGame();
	initializeGame(numPlayer, k, seed, state);
	printf("Executing VillageFuncTest...\n");
	int cardBefore = state-> handCount[1];
	int actionBefore = state-> numActions;
	villageFunc(1, state, 1);
	int cardAfter = state->handCount[1];
	int actionAfter = state->numActions;

	int cardSum = cardAfter - cardBefore;
	int actionSum = actionAfter = actionBefore;

	if (cardSum != 0) {passed = 0; }
	if (actionSum != 2) {passed = 0; }

	if(passed == 1){
		printf("Test passed!\n");
	}
	else{
		printf("Test failed!\n");
	}

	return 0;
}


