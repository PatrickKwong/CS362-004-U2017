/* -----------------------------------------------------------------------
 * CS362-004 Summer 2017 Assignment 5
 * unittest1.c
 * 
 * Patrick Kwong
 * kwongp@oregonstate.edu
 *
 * Unit test for dominion function getCost using teammate(cuddhys)'s dominion code
 * - getCost returns the value of the card
 *
 * -----------------------------------------------------------------------
 * Include the following lines in the makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>

// testResult
// checks if the provided testCost from getCost against the provide correct
// returns 1 if getCost's cost doesn't make cost from rules
// return 0 if getCost's cost does make cost from rules
int testResult(int testCost, int correctCost)
{
    if(testCost != correctCost)
    {
        printf("BUG!!! The cost from getCost function did not match the cost from rules.\n\n");
        return 1;
    }
    else
        printf("Great! The cost from getCost function matched the cost from rules.\n\n");
        return 0;
}

int main() 
{
    int testCost, correctCost;
    int bugCount = 0;

    printf("Testing getCost function...\n");
    printf("Checking the costs from getCost function in dominion.c against\n");
    printf("the costs at http://wiki.dominionstrategy.com/index.php/List_of_cards\n");
    printf("---------------------------------------------------------------------\n\n");

    // curse card
    testCost = getCost(curse);
    correctCost = 0;
    printf("Testing curse:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {    
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // estate card
    testCost = getCost(estate);
    correctCost = 2;
    printf("Testing estate:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // duchy card
    testCost = getCost(duchy);
    correctCost = 5;
    printf("Testing duchy:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // province card
    testCost = getCost(province);
    correctCost = 8;
    printf("Testing province:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // copper card
    testCost = getCost(copper);
    correctCost = 0;
    printf("Testing copper:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // silver card
    testCost = getCost(silver);
    correctCost = 3;
    printf("Testing silver:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // gold card
    testCost = getCost(gold);
    correctCost = 6;
    printf("Testing gold:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // adventurer card
    testCost = getCost(adventurer);
    correctCost = 6;
    printf("Testing adventurer:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // council_room card
    testCost = getCost(council_room);
    correctCost = 5;
    printf("Testing council_room:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // feast card
    testCost = getCost(feast);
    correctCost = 4;
    printf("Testing feast:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // gardens card
    testCost = getCost(gardens);
    correctCost = 4;
    printf("Testing gardens:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // mine card
    testCost = getCost(mine);
    correctCost = 5;
    printf("Testing mine:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // remodel card
    testCost = getCost(remodel);
    correctCost = 4;
    printf("Testing remodel:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // smithy card
    testCost = getCost(smithy);
    correctCost = 4;
    printf("Testing smithy:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // village card
    testCost = getCost(village);
    correctCost = 3;
    printf("Testing village:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // baron card
    testCost = getCost(baron);
    correctCost = 4;
    printf("Testing baron:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // great_hall card
    testCost = getCost(great_hall);
    correctCost = 3;
    printf("Testing great_hall:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // minion card
    testCost = getCost(minion);
    correctCost = 5;
    printf("Testing minion:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // steward card
    testCost = getCost(steward);
    correctCost = 3;
    printf("Testing steward:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // tribute card
    testCost = getCost(tribute);
    correctCost = 5;
    printf("Testing tribute:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // ambassador card
    testCost = getCost(ambassador);
    correctCost = 3;
    printf("Testing ambassador:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // cutpurse card
    testCost = getCost(cutpurse);
    correctCost = 4;
    printf("Testing cutpurse:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // embargo card
    testCost = getCost(embargo);
    correctCost = 2;
    printf("Testing embargo:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // outpost card
    testCost = getCost(outpost);
    correctCost = 5;
    printf("Testing outpost:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // salvager card
    testCost = getCost(salvager);
    correctCost = 4;
    printf("Testing salvager:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // sea_hag card
    testCost = getCost(sea_hag);
    correctCost = 4;
    printf("Testing sea_hag:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // treasure_map card
    testCost = getCost(treasure_map);
    correctCost = 4;
    printf("Testing treasure_map:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {  
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);
    }

    // market card - why isn't this base card in the dominion.c?
    /*
    testCost = getCost(market);
    correctCost = 5;
    printf("Testing market:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);        
    }

    // militia card - why isn't this base card in the dominion.c?
    testCost = getCost(militia);
    correctCost = 2;
    printf("Testing militia:\n");
    if(testCost < 0)
        printf("getCost failed to provide cost for this card.\n");
    else
    {
        printf("Cost from getCost function: %d coins\n",testCost);
        printf("Cost from dominionstrategy: %d coins\n",correctCost);
        bugCount += testResult(testCost, correctCost);        
    }
    */


    // output the test results overall
    printf("-----------------------------------------\n");
    printf("Final Testing results of getCost function\n");
    printf("-----------------------------------------\n");
    if(bugCount == 0)
        printf("All tests passed for the getCost function!\n\n");
    else
        printf("getCost failed to get correct cost for %d cards(s), check above for which ones.\n\n", bugCount);
    
    return 0;
}
