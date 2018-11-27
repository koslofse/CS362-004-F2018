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
#include <time.h>


#define TESTCARD "village"

int main() {
	// random number seed
	srand(time(0)); 

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Current player should have same net amount of cards (play village, but gain a card) --------------
	printf("TEST 1: Current player should have same net amount of cards (play village, but gain a card)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// randomize player hand
	int i;
	for (i=0; i<numHandCards(&testG); i++ ){
			// random number corresping to 27 possible cards
			int num = rand() % 27;
			testG.hand[testG.whoseTurn][i] = num;
	}

	// make sure at least one card is a smithy by assigning village to random index in hand
	int num = rand() % numHandCards(&testG);
	testG.hand[testG.whoseTurn][num] = village;


	int playerHandCardsBefore = numHandCards(&testG);

	//go to 2nd players turn
	endTurn(&testG);

	// play village
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	int playerHandCardsAfter = numHandCards(&testG);

	// player should have same amount of hand cards
	if(playerHandCardsBefore == playerHandCardsAfter){
		printf("PASS - TEST 1: player still has same amount of hand cards\n");
	}
	else{
		printf("FAIL - TEST 1: player does not still have same amount of hand cards\n");
	}

	// ----------- TEST 2: Number of actions should increase by 2 --------------
	printf("TEST 2: 3 cards should come from player's own pile\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// randomize player hand
	for (i=0; i<numHandCards(&testG); i++ ){
			// random number corresping to 27 possible cards
			int num = rand() % 27;
			testG.hand[testG.whoseTurn][i] = num;
	}

	// make sure at least one card is a smithy by assigning village to random index in hand
	 num = rand() % numHandCards(&testG);
	testG.hand[testG.whoseTurn][num] = village;



	//go to 2nd players turn
	endTurn(&testG);

	int numOfActionsBefore = testG.numActions;

	// play village
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	int numOfActionsAfter = testG.numActions;

	int netGain = numOfActionsAfter - numOfActionsBefore;

	// num of actions should increase by two
	if(netGain == 2){
		printf("PASS - TEST 2: number of actions has increased by two\n");
	}
	else{
		printf("FAIL - TEST 2: number of actions has not increased by %d\n", netGain);
	}





	// ----------- TEST 3: No state change should occur for other players --------------
	printf("TEST 3: No state change should occur for other players\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// randomize player hand
	for (i=0; i<numHandCards(&testG); i++ ){
			// random number corresping to 27 possible cards
			int num = rand() % 27;
			testG.hand[testG.whoseTurn][i] = num;
	}

	// make sure at least one card is a smithy by assigning village to random index in hand
	 num = rand() % numHandCards(&testG);
	testG.hand[testG.whoseTurn][num] = village;

	//go to 2nd players turn in both games
	endTurn(&testG);

	//go to 2nd players turn in both games
	endTurn(&G);

	// play village
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	int noStateChangeOtherPlayer = 1;

	// compare player 1's hand, before and after
	if (testG.handCount[0] != G.handCount[0]){
		noStateChangeOtherPlayer = 0;
		printf("FAIL - TEST 3: other player's hand count has changed\n");
	}
	
	// compare player 1's deck, before and after
	if (testG.deckCount[0] != G.deckCount[0]){
		noStateChangeOtherPlayer = 0;
		printf("FAIL - TEST 3: other player's deck count has changed\n");
	}

	// compare player 1's discard pile, before and after
	if (testG.discardCount[0] != G.discardCount[0]){
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
	
	// randomize player hand
	for (i=0; i<numHandCards(&testG); i++ ){
			// random number corresping to 27 possible cards
			int num = rand() % 27;
			testG.hand[testG.whoseTurn][i] = num;
	}

	// make sure at least one card is a smithy by assigning village to random index in hand
	 num = rand() % numHandCards(&testG);
	testG.hand[testG.whoseTurn][num] = village;

	//go to 2nd players turn in both games
	endTurn(&testG);

	//go to 2nd players turn in both games
	endTurn(&G);

	
	// play village
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

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


