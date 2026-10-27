/* Prime factorization of many numbers with a sieve.
 *
 * Input:  q, then q integers 2 <= x <= 10^6.
 * Output: the number of primes up to 10^6, then "x = p1^e1 * p2^e2 ..." per query.
 * Idea:   the sieve stores the smallest prime factor spf[x]; dividing by it
 *         repeatedly factorizes x in O(log x).
 */
#include "numtheory.h"

int main(void) {
    int q, p[20], e[20];
    sieve(1000000);
    printf("%d\n", nprimes);
    if (scanf("%d", &q) != 1) return 0;
    while (q--) {
        int x;
        scanf("%d", &x);
        int k = factor_spf(x, p, e);
        printf("%d =", x);
        for (int i = 0; i < k; i++) {
            printf("%s %d", i ? " *" : "", p[i]);
            if (e[i] > 1) printf("^%d", e[i]);
        }
        printf("\n");
    }
    return 0;
}
