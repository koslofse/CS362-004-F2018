/*
 * unittest2.c
 *
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "isGameOver"

int main() {

    int seed = 1000;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);



	// ----------- TEST 1: game has just started, should not be over --------------
	printf("TEST 1: game has just started, should not be over\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// with no province cards, game should be over
	if(!isGameOver(&testG)){
		printf("PASS - game has just started, and is not yet over\n");
	}
	else{
		printf("FAIL - game has just started, but is already over\n");
	}


		// ----------- TEST 2: if three supply piles are at 0, the game should be over --------------
	printf("TEST 2: if three supply piles are at 0, the game should be over \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));


	// set supply of all piles to zero
	int i = 0;
	for (i = 0; i < 25; i++){
		testG.supplyCount[i] = 0;
	}

	//if three supply piles are at 0, the game should be over
	if(isGameOver(&testG)){
		printf("PASS - three supply piles are at 0, and the game is over\n");
	}
	else{
		printf("FAIL - three supply piles are at 0, and the game is not over\n");
	}


	// ----------- TEST 3: with no province cards, game should be over --------------
	printf("TEST 3: with no province cards, game should be over\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// set supply count of provice cards to zero
	testG.supplyCount[province] = 0;

	// with no province cards, game should be over
	if(isGameOver(&testG)){
		printf("PASS - with no province cards, game is over\n");
	}
	else{
		printf("FAIL - with no province cards, game is not over\n");
	}


	printf("TEST SUCCESSFULLY COMPLETED\n");


	return 0;
}


