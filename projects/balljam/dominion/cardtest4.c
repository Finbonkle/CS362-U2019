/* -----------------------------------------------------------------------
 * getWinners
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
    int players[2];
    initializeGame(numPlayers, k, seed, &G);

    printf("---------- Testing getWinners() ----------\n");

    // TEST 1, tie
    printf("Testing a tie...\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    getWinners(players, &testG);
    if (players[0] == 1 && players[1] == 1)
      printf(" - Passed, tied for victory...\n");
    else
      printf(" - Failed, players did not tie for victory with identical cards...\n");

    // TEST 2, player 1 wins
    printf("Testing P1 wins...\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    gainCard(2, &testG, 2, thisPlayer);
    getWinners(players, &testG);
    if (players[0] == 1 && players[1] == 0)
      printf(" - Passed, Player 1 wins...\n");
    else
      printf(" - Failed, Player 1 did not win...\n");

    // TEST 3, player 2 wins
    printf("Testing P2 wins...\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    gainCard(2, &testG, 2, thisPlayer + 1);
    getWinners(players, &testG);
    if (players[0] == 2 && players[1] == 1)
      printf(" - Passed, Player 2 wins...\n");
    else
      printf(" - Failed, Player 2 did not win...\n");

    /*
    printf(" - After initialization:\n");
    for (int i = 0; i < 2; i++)
      {
	printf(" - Player %d has:\n deck-%d\n discard-%d\n hand-%d\n", i,
	       testG.deckCount[i], testG.discardCount[i], testG.handCount[i]);
      }
 	endTurn(&testG);
    printf(" - After 1 endTurn,:\n");
    for (int i = 0; i < 2; i++)
      {
	printf(" - Player %d has:\n deck-%d\n discard-%d\n hand-%d\n", i,
	       testG.deckCount[i], testG.discardCount[i], testG.handCount[i]);
      }

    /*
    for (int i = 0; i < MAX_PLAYERS; i++)
      printf(" Player %d has a score of %d\n", i, scoreFor(i, &testG));
    endTurn(&testG);
    printf(" - After 1 endTurn:\n");
    for (int i = 0; i < MAX_PLAYERS; i++)
      printf(" Player %d has a score of %d\n", i, scoreFor(i, &testG));
    endTurn(&testG);
    printf(" - After 2 endTurns:\n");
    for (int i = 0; i < MAX_PLAYERS; i++)
      printf(" Player %d has a score of %d\n", i, scoreFor(i, &testG));
    printf(" - After getWinners:\n");
    getWinners(players, &testG);
    for (int i = 0; i < MAX_PLAYERS; i++)
      printf(" Player %d has a value of %d\n", i, players[i]);


    */    
    printf("All tests completed!\n");

    return 0;
}
