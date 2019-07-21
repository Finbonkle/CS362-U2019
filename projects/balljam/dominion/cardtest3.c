/* -----------------------------------------------------------------------
 * endturn
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
    
    printf("---------- Testing endTurn() ----------\n");

    // Test 1, discard hand
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing discard hand...\n");
    /*
    printf(" - Initial thisPlayer hand count: %d\n", testG.handCount[thisPlayer]);
    printf(" - Initial thisPlayer -1 hand count: %d\n", testG.handCount[thisPlayer - 1]);
    printf(" - Initial thisPlayer +1 hand count: %d\n", testG.handCount[thisPlayer + 1]);
    */
    printf(" - call endTurn()...\n");
    endTurn(&testG);
    /*
    printf(" - after call, thisPlayer hand count: %d\n", testG.handCount[thisPlayer]);
    printf(" - after call, thisPlayer -1 hand count: %d\n", testG.handCount[thisPlayer - 1]);
    printf(" - after call, thisPlayer +1 hand count: %d\n", testG.handCount[thisPlayer + 1]);
    */
    if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 5)
      printf(" - Passed, discarded hand...\n");
    else
      printf(" - Faile, hand not discarded...\n");

    // Test 2
    printf("Testing new player draws cards...\n");
    if (testG.handCount[thisPlayer + 1] == G.handCount[thisPlayer + 1] + 5)
      printf(" - Passed, new player drew cards...\n");
    else
      printf(" - Failed, new player did not draw cards...\n");

    // Test 3 
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Testing new turn conditions...\n");
    // alter conditions
    testG.numActions++;
    testG.coins = 5;
    testG.numBuys--;
    /*
    // TESTING
    printf(" - before call,\n");
    printf("  --  acitons:%d\n  --  coins:%d\n  --  numBuys:%d\n", testG.numActions, testG.coins, testG.numBuys);
    */

    printf(" - call endTurn()...\n");
    endTurn(&testG);
    /*
    // TESTING
    printf(" - after call,\n");
    printf("  --  acitons:%d\n  --  coins:%d\n  --  numBuys:%d\n", testG.numActions, testG.coins, testG.numBuys);
    */
    if (testG.numActions != 2 && testG.coins != 5 && testG.numBuys != 0)
      printf(" - Passed, conditions reset on new turn...\n");
    else
      printf(" - Failed, conditions not reset...\n");
    
    printf("All tests completed!\n");

    return 0;
}
