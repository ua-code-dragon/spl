/* Distances in a weighted tree (lowest common ancestor, binary lifting).
 *
 * Input:  n, then n-1 lines "u v w" (tree edges, vertices 1..n), q, then q lines "a b".
 * Output: for each query: the distance between a and b and their LCA (tree rooted at 1).
 * Idea:   dist(a, b) = depth(a) + depth(b) - 2 depth(lca(a, b)), where depth
 *         is the weighted distance from the root. O(n log n) + O(log n) per query.
 */
#include "tree.h"

int main(void) {
    int n, q;
    if (scanf("%d", &n) != 1) return 0;
    g_init(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        g_add2(u, v, w);
    }
    lca_init(1);
    scanf("%d", &q);
    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%lld %d\n", tree_dist(a, b), lca(a, b));
    }
    return 0;
}
