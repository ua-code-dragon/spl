/* Exact factorial (big integers).
 *
 * Input:  n (0 <= n <= 3000).
 * Output: n! in decimal.
 * Idea:   n! has thousands of digits; keep it in base 10^9 limbs and multiply
 *         by 1, 2, ..., n with the schoolbook carry. O(n * digits)
 */
#include "bignum.h"

int main(void) {
    static Big f;
    int n;
    if (scanf("%d", &n) != 1) return 0;
    bn_from_ll(&f, 1);
    for (int i = 2; i <= n; i++) bn_mul_small(&f, &f, i);
    bn_print(&f);
    printf("\n");
    return 0;
}
