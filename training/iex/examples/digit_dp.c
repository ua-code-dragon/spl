/* Digit DP: how many numbers in [A, B] have a digit sum divisible by K?
 *
 * Input:  A B K with 0 <= A <= B <= 10^18 and 1 <= K <= 100.
 * Output: the count.
 * Idea:   count(X) = numbers in [0, X] with the property; answer = count(B) - count(A-1).
 *         Walk the digits of X from the left. State: (position, digit sum mod K,
 *         "tight" = the prefix equals X's prefix so far). When not tight the
 *         remaining digits are free and the result can be memoised.
 *         States: 19 positions * K sums; 10 transitions each.
 */
#include "common.h"

static int dig[20], nd, K;
static ll memo[20][100];
static char seen[20][100];

/* numbers formed by positions pos.. (digits dig[pos..nd-1] are the limit when tight) */
static ll go(int pos, int sum, int tight) {
    if (pos == nd) return sum == 0;
    if (!tight && seen[pos][sum]) return memo[pos][sum];
    int limit = tight ? dig[pos] : 9;
    ll res = 0;
    for (int d = 0; d <= limit; d++) res += go(pos + 1, (sum + d) % K, tight && d == limit);
    if (!tight) { seen[pos][sum] = 1; memo[pos][sum] = res; }
    return res;
}

static ll count_upto(ll x) {                    /* how many v in [0, x] */
    if (x < 0) return 0;
    nd = 0;
    char s[24];
    sprintf(s, "%lld", x);
    for (int i = 0; s[i]; i++) dig[nd++] = s[i] - '0';
    memset(seen, 0, sizeof seen);               /* memo depends on the number of digits */
    return go(0, 0, 1);
}

int main(void) {
    ll a, b;
    if (scanf("%lld %lld %d", &a, &b, &K) != 3) return 0;
    printf("%lld\n", count_upto(b) - count_upto(a - 1));
    return 0;
}
