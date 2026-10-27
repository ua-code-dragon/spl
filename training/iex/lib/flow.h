/* flow.h - maximum flow, bipartite matching, minimum cost flow.
 *
 *   flow_init flow_add max_flow                (Dinic)
 *   bipartite_matching                         (Kuhn, uses graph.h adjacency)
 *   mcmf_init mcmf_add mcmf                    (min-cost max-flow, SPFA)
 *
 * Modelling tricks (vertex capacities, min cut, assignment): docs/en/handbook.md.
 * These networks have their own arrays and do not touch graph.h's graph.
 */
#ifndef XT_FLOW_H
#define XT_FLOW_H
#include "common.h"
#include "graph.h"

#ifndef FL_V
#define FL_V 5005
#endif
#ifndef FL_E
#define FL_E 200005 /* two slots per flow_add */
#endif

static int fl_head[FL_V], fl_nxt[FL_E], fl_to[FL_E], fl_level[FL_V], fl_it[FL_V], fl_q[FL_V];
static ll fl_cap[FL_E]; /* residual capacity */
static int fl_n, fl_m;

static inline void flow_init(int n) {
    fl_n = n; fl_m = 0;
    for (int i = 0; i < n; i++) fl_head[i] = -1;
}

/* edge u -> v with capacity cap; returns its id e. Flow through it = cap - fl_cap[e]. */
static inline int flow_add(int u, int v, ll cap) {
    fl_to[fl_m] = v; fl_cap[fl_m] = cap; fl_nxt[fl_m] = fl_head[u]; fl_head[u] = fl_m++;
    fl_to[fl_m] = u; fl_cap[fl_m] = 0;   fl_nxt[fl_m] = fl_head[v]; fl_head[v] = fl_m++;
    return fl_m - 2;
}

static inline int fl_bfs_(int s, int t) { /* level graph */
    int h = 0, q = 0;
    for (int i = 0; i < fl_n; i++) fl_level[i] = -1;
    fl_level[s] = 0; fl_q[q++] = s;
    while (h < q) {
        int u = fl_q[h++];
        for (int e = fl_head[u]; e != -1; e = fl_nxt[e])
            if (fl_cap[e] > 0 && fl_level[fl_to[e]] < 0) {
                fl_level[fl_to[e]] = fl_level[u] + 1;
                fl_q[q++] = fl_to[e];
            }
    }
    return fl_level[t] >= 0;
}

static inline ll fl_dfs_(int u, int t, ll f) { /* one augmenting path in the level graph */
    if (u == t) return f;
    for (; fl_it[u] != -1; fl_it[u] = fl_nxt[fl_it[u]]) {
        int e = fl_it[u], v = fl_to[e];
        if (fl_cap[e] > 0 && fl_level[v] == fl_level[u] + 1) {
            ll d = fl_dfs_(v, t, MIN(f, fl_cap[e]));
            if (d > 0) { fl_cap[e] -= d; fl_cap[e ^ 1] += d; return d; }
        }
    }
    return 0;
}

/* Dinic: O(V^2 E) in general, O(E sqrt V) on unit-capacity bipartite graphs */
static inline ll max_flow(int s, int t) {
    ll flow = 0;
    while (fl_bfs_(s, t)) {
        for (int i = 0; i < fl_n; i++) fl_it[i] = fl_head[i];
        ll f;
        while ((f = fl_dfs_(s, t, LINF)) > 0) flow += f;
    }
    return flow;
}

/* ---------- maximum bipartite matching (Kuhn) ----------
 * Left vertices 0..nl-1 are graph.h vertices; edge u -> v means left u may
 * be matched with right v (0..nr-1). mt_left[u] / mt_right[v] = partner or -1. O(V E) */
static int mt_left[GV_MAX], mt_right[GV_MAX], mt_seen[GV_MAX], mt_stamp;

static inline int kuhn_try_(int u) {
    G_EACH(e, u) {
        int v = g_to[e];
        if (mt_seen[v] == mt_stamp) continue;
        mt_seen[v] = mt_stamp;
        if (mt_right[v] == -1 || kuhn_try_(mt_right[v])) {
            mt_right[v] = u; mt_left[u] = v;
            return 1;
        }
    }
    return 0;
}

static inline int bipartite_matching(int nl, int nr) {
    int res = 0;
    for (int i = 0; i < nl; i++) mt_left[i] = -1;
    for (int i = 0; i < nr; i++) { mt_right[i] = -1; mt_seen[i] = 0; }
    mt_stamp = 0;
    for (int u = 0; u < nl; u++) {
        mt_stamp++;
        res += kuhn_try_(u);
    }
    return res;
}

/* ---------- minimum cost maximum flow ---------- */
#ifndef MC_V
#define MC_V 1005
#endif
#ifndef MC_E
#define MC_E 100005
#endif
static int mc_head[MC_V], mc_nxt[MC_E], mc_to[MC_E];
static ll mc_cap[MC_E], mc_cost[MC_E];
static int mc_n, mc_m;

static inline void mcmf_init(int n) {
    mc_n = n; mc_m = 0;
    for (int i = 0; i < n; i++) mc_head[i] = -1;
}

static inline int mcmf_add(int u, int v, ll cap, ll cost) {
    mc_to[mc_m] = v; mc_cap[mc_m] = cap; mc_cost[mc_m] = cost;  mc_nxt[mc_m] = mc_head[u]; mc_head[u] = mc_m++;
    mc_to[mc_m] = u; mc_cap[mc_m] = 0;   mc_cost[mc_m] = -cost; mc_nxt[mc_m] = mc_head[v]; mc_head[v] = mc_m++;
    return mc_m - 2;
}

/* send up to maxf units from s to t along cheapest paths; returns the flow
 * sent and stores its total cost in *cost. Costs may be negative but the
 * network must not contain a negative cycle. */
static inline ll mcmf(int s, int t, ll maxf, ll *cost) {
    static ll d[MC_V];
    static int pe[MC_V], q[MC_V];
    static char inq[MC_V];
    ll flow = 0;
    *cost = 0;
    while (flow < maxf) {
        for (int i = 0; i < mc_n; i++) { d[i] = LINF; inq[i] = 0; }
        int h = 0, cnt = 0; /* circular queue (SPFA) */
        d[s] = 0; q[0] = s; cnt = 1; inq[s] = 1;
        while (cnt) {
            int u = q[h]; h = (h + 1) % MC_V; cnt--; inq[u] = 0;
            for (int e = mc_head[u]; e != -1; e = mc_nxt[e]) {
                int v = mc_to[e];
                if (mc_cap[e] > 0 && d[u] + mc_cost[e] < d[v]) {
                    d[v] = d[u] + mc_cost[e]; pe[v] = e;
                    if (!inq[v]) { q[(h + cnt) % MC_V] = v; cnt++; inq[v] = 1; }
                }
            }
        }
        if (d[t] == LINF) break;
        ll f = maxf - flow;
        for (int v = t; v != s; v = mc_to[pe[v] ^ 1]) f = MIN(f, mc_cap[pe[v]]);
        for (int v = t; v != s; v = mc_to[pe[v] ^ 1]) { mc_cap[pe[v]] -= f; mc_cap[pe[v] ^ 1] += f; }
        flow += f;
        *cost += f * d[t];
    }
    return flow;
}

#endif
