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

#define TESTCARD "smithy"

int main() {

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Current player should have net gain of 2 hand cards (draw 3 cards, discard smithy card) --------------
	printf("TEST 1: Current player should have net gain of 2 hand cards (draw 3 cards, discard smithy card)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// play smithy
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	int playerHandCards = numHandCards(&testG);

	// player should have 7 hand cards
	if(playerHandCards == 7){
		printf("PASS - TEST 1: player now has 7 hand cards\n");
	}
	else{
		printf("FAIL - TEST 1: player has %d hand cards\n", playerHandCards);
	}



	// ----------- TEST 2: 3 cards should come from player's own pile --------------
	printf("TEST 2: 3 cards should come from player's own pile\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	int playerDeckCountBefore = testG.deckCount[testG.whoseTurn];

	// play smithy
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	int playerDeckCountAfter = testG.deckCount[testG.whoseTurn];

	int netLoss = playerDeckCountBefore - playerDeckCountAfter;

	// player should lose 3 cards from their own pile
	if(netLoss == 3){
		printf("PASS - TEST 2: player lost 3 cards from their own pile\n");
	}
	else{
		printf("FAIL - TEST 2: player lost %d cards from their own pile\n", netLoss);
	}





	// ----------- TEST 3: No state change should occur for other players --------------
	printf("TEST 3: No state change should occur for other players\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// play smithy
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

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

	// play smithy
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

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


