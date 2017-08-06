/*************************
 *testGetWinners.c
 *
 * Description: unit test for testGetWinners.c
**************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"



int main(int argc, char* argv[]){
	
	printf("Executing testGetWinners...\n");
	int players[MAX_PLAYERS];
	struct gameState* state = newGame();
	state->numPlayers = 4;
	int passed = 1;
	int i;

	//Setting player scores
	players[0] = 0;
	players[1] = 1;
	players[2] = 2;
	players[3] = 3;


	//Basic function call, get Winners should pick the winner correctly
	getWinners(players, state);
	if(players[3] != 1){ passed = 0; }





	if(passed == 1){
		printf("getWinners test passed!\n");
	}
	else{
		printf("getWinners test failed!\n");
	}

	return 0;
}
