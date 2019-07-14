/*
 * unittest3 -- Ambassador
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "ambassador"

int main() {
  /*
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
  */
  int handpos = 0, choice1 = 0, choice2 = 0; //, choice3 = 0, bonus = 0;
    //    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, ambassador};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    //int currentPlayer = whoseTurn(&G);
    int currentPlayer = 0;
      
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    
    // establish a dummy hand
    G.hand[currentPlayer][0] = ambassador;
    G.hand[currentPlayer][1] = copper;
    G.hand[currentPlayer][2] = estate;
    G.hand[currentPlayer][3] = estate;
    G.hand[currentPlayer][4] = village;

    // ----------- TEST 1 - 2: player reveals card, selects 0-1 copies --------------
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    printf(" - Player's hand has:  ");
    for (int k = 0; k < 5; k++)
      printf("%d ", testG.hand[currentPlayer][k]);
    printf("\n");
    //loop through choosing 0, 1, or 2 copies
    for (int j = 0; j < 2; j++)
      {
	printf("TEST %d: player reveals a card, selects %d copies\n", j+1, j);
	// loop throught the other 4 cards
	for (int i = 1; i < 5; i++)
	  {
	    memcpy(&testG, &G, sizeof(struct gameState));
	    choice1 = i;
	    choice2 = j;
	    int goodRun = ce_Ambassador(choice1, choice2, &testG, handpos);
	    printf(" - Returns %d with card %d\n", goodRun, choice1);
	    if (goodRun == 0)
	      printf(" - Passed %d copy/copies\n", j);
	    else
	      printf(" - Failed %d copy/copies, returned %d \n", j, goodRun);

	    printf(" - player handCount is %d\n", testG.handCount[currentPlayer]);
	  }
      }

    // ----------- TEST 3, ask for 2 valid copies --------------
    printf("TEST 3: player reveals a card, selects 2copies\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    choice1 = 2;
    choice2 = 2;
    int goodRun = ce_Ambassador(choice1, choice2, &testG, handpos);
    if (goodRun == 0)
      printf(" - Passed 2 copies\n");
    else
      printf(" - Failed 2 copies, Ambassador returned %d \n", goodRun);
    
    // ----------- TEST 4, ask for invalid numer of copies --------------
    printf("TEST 4: player reveals a card, doesn't have enough copies\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    choice1 = 4;
    choice2 = 2;
    goodRun = ce_Ambassador(choice1, choice2, &testG, handpos);
    if (goodRun == -1)
      printf(" - Passed, returned error");
    else
      printf(" - Failed, returned 0");
    printf("\n");

    // ----------- TEST 5, send card to Supply --------------
    printf("TEST 5: Send card to Supply\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    choice1 = 1;
    choice2 = 1;
    int supCount = testG.supplyCount[testG.hand[currentPlayer][choice1]];
    printf(" - Before call supply is %d\n", supCount);
    goodRun = ce_Ambassador(choice1, choice2, &testG, handpos);
    supCount = testG.supplyCount[testG.hand[currentPlayer][choice1]];
    printf(" - After call supply is %d\n", supCount);

    
    // ----------- TEST 6, opponent receives a copy --------------
    printf("TEST 6: opponent receieves copy of card\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    choice1 = 1;
    choice2 = 1;
    // give the opponent a dummy hand
    testG.hand[currentPlayer + 1][0] = ambassador;
    testG.hand[currentPlayer + 1][1] = copper;
    testG.hand[currentPlayer + 1][2] = estate;
    testG.hand[currentPlayer + 1][3] = estate;
    testG.hand[currentPlayer + 1][4] = village;
    // confirm hand
    printf(" - Before Ambassador, opponent has handCount %d containing ", testG.handCount[currentPlayer + 1]);
    for (int i = 0; i < testG.handCount[currentPlayer + 1]; i++)
      printf("%d ", testG.hand[currentPlayer + 1][i]);
    printf("\n");
    ce_Ambassador(choice1, choice2, &testG, handpos);
    printf(" - After Ambassador, opponent has handCount %d containing ", testG.handCount[currentPlayer + 1]);
    for (int i = 0; i < testG.handCount[currentPlayer + 1]; i++)
      printf("%d ", testG.hand[currentPlayer + 1][i]);
    printf("\n");
    

    
    /*    




	
	choice1 = 1;
	cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 2;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
	assert(testG.coins == G.coins + xtraCoins);

	// ----------- TEST 2: choice1 = 2 = +2 coins --------------
	printf("TEST 2: choice1 = 2 = +2 coins\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 2;
	cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 0;
	xtraCoins = 2;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
	assert(testG.coins == G.coins + xtraCoins);

	// ----------- TEST 3: choice1 = 3 = trash two cards --------------

	printf("TEST 3: choice1 = 3 = trash two cards\n");
	choice1 = 3;

	// cycle through each eligible combination of 2 cards to trash
	for (i=1; i<G.handCount[thisPlayer]; i++) {
		for (j=i+1; j<G.handCount[thisPlayer]; j++) {

			G.hand[thisPlayer][0] = steward;
			G.hand[thisPlayer][1] = copper;
			G.hand[thisPlayer][2] = duchy;
			G.hand[thisPlayer][3] = estate;
			G.hand[thisPlayer][4] = feast;

			// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));

			printf("starting cards: ");
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%d)", testG.hand[thisPlayer][m]);
			}
			printf("; ");

			choice2 = j;
			choice3 = i;
			remove1 = testG.hand[thisPlayer][i];
			remove2 = testG.hand[thisPlayer][j];
			cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

			printf("removed: (%d)(%d); ", remove1, remove2);
			printf("ending cards: ");

			// tests that the removed cards are no longer in the player's hand
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%d)", testG.hand[thisPlayer][m]);
				assert(testG.hand[thisPlayer][m] != remove1);
				assert(testG.hand[thisPlayer][m] != remove2);
			}
			printf(", expected: ");
			for (m=1; m<G.handCount[thisPlayer]; m++) {
				if (G.hand[thisPlayer][m] != G.hand[thisPlayer][i] && G.hand[thisPlayer][m] != G.hand[thisPlayer][j]) {
					printf("(%d)", G.hand[thisPlayer][m]);
				}
			}
			printf("\n");

			// tests for the appropriate number of remaining cards
			newCards = 0;
			xtraCoins = 0;
			discarded = 3;
			if (i==1 && j==2) {
				printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
				printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
			}
			assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
			assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
		}

	}
    */
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


