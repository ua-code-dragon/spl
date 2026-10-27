/* Binary search on the answer: split an array into at most k contiguous
 * parts so that the largest part sum is as small as possible.
 *
 * Input:  n k, then n non-negative integers.
 * Output: the minimal possible largest part sum.
 * Idea:   ok(x) = "parts with sum <= x need at most k pieces" is false for
 *         small x and true for large x, so binary search the first true x.
 *         Each check is a greedy O(n) pass: O(n log(sum)).
 */
#include "search.h"

static ll a[200005];
static int n, k;

static int ok(ll limit) {
    int parts = 1;
    ll cur = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > limit) return 0;
        if (cur + a[i] > limit) { parts++; cur = 0; }   /* start a new part */
        cur += a[i];
    }
    return parts <= k;
}

int main(void) {
    ll total = 0;
    if (scanf("%d %d", &n, &k) != 2) return 0;
    for (int i = 0; i < n; i++) { scanf("%lld", &a[i]); total += a[i]; }
    printf("%lld\n", bs_first_true(0, total, ok));
    return 0;
}
