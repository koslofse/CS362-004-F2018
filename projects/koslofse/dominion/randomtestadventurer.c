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

#define TESTCARD "adventurer"

int main() {
	// randome number seed
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
	printf("(last 2 cards in deck are gold/first 3 estate cards)\n");


	// ----------- TEST 1: Current player should have net gain of 2 hand cards and both should be treasure cards --------------
	printf("TEST 1: Current player should have net gain of 2 hand cards and both should be gold\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// array of possible treasure cards
	int treasureCards[] = {copper, silver, gold};

	// array of possible non-treasure cards
	int nonTreasureCards[] = {curse, estate, duchy, province,
	adventurer, council_room, feast,  gardens, mine, remodel, smithy,
   village, baron,  great_hall,  minion, steward, tribute, ambassador, cutpurse,
   embargo,  outpost,salvager, sea_hag, treasure_map};
	

	// set hand to have random treasure card in odd positions and random non-treasure cards in even positions
	int i;
	for (i = 0; i < testG.deckCount[0]; i++){
		if (i>1){
			int num = rand() % 23;
			testG.deck[0][i] = nonTreasureCards[num];
		}
		else{
			int num = rand() % 2;
			testG.deck[0][i] = treasureCards[num];
		}
	}

	// play adventurer
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	int playerHandCards = numHandCards(&testG);

	int has7HandCards = 0;
	int last2HandCardsAreGold = 0;

	// player should have 7 hand cards
	if(playerHandCards == 7){
		has7HandCards = 1;
	}
	else{
		printf("FAIL - TEST 1: player does not have 7 hand cards\n");
	}

	// last 2 hands cards should be a treasure card
	if( ((testG.hand[0][testG.handCount[0]-1] == copper) || (testG.hand[0][testG.handCount[0]-1] == silver) ||
	(testG.hand[0][testG.handCount[0]-1] == gold))
	&&
	((testG.hand[0][testG.handCount[0]-2] == copper) || (testG.hand[0][testG.handCount[0]-2] == silver) ||
	(testG.hand[0][testG.handCount[0]-2] == gold)) ){
		printf("PASS - TEST 1: player's last 2 hands cards are treasure cards\n");
	}
	else{
		printf("FAIL - TEST 1: player's last 2 hands cards are not treasure cards\n");
	}

	if (last2HandCardsAreGold && has7HandCards){
		printf("PASS - TEST 1: player has net gain of 2 hand cards and both are golds\n");
	}







	// ----------- TEST 2: 3 estates should be in discard pile are deck should be empty  --------------
	printf("TEST 2: 3 estates should be in discard pile are deck should be empty\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));


	// set hand to have random treasure card in odd positions and random non-treasure cards in even positions
	for (i = 0; i < testG.deckCount[0]; i++){
		if (i>1){
			int num = rand() % 23;
			testG.deck[0][i] = nonTreasureCards[num];
		}
		else{
			int num = rand() % 2;
			testG.deck[0][i] = treasureCards[num];
		}
	}
 
 	drawCard(0, &testG);


	// play adventurer
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	int deckCountIsZero = 0;
	int discardPileIs3 = 0;

	// deck count should be zero
	if(testG.deckCount[0] == 0){
		deckCountIsZero = 1;
	}
	else{
		printf("FAIL - TEST 2: deck count is not zero\n");
	}

	// discard pile should be 3
	if(testG.discardCount[0] == 3){
		discardPileIs3 = 1;
	}
	else{
		printf("FAIL - TEST 2: discard pile is not 3\n");
	}

	if (discardPileIs3 && deckCountIsZero){
		printf("PASS - TEST 1: 3 estates are in discard pile are deck is empty\n");
	}



	// ----------- TEST 3: No state change should occur for other players --------------
	printf("TEST 3: No state change should occur for other players\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// set hand to have random treasure card in odd positions and random non-treasure cards in even positions
	for (i = 0; i < testG.deckCount[0]; i++){
		if (i>1){
			int num = rand() % 23;
			testG.deck[0][i] = nonTreasureCards[num];
		}
		else{
			int num = rand() % 2;
			testG.deck[0][i] = treasureCards[num];
		}
	}

	// play adventurer
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

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


	// set deck to have gold in odd positions and estates in even positions
	for (i = 0; i < testG.deckCount[0]; i++){
		if (i>1){
			testG.deck[0][i] = estate;
		}
		else{
			testG.deck[0][i] = gold;
		}
	}

	// play adventurer
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

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


