/* Range updates and range queries (lazy segment tree).
 *
 * Input:  n q, the array a[1..n], then q operations:
 *           1 l r x   add x to a[l..r]
 *           2 l r x   set a[l..r] = x
 *           3 l r     print a[l] + ... + a[r]
 *           4 l r     print max(a[l..r])
 * Output: one line per query of type 3 or 4.
 * Idea:   a node stores the sum and max of its range plus a pending
 *         operation that is pushed to the children only when needed. O(log n) each.
 */
#include "segtree.h"

static ll a[LSEG_MAX];

int main(void) {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    lz_init(n, a);
    while (q--) {
        int t, l, r;
        ll x;
        scanf("%d %d %d", &t, &l, &r);
        l--; r--;                                   /* the tree uses 0-based positions */
        if (t == 1) { scanf("%lld", &x); lz_add(l, r, x); }
        else if (t == 2) { scanf("%lld", &x); lz_assign(l, r, x); }
        else if (t == 3) printf("%lld\n", lz_sum(l, r));
        else printf("%lld\n", lz_max(l, r));
    }
    return 0;
}
