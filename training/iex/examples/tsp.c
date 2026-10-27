/* Shortest round trip through all cities (travelling salesman, bitmask DP).
 *
 * Input:  n (<= 16), then the n x n matrix of travel costs.
 * Output: the cost of the cheapest cycle that starts in city 0, visits every
 *         city exactly once and returns to city 0.
 * Idea:   dp[mask][v] = cheapest path from 0 that visited exactly the cities in
 *         mask and stands in v. 2^n * n states, n transitions each.
 */
#include "dp.h"

static ll d[TSP_N][TSP_N];

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) scanf("%lld", &d[i][j]);
    printf("%lld\n", tsp(n, d));
    return 0;
}
