/* Cheapest route between two cities (Dijkstra) with path reconstruction.
 *
 * Input:  n m, then m lines "u v w": a two-way road of length w (cities 1..n).
 * Output: shortest distance from 1 to n and the cities on one shortest path,
 *         or -1 if n cannot be reached.
 * Idea:   Dijkstra with a binary heap, prev[] remembers where we came from. O(m log m)
 */
#include "paths.h"

static ll dist[GV_MAX];
static int prev[GV_MAX], path[GV_MAX];

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    g_init(n + 1);                          /* vertices 1..n */
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        g_add2(u, v, w);
    }
    dijkstra(1, dist, prev);
    if (dist[n] == LINF) { printf("-1\n"); return 0; }
    int k = build_path(prev, n, path);
    printf("%lld\n", dist[n]);
    for (int i = 0; i < k; i++) printf("%d%c", path[i], i + 1 < k ? ' ' : '\n');
    return 0;
}
