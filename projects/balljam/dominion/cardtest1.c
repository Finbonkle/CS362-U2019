/* ---------------------------------------------------------------------- * initializeGame
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
    struct gameState G;
    int maxHandCount = 5;
    int thisPlayer = 0;

    printf("---------- Testing initializeGame() ----------\n");
    
    // Test 1 number of players - good conditions
    printf("Testing with 2 players...\n");
    initializeGame(numPlayers, k, seed, &G);
    if (G.numPlayers == 2)
      printf(" - Passed, 2 players...\n");
    else
      printf(" - Failed, function did not yield 2 players...\n");
    
    // Test 2 duplicate kingdom cards
    printf("Testing duplicate kingdom cards...\n");
    int badk[10] = {adventurer, council_room, feast, mine, mine
               , remodel, smithy, village, baron, great_hall};
    int dupTest = initializeGame(numPlayers, badk, seed, &G);
    if (dupTest == -1)
      printf(" - Passed, caught duplicate kingdom cards...\n");
    else
      printf(" - Failed, did not return -1 for duplicates...\n");

    // Test 3 and 4, wrong number of kingdom cards
    printf("Testing too many kingdom cards...\n");
    int badk2[11] = {adventurer, council_room, feast, gardens, mine
		       , remodel, smithy, village, baron, great_hall,
		     ambassador};
    int wrongNum1 = initializeGame(numPlayers, badk2, seed, &G);
    if (wrongNum1 == -1)
      printf(" - Passed, caught 11 kingdom cards...\n");
    else
      printf(" - Failed, did not catch too many kingdom cards...\n");
    printf("Testing too few kingdom cards...\n");
    int badk3[9] = {adventurer, council_room, feast, gardens, mine
		    , remodel, smithy, village, baron};
    int wrongNum2 = initializeGame(numPlayers, badk3, seed, &G);
    if (wrongNum2 == -1)
      printf(" - Passed, caught 9 kingdom cards...\n");
    else
      printf(" - Failed, did not catch too few kingdom cards...\n");

    // Test 5 check supply
    printf("Testing supply counts...\n");
    initializeGame(numPlayers, k, seed, &G);
    /*
    printf(" curse: %d\nprovince: %d\nsilver: %d\n",
	   G.supplyCount[curse], G.supplyCount[province],
	   G.supplyCount[silver]);
    */
    if (G.supplyCount[curse] == 10 && G.supplyCount[province] == 8 &&
	G.supplyCount[silver] == 40)
      printf(" - Passed, checked sample of supply...\n");
    else
      printf(" - Failed, did not meet sample requirements...\n");

    // Test 6 check decks and hands for size
    printf("Testing hand and deck sizes...\n");
    /*
    printf(" - Player deck is %d and player hand is %d\n",
	   G.deckCount[thisPlayer], G.handCount[thisPlayer]);
    printf(" - Opponent deck is %d and opponent hand is %d\n",
	   G.deckCount[thisPlayer + 1], G.handCount[thisPlayer + 1]);
    */
    if (G.deckCount[thisPlayer] + G.handCount[thisPlayer] == 10 &&
	G.deckCount[thisPlayer + 1] + G.handCount[thisPlayer + 1]
	== 10)
      printf(" - Passed, deck and hand sizes ok...\n");
    else
      printf(" - Failed, deck and hand sizes incorrect...\n");
    
    printf("All tests completed!\n");

    return 0;
}
