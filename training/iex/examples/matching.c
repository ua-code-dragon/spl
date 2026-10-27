/* Assign workers to jobs (maximum bipartite matching) and check with max flow.
 *
 * Input:  nw nj m, then m lines "w j": worker w (1..nw) can do job j (1..nj).
 * Output: the maximum number of assigned workers, then "w j" for each assignment.
 * Idea:   Kuhn's algorithm: for every worker look for an augmenting path that
 *         frees a job. The same answer is a max flow source -> workers -> jobs -> sink
 *         with capacities 1 (computed below as a cross-check). O(V E)
 */
#include "flow.h"

int main(void) {
    int nw, nj, m;
    if (scanf("%d %d %d", &nw, &nj, &m) != 3) return 0;
    int S = nw + nj, T = S + 1;
    g_init(nw);
    flow_init(nw + nj + 2);
    for (int i = 0; i < nw; i++) flow_add(S, i, 1);
    for (int j = 0; j < nj; j++) flow_add(nw + j, T, 1);
    for (int i = 0; i < m; i++) {
        int w, j;
        scanf("%d %d", &w, &j);
        g_add(w - 1, j - 1, 0);
        flow_add(w - 1, nw + j - 1, 1);
    }
    int res = bipartite_matching(nw, nj);
    if (res != max_flow(S, T)) printf("flow disagrees!\n");
    printf("%d\n", res);
    for (int w = 0; w < nw; w++)
        if (mt_left[w] >= 0) printf("%d %d\n", w + 1, mt_left[w] + 1);
    return 0;
}
