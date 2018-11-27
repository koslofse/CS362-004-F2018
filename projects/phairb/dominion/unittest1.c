/*
 * unittest1.c
 *
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "endTurn"

int main() {
    int seed = 1000;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	// ----------- TEST 1: player turn changes --------------
	printf("TEST 1: player turn changes\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// call whoseTurn function before end turn
	int playerBeforeEndTurn = whoseTurn(&testG);
	endTurn(&testG);

	// call whoseTurn function after end turn
	int playerAfterEndTurn = whoseTurn(&testG);

	// if current player after end turn has changed, pass
	if (playerBeforeEndTurn != playerAfterEndTurn){
			printf("PASS: Current player changed after turn ended\n");
	}
	else{
		printf("FAIL: Current player did not change after turn ended\n");
	}




// ----------- TEST 2: player hand count is empty after turn ends --------------
	printf("TEST 2: player hand count is empty after turn ends\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	int currentplayer = whoseTurn(&testG);

	// get hand count of player after turn ends
	endTurn(&testG);
	int playerHandCount = testG.handCount[currentplayer];


	// if current player hand count after end turn is 0, pass
	if (playerHandCount == 0){
		printf("PASS: player hand count is empty after turn ends\n");
	}
	else{
		printf("FAIL: player hand count is not empty after turn ends\n");
	}

// ----------- TEST 3: next player's hand count is 5 after other player's turn ends --------------
	printf("TEST 3: player hand count is empty after turn ends\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	currentplayer = whoseTurn(&testG);

	// get hand count of player after turn ends
	playerHandCount = testG.handCount[currentplayer];


	// if next player hand count after end turn is 5, pass
	if (playerHandCount == 5){
		printf("PASS: next player's hand count is 5 after other player's turn ends\n");
	}
	else{
		printf("FAIL: next player's hand count is not 5 after other player's turn ends\n");
	}

	printf("TEST SUCCESSFULLY COMPLETED\n");

	return 0;
}


