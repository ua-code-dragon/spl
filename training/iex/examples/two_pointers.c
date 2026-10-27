/* Two pointers: the longest block of consecutive days with total cost <= budget.
 *
 * Input:  n budget, then n non-negative costs.
 * Output: the maximum length of a contiguous block whose sum is <= budget.
 * Idea:   for every right end r move the left end l forward while the sum is
 *         too big. Both pointers only move forward, so the loop is O(n), not O(n^2).
 *         (Works because costs are non-negative: extending never lowers the sum.)
 */
#include "common.h"

static ll a[200005];

int main(void) {
    int n, best = 0;
    ll budget, sum = 0;
    if (scanf("%d %lld", &n, &budget) != 2) return 0;
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    for (int l = 0, r = 0; r < n; r++) {
        sum += a[r];                            /* window is a[l..r] */
        while (sum > budget) sum -= a[l++];
        best = MAX(best, r - l + 1);
    }
    printf("%d\n", best);
    return 0;
}
