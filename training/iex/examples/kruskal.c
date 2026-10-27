/* Cheapest network connecting all cities (minimum spanning tree, Kruskal).
 *
 * Input:  n m, then m lines "u v w" (cities 1..n, cable cost w).
 * Output: total cost of the cheapest network, or IMPOSSIBLE if the graph is disconnected.
 * Idea:   take edges from cheapest to most expensive and keep an edge when it
 *         joins two different components (DSU). O(m log m)
 */
#include "graph.h"

static Edge e[GE_MAX];

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %lld", &e[i].u, &e[i].v, &e[i].w);
        e[i].u--; e[i].v--;                         /* kruskal uses vertices 0..n-1 */
    }
    ll cost = kruskal(n, e, m);
    if (dsu_sets != 1) printf("IMPOSSIBLE\n");
    else printf("%lld\n", cost);
    return 0;
}
