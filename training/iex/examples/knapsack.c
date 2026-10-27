/* 0/1 knapsack written out in full, with reconstruction of the chosen items.
 *
 * Input:  n W, then n lines "weight value".
 * Output: the best total value with total weight <= W, then the chosen items (1-based).
 *
 * DP recipe:
 *   state       f[i][c] = best value using the first i items with capacity c
 *   transition  f[i][c] = max(f[i-1][c], f[i-1][c-w_i] + v_i)  (skip / take item i)
 *   base        f[0][c] = 0
 *   answer      f[n][W]; walk back from (n, W) to see which items were taken
 * Time and memory O(n W). (dp.h has the O(W)-memory version without reconstruction.)
 */
#include "common.h"

#define N 105
#define WMAX 10005
static ll f[N][WMAX];
static int w[N];
static ll v[N];

int main(void) {
    int n, W;
    if (scanf("%d %d", &n, &W) != 2) return 0;
    for (int i = 1; i <= n; i++) scanf("%d %lld", &w[i], &v[i]);
    for (int i = 1; i <= n; i++)
        for (int c = 0; c <= W; c++) {
            f[i][c] = f[i - 1][c];
            if (c >= w[i] && f[i - 1][c - w[i]] + v[i] > f[i][c]) f[i][c] = f[i - 1][c - w[i]] + v[i];
        }
    printf("%lld\n", f[n][W]);
    int chosen[N], k = 0;
    for (int i = n, c = W; i >= 1; i--)
        if (f[i][c] != f[i - 1][c]) { chosen[k++] = i; c -= w[i]; }   /* item i was taken */
    for (int i = k - 1; i >= 0; i--) printf("%d%c", chosen[i], i ? ' ' : '\n');
    return 0;
}
