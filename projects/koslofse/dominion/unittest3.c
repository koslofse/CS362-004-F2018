/*
 * unittest3.c
 *
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "getCost"

int main() {
	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);



	// ----------- TEST 1: invalid card number should return -1 --------------
	printf("TEST 1: invalid card number should return -1\n");

	// with no province cards, game should be over
	if(getCost(50) == -1){
		printf("PASS - invalid card number returns -1\n");
	}
	else{
		printf("PASS - invalid card number does not return -1\n");
	}

	// ----------- TEST 2: all valid card numbers should return value of 0 or greater --------------
	printf("TEST 2: all valid card numbers should return value of 0 or greater\n");
	int i;
	int invalidCardFound = 0;
	for(i=0; i < 27; i++){
		if(getCost(i) == -1){
			printf("FAIL - valid card number %d did not return value of 0 or greater\n", i);
			invalidCardFound = 1;
		}
	}
	
	if(!invalidCardFound){
		printf("PASS - all valid card numbers returned value of 0 or greater\n");
	}

	printf("TEST SUCCESSFULLY COMPLETED\n");

	return 0;
}


