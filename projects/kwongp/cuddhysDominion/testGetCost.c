/*************************************
 *testGetCost.c
 *
 *Description: Unit test for the getCost() function
**************************************/

#ifndef DOMINION_H
#define DOMINION_H


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


int main(int argc, char* argv[]){

	struct gameState* state = newGame();
	printf("Testing getCost()....\n");
	int handPos = 0;
	int i;
	int temp;
	int passed = 1;
	int seed = 1000;
	int values[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};

	//test valid numbers
	temp = getCost(-1);
	if(temp != -1) {passed = 0;}

	temp = getCost(28);
	if (temp != -1) {passed = 0;}
	
	//test values return correctly 
	for(i = 0; i < 27; i++){
		temp = getCost(i);
		if (temp != values[i]){
			passed = 0;
			break;
		}
	}

	if(passed == 1){
		printf("getCost passed!\n");
	}
	else{
		printf("getCost failed\n");
	}

	free(state); //free from malloc call
	return 0;
}



#endif
