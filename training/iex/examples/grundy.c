/* Who wins? Several piles, a move removes m stones from one pile, m in a given set.
 *
 * Input:  k, the k allowed move sizes, then n and the n pile sizes (<= 10^6).
 * Output: "First" if the player to move wins with perfect play, else "Second".
 * Idea:   Sprague-Grundy: g(x) = mex{ g(x - m) }, a position is lost iff g = 0,
 *         independent piles combine by XOR (like Nim). O(maxpile * k)
 */
#include "game.h"

static int g[1000001];

int main(void) {
    int k, n, moves[100], mx = 0, x = 0;
    static int pile[100000];
    if (scanf("%d", &k) != 1) return 0;
    for (int i = 0; i < k; i++) scanf("%d", &moves[i]);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) { scanf("%d", &pile[i]); mx = MAX(mx, pile[i]); }
    grundy_subtraction(mx, moves, k, g);
    for (int i = 0; i < n; i++) x ^= g[pile[i]];
    printf("%s\n", x ? "First" : "Second");
    return 0;
}
