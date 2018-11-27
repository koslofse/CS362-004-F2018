/*
 * cardtest1.c
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "salvager"

int main() {

    int handpos, choice1 = 1, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: if player trashes card, they should recieve the gold it costs --------------
	printf("TEST 1: if player trashes card, they should recieve the gold it costs\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// put estate in hand position 0
	handpos = 0;
	testG.hand[0][handpos] = estate;

	int coinsBefore = testG.coins;

	// play salvager
	cardEffect(salvager, 2, choice2, choice3, &testG, handpos, &bonus);
	
	int coinsAfter = testG.coins;

	if (coinsAfter - coinsBefore == 2){
		printf("PASS - TEST 1: 2 coins were gained\n");
	}
	else{
		printf("FAIL - TEST 1: 2 coins were not gained\n");

	}






	// ----------- TEST 2: number of buys should increase by 1 --------------
	printf("TEST 2: number of buys should increase by 1\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// put estate in hand position 0
	handpos = 0;
	testG.hand[0][handpos] = estate;

	int numBuysBefore = testG.numBuys;

	// play salvager
	cardEffect(salvager, 2, choice2, choice3, &testG, handpos, &bonus);
	
	int numBuysAfter = testG.numBuys;

	if (numBuysAfter - numBuysBefore == 1){
		printf("PASS - TEST 2: number of buys increased by 1\n");
	}
	else{
		printf("FAIL - TEST 2: number of buys did not increase by 1\n");

	}




	// ----------- TEST 3: No state change should occur for other players --------------
	printf("TEST 3: No state change should occur for other players\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// play salvager
	cardEffect(salvager, choice1, choice2, choice3, &testG, handpos, &bonus);

	int noStateChangeOtherPlayer = 1;

	// compare player 1's hand, before and after
	if (testG.handCount[1] != G.handCount[1]){
		noStateChangeOtherPlayer = 0;
		printf("FAIL - TEST 3: other player's hand count has changed\n");
	}
	
	// compare player 1's deck, before and after
	if (testG.deckCount[1] != G.deckCount[1]){
		noStateChangeOtherPlayer = 0;
		printf("FAIL - TEST 3: other player's deck count has changed\n");
	}

	// compare player 1's discard pile, before and after
	if (testG.discardCount[1] != G.discardCount[1]){
		noStateChangeOtherPlayer = 0;
		printf("FAIL - TEST 3: other player's discard count has changed\n");
	}

	if(noStateChangeOtherPlayer){
		printf("PASS - TEST 3: No state change has occurred for other player\n");
	}


	// ----------- TEST 4: No state change should occur to the victory card piles and kingdom card piles --------------
	printf("TEST 4: No state change should occur to the victory card piles and kingdom card piles\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// play salvager
	cardEffect(salvager, choice1, choice2, choice3, &testG, handpos, &bonus);

	int noStateChangeVictory = 1;
	int noStateChangeKingdom = 1;

	// check to make sure victory cards havent changed
	if(G.supplyCount[estate] != testG.supplyCount[estate]){
		noStateChangeVictory = 0;
		printf("FAIL - TEST 4: estate count has changed\n");
	}
	if(G.supplyCount[duchy] != testG.supplyCount[duchy]){
		noStateChangeVictory = 0;
		printf("FAIL - TEST 4: duchy count has changed\n");
	}
	if(G.supplyCount[province] != testG.supplyCount[province]){
		noStateChangeVictory = 0;
		printf("FAIL - TEST 4: province count has changed\n");
	}

	// check to make sure kingdom cards havent changed
	int i;
  	for (i = adventurer; i <= treasure_map; i++){
		if(G.supplyCount[i] != testG.supplyCount[i]){
			noStateChangeKingdom = 0;
			printf("FAIL - TEST 4: kingdom card %d count has changed\n", i);
		}
	}

	if (noStateChangeVictory && noStateChangeKingdom){
		printf("PASS - TEST 4: No state change occurred to the victory card piles or kingdom card piles\n");
	}

	printf("TEST SUCCESSFULLY COMPLETED\n");

	return 0;
}


