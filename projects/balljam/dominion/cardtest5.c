/* -----------------------------------------------------------------------
 * drawCard
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
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int thisPlayer = 0;

    initializeGame(numPlayers, k, seed, &G);

    printf("---------- Testing drawCard() ----------\n");

    // test 1, draw from deck
    printf("Testing draw card from cards in deck...\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    drawCard(thisPlayer, &testG);
    if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 1 &&
	testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 1)
      printf(" - Passed, drew card from deck...\n");
    else
      printf(" - Failed, did not draw from deck...\n");

    // test 2, draw from empty deck, fill with discard
    printf("Testing discard pile to fill empty deck...\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    //move deck to discard
    for (int i = 0; i < testG.deckCount[thisPlayer]; i++)
      {
	testG.discard[thisPlayer][i] = testG.deck[thisPlayer][i];
	testG.deck[thisPlayer][i] = -1;
      }
    testG.discardCount[thisPlayer] = testG.deckCount[thisPlayer];
    testG.deckCount[thisPlayer] = 0; 
    drawCard(thisPlayer, &testG);
    if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 1 &&
	testG.discardCount[thisPlayer] == 0)
      printf(" - Passed, discard moved to deck...\n");
    else
      printf(" - Failed, improper draw...\n");

    // test 3, empty deck, empty discard
    printf("Testing draw from empty deck and empty discard pile...\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    // empty deck
    for (int i = 0; i < 5; i++)
      drawCard(thisPlayer, &testG);
    int drawStatus = drawCard(thisPlayer, &testG);
    if (drawStatus == -1)
      printf(" - Passed, could not draw from empty deck and empty discard...\n");
    else
      printf(" - Failed, improper draw...\n");
    
    /*
    printf(" - thisPlayer has:\n  --  deck-%d\n  --  discard-%d\\
n  --  hand-%d\n", testG.deckCount[thisPlayer], testG.discardCou\
nt[thisPlayer], testG.handCount[thisPlayer]);
    */
    printf("All tests completed!\n");

    return 0;
}
