/* N-th Fibonacci number for huge N (matrix exponentiation).
 *
 * Input:  q, then q values 0 <= n <= 10^18.
 * Output: F(n) mod 1e9+7 (F(0) = 0, F(1) = 1).
 * Idea:   (F(n+1), F(n)) = M^n (F(1), F(0)) with M = [[1,1],[1,0]];
 *         M^n by repeated squaring in O(log n) matrix products.
 *         Works for any linear recurrence: put its coefficients in the first row.
 */
#include "matrix.h"

int main(void) {
    int q;
    if (scanf("%d", &q) != 1) return 0;
    while (q--) {
        ll n;
        scanf("%lld", &n);
        Mat m = mat_ident(2);
        m.a[0][0] = 1; m.a[0][1] = 1;
        m.a[1][0] = 1; m.a[1][1] = 0;
        Mat r = mat_pow(m, n, MOD);
        printf("%lld\n", r.a[0][1]);                 /* M^n = [[F(n+1), F(n)], [F(n), F(n-1)]] */
    }
    return 0;
}
