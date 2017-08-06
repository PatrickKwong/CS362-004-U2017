/***********************
 *testGreatHallFunc.c
 *
 *
 * Description: the unit testing file
***********************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"




int main(){
	struct gameState* state = newGame();
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
		smithy, village, baron, great_hall};
	initializeGame(2, k, 1000, state);
	int passed = 1;
	printf("Executing great hall test...\n");

	int callit = great_HallFunc(1, state, 1);

	if (callit == 0){
		printf("Test is passed!\n");
	}
	else{
		printf("Test has failed!\n");
	}

	return 0;
}


