/**************************************
 *testisGameOver.c
 *
 *Description: Unit testing file for isGameOver() function
**************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>




int main(int argc, char *argv[]){
	struct gameState* state = newGame();

	//check stack of province cards, empty and non-empty
	int i;
	int passed = 1;
	int temp;

	//Province cards available, no empty supplies
	//function should return 0;
	state->supplyCount[province] = 1;
	for(i = 0; i < 25; i++){
		state->supplyCount[i] = 1;
	}
	temp = isGameOver(state);
	if (temp != 0){ passed = 0; }

	//Province cards not available
	//should return 1
	state->supplyCount[province] = 0;
	temp = isGameOver(state);
	if (temp != 1) { passed = 0; }


	//more than three supply cards are empty
	//should return 1
	state->supplyCount[1] = 1;
	state->supplyCount[5] = 1;
	state->supplyCount[25] = 1;
	temp = isGameOver(state);
	if (temp != 1) { passed = 0; }




	if(passed == 1){
		printf("isGameOver test passed!\n");
	}
	else{
		printf("GameOver test failed!\n");
	}

	free(state);
	return 0;
}

