/*
 * unittest4.c
 *
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "numHandCards"

int main() {

    int seed = 1000;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);



	// ----------- TEST 1: player's turn has just started, should have 5 hand cards --------------
	printf("TEST 1: player's turn has just started, should have 5 hand cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	int player0HandCards = numHandCards(&testG);

	// player's turn has just started, should have 5 hand cards
	if(player0HandCards == 5){
		printf("PASS - player's turn has just started, has 5 hand cards\n");
	}
	else{
		printf("FAIL - player's turn has just started, does not have 5 hand cards\n");
	}




	// ----------- TEST 2: player draws card, should now have 6 hand cards --------------
	printf("TEST 2: player draws card, should now have 6 hand cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// draw card
	drawCard(testG.whoseTurn, &testG);
	player0HandCards = numHandCards(&testG);

	// player drew card, should have 6 hand cards
	if(player0HandCards == 6){
		printf("PASS - TEST 2: player drew card, now has 6 hand cards\n");
	}
	else{
		printf("FAIL - TEST 2: player drew card, but does not have 6 hand cards\n");
	}




	// ----------- TEST 3: player discards card, should have 4 hand cards --------------
	printf("TEST 3: player discards card, should have 4 hand cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// discard card
	discardCard(0, testG.whoseTurn, &testG, 1);
	player0HandCards = numHandCards(&testG);

	// player discards card, should have 4 hand cards
	if(player0HandCards == 4){
		printf("PASS - TEST 2: player discarded card, now has 4 hand cards\n");
	}
	else{
		printf("FAIL - TEST 2: player discarded card, but does not have 4 hand cards\n");
	}


	printf("TEST SUCCESSFULLY COMPLETED\n");



	return 0;
}


