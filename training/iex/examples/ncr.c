/* Binomial coefficients modulo a prime, many queries.
 *
 * Input:  q, then q lines "n r" with 0 <= r, n <= 10^6.
 * Output: C(n, r) mod 1e9+7 for each query (0 if r > n).
 * Idea:   C(n, r) = n! / (r! (n-r)!). Division mod a prime p is multiplication
 *         by the inverse, and 1/x = x^(p-2) (Fermat). Precompute factorials and
 *         inverse factorials once: O(N) + O(1) per query.
 */
#include "combin.h"

int main(void) {
    int q;
    comb_init(1000000);
    if (scanf("%d", &q) != 1) return 0;
    while (q--) {
        int n, r;
        scanf("%d %d", &n, &r);
        printf("%lld\n", nCr(n, r));
    }
    return 0;
}
