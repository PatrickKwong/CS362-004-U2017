/****************************************
 *testAdventureFunc.c
 *
 * Description: unit test for adventureFunc()
****************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main(int argc, char* argv[]){
	printf("Executing adventureFuncTesting...\n");
	
	int currentPlayer = 1;
	struct gameState* state = newGame();
	int k[10] ={adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron,
		great_hall};
	int passed = 1;
	int x;

	initializeGame(MAX_PLAYERS, k, 1000, state);

	
	//call without deck shuffle
	state->deckCount[1] = 1;
	x = adventurerFunc(currentPlayer, state); 
	if (x != 0) { passed = 0; }


	//call with deck shuffle
	state->deckCount[1] = 0;
	x = adventurerFunc(currentPlayer, state);
	if (x != 0) { passed = 0; }


	if(passed == 1){
		printf("adventureFunc test passed!\n");
	}
	else {
		printf("adventureFunct test failed!\n");
	}


	free(state);
	return 0; 
}


