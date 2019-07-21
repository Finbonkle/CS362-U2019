/* -----------------------------------------------------------------------
 * shuffle
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayers = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int handPos = 0;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int thisPlayer = 0;

    initializeGame(numPlayers, k, seed, &G);

    printf("---------- Testing shuffle() ----------\n");
    
    // Test 1, deck of size 0
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing deck shuffle with empty deck...\n");
    /*
    printf(" - thisPlayer has a deck of size %d\n",
	   testG.deckCount[thisPlayer]);
    */
    int dc = testG.deckCount[thisPlayer];
    for ( int i = 0; i < dc; i++)
      drawCard(thisPlayer, &testG);
    /*
    printf(" - after drawing, thisPlayer has a deck of size %d\n",
	   testG.deckCount[thisPlayer]);
    */
    int zeroCheck = shuffle(thisPlayer, &testG);
    if (zeroCheck != 0)
      printf(" - Passed, did not try to shuffle an empty deck...\n");
    else
      printf(" - Failed, shuffled an empty deck...\n");

    // Test 2, deck of size 1
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing deck shuffle with single card deck...\n");
    /*
    printf(" - thisPlayer has:\n  --  deck-%d\n  --  discard-%d\n  --  hand-%d\n", testG.deckCount[thisPlayer], testG.discardCount[thisPlayer], testG.handCount[thisPlayer]);
    */
    dc = testG.deckCount[thisPlayer];
    for ( int i = 0; i < dc - 1; i++)
      drawCard(thisPlayer, &testG);
    /*
    printf(" - thisPlayer has:\n  --  deck-%d\n  --  discard-%d\n  --  hand-%d\n", testG.deckCount[thisPlayer], testG.discardCount[thisPlayer], testG.handCount[thisPlayer]);
    */
    int oneCheck = shuffle(thisPlayer, &testG);
    if (oneCheck == 0)
      printf(" - Passed, shuffled single card...\n");
    else
      printf(" - Failed, could not shuffle single card...\n");
    
    // Test 3, shuffle a deck of size 10
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing deck shuffle with 10 card deck...\n");
    // TESTING
    printf(" AFTER INITIALIZATION:\n");
    printf(" - thisPlayer has:\n  --  deck-%d\n  --  discard-%d\n  --  hand-%d\n", testG.deckCount[thisPlayer], testG.discardCount[thisPlayer], testG.handCount[thisPlayer]);
    dc = testG.deckCount[thisPlayer];
    // draw deck into hand
    for (int i = 0; i < dc; i++)
      drawCard(thisPlayer, &testG);
    // TESTING
    printf(" AFTER DRAWING DECK INTO HAND:\n");
    printf(" - thisPlayer has:\n  --  deck-%d\n  --  discard-%d\n  --  hand-%d\n", testG.deckCount[thisPlayer], testG.discardCount[thisPlayer], testG.handCount[thisPlayer]);
    // for test purposes, alter hand
    for (int i = 0; i < 10; i++)
      testG.hand[thisPlayer][i] = i;
    printf(" AFTER ALTERING HAND:\n");
    printf(" - thisPlayer has:\n  --  deck-%d\n  --  discard-%d\n  --  hand-%d\n", testG.deckCount[thisPlayer], testG.discardCount[thisPlayer], testG.handCount[thisPlayer]);
    printf(" - Starting hand is: \n");
    for (int i = 0; i < 10; i++)
      printf(" %d", testG.hand[thisPlayer][i]);
    printf("\n");
    // discard hand
    for (int j = 0; j < testG.handCount[thisPlayer]; j++)
      {
	testG.discard[thisPlayer][testG.discardCount[thisPlayer]++] =
	  testG.hand[thisPlayer][j];
	testG.hand[thisPlayer][j] = -1;
      }
    testG.handCount[thisPlayer] = 0;
    printf(" AFTER DISCARDING HAND:\n");
    printf(" - thisPlayer has:\n  --  deck-%d\n  --  discard-%d\n  --  hand-%d\n", testG.deckCount[thisPlayer], testG.discardCount[thisPlayer], testG.handCount[thisPlayer]);
    // move discard pile back to the deck
    int discardC = testG.discardCount[thisPlayer];
    for (int i = 0; i < discardC; i++)
      {
	testG.deck[thisPlayer][i] = testG.discard[thisPlayer][i];
	testG.discard[thisPlayer][i] = -1;
	testG.discardCount[thisPlayer]--;
	testG.deckCount[thisPlayer]++;
      }
    printf(" AFTER MOVING DISCARD TO DECK:\n");
    printf(" - thisPlayer has:\n  --  deck-%d\n  --  discard-%d\n  --  hand-%d\n", testG.deckCount[thisPlayer], testG.discardCount[thisPlayer], testG.handCount[thisPlayer]);

    printf(" - Now deck is: \n");
    for (int i = 0; i < 10; i++)
      printf(" %d", testG.deck[thisPlayer][i]);
    printf("\n");
    int tenCheck = shuffle(thisPlayer, &testG);
    printf(" - shuffled deck is: \n");
    for (int i = 0; i < 10; i++)
      printf(" %d", testG.deck[thisPlayer][i]);
    printf("\n");
    /*    
    if (oneCheck == 0)
      printf(" - Passed, shuffled single card...\n");
    else
      printf(" - Failed, could not shuffle single card...\n");
    
    printf("All tests completed!\n");
    */
    /*
    // Test 3, shuffle a deck of size 10
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing deck shuffle with 10 card deck...\n");
    dc = testG.deckCount[thisPlayer];
    // draw deck into hand
    for (int i = 0; i < dc; i++)
      drawCard(thisPlayer, &testG);
    // for test purposes, alter hand
    for (int i = 0; i < 10; i++)
      testG.hand[thisPlayer][i] = i;
    // discard hand
    while (testG.handCount[thisPlayer] > 0)
      {
	discardCard(handPos, thisPlayer, &testG, 0);
      }
    // move discard pile back to the deck
    int discardC = testG.discardCount[thisPlayer];
    for (int i = 0; i < discardC; i++)
      {
	testG.deck[thisPlayer][i] = testG.discard[thisPlayer][i];
	testG.discard[thisPlayer][i] = -1;
      }
    int tenCheck = shuffle(thisPlayer, &testG);
    printf(" - shuffled deck is: \n");
    for (int i = 0; i < 10; i++)
      printf(" %d", testG.deck[thisPlayer][i]);
    printf("\n");
    */
    printf("All tests completed!\n");
    
    return 0;
}
