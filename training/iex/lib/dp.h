/* dp.h - classic dynamic programming problems.
 *
 *   max_subarray lis_length lcs_length edit_distance
 *   knapsack01 coin_min coin_ways tsp
 *
 * They are also templates: copy one and change the recurrence.
 * DP recipe: 1) state, 2) transition, 3) base case, 4) order of evaluation,
 * 5) where the answer is. See docs/en/handbook.md, section "Dynamic programming".
 */
#ifndef XT_DP_H
#define XT_DP_H
#include "common.h"

#ifndef DP_MAX
#define DP_MAX 1000005
#endif

/* maximum sum of a non-empty contiguous subarray (Kadane). O(n) */
static inline ll max_subarray(const ll *a, int n) {
    ll best = a[0], cur = a[0];
    for (int i = 1; i < n; i++) {
        cur = MAX(a[i], cur + a[i]); /* extend or start again at i */
        best = MAX(best, cur);
    }
    return best;
}

/* longest increasing subsequence; strict = 0 allows equal neighbours. O(n log n)
 * t[k] = smallest possible last element of an increasing subsequence of length k+1 */
static inline int lis_length(const int *a, int n, int strict) {
    static int t[DP_MAX];
    int len = 0;
    for (int i = 0; i < n; i++) {
        int lo = 0, hi = len; /* first t[pos] >= a[i] (or > if !strict) */
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (t[mid] < a[i] || (!strict && t[mid] == a[i])) lo = mid + 1; else hi = mid;
        }
        t[lo] = a[i];
        if (lo == len) len++;
    }
    return len;
}

/* longest common subsequence of strings a and b. O(|a| |b|) time, O(|b|) memory */
static inline int lcs_length(const char *a, const char *b) {
    static int prev[DP_MAX], cur[DP_MAX];
    int n = (int)strlen(a), m = (int)strlen(b);
    memset(prev, 0, sizeof(int) * (size_t)(m + 1));
    for (int i = 1; i <= n; i++) {
        cur[0] = 0;
        for (int j = 1; j <= m; j++)
            cur[j] = (a[i - 1] == b[j - 1]) ? prev[j - 1] + 1 : MAX(prev[j], cur[j - 1]);
        memcpy(prev, cur, sizeof(int) * (size_t)(m + 1));
    }
    return prev[m];
}

/* Levenshtein distance: fewest insertions, deletions, replacements a -> b */
static inline int edit_distance(const char *a, const char *b) {
    static int prev[DP_MAX], cur[DP_MAX];
    int n = (int)strlen(a), m = (int)strlen(b);
    for (int j = 0; j <= m; j++) prev[j] = j;
    for (int i = 1; i <= n; i++) {
        cur[0] = i;
        for (int j = 1; j <= m; j++) {
            int best = prev[j - 1] + (a[i - 1] != b[j - 1]); /* keep or replace */
            best = MIN(best, prev[j] + 1); /* delete a[i-1]   */
            best = MIN(best, cur[j - 1] + 1); /* insert b[j-1]   */
            cur[j] = best;
        }
        memcpy(prev, cur, sizeof(int) * (size_t)(m + 1));
    }
    return prev[m];
}

/* 0/1 knapsack: each item once, total weight <= cap, maximize value. O(n cap) */
static inline ll knapsack01(const int *w, const ll *v, int n, int cap) {
    static ll f[DP_MAX]; /* f[c] = best value with weight <= c */
    memset(f, 0, sizeof(ll) * (size_t)(cap + 1));
    for (int i = 0; i < n; i++)
        for (int c = cap; c >= w[i]; c--) /* downwards: item used at most once */
            f[c] = MAX(f[c], f[c - w[i]] + v[i]);
    return f[cap]; /* unbounded (reuse items): loop c upwards from w[i] */
}

/* fewest coins summing exactly to target, -1 if impossible */
static inline int coin_min(const int *coin, int k, int target) {
    static int f[DP_MAX];
    f[0] = 0;
    for (int s = 1; s <= target; s++) {
        f[s] = INF;
        for (int i = 0; i < k; i++)
            if (coin[i] <= s && f[s - coin[i]] + 1 < f[s]) f[s] = f[s - coin[i]] + 1;
    }
    return f[target] >= INF ? -1 : f[target];
}

/* number of multisets of coins summing to target, modulo mod */
static inline ll coin_ways(const int *coin, int k, int target, ll mod) {
    static ll f[DP_MAX];
    memset(f, 0, sizeof(ll) * (size_t)(target + 1));
    f[0] = 1;
    for (int i = 0; i < k; i++) /* coins outer: order does not matter */
        for (int s = coin[i]; s <= target; s++) f[s] = (f[s] + f[s - coin[i]]) % mod;
    return f[target];
}

/* ---------- bitmask DP: travelling salesman ---------- */
#ifndef TSP_N
#define TSP_N 16
#endif

/* shortest cycle 0 -> all vertices -> 0 (d[i][j] = cost i -> j, LINF if none).
 * dp[mask][v] = cheapest path from 0 visiting exactly mask, ending in v. O(2^n n^2) */
static inline ll tsp(int n, ll d[][TSP_N]) {
    static ll dp[1 << TSP_N][TSP_N];
    int full = (1 << n) - 1;
    for (int m = 0; m <= full; m++)
        for (int v = 0; v < n; v++) dp[m][v] = LINF;
    dp[1][0] = 0;
    for (int m = 1; m <= full; m++)
        for (int v = 0; v < n; v++) {
            if (dp[m][v] == LINF || !(m >> v & 1)) continue;
            for (int u = 0; u < n; u++) {
                if ((m >> u & 1) || d[v][u] == LINF) continue;
                ll c = dp[m][v] + d[v][u];
                if (c < dp[m | 1 << u][u]) dp[m | 1 << u][u] = c;
            }
        }
    ll best = LINF;
    for (int v = 0; v < n; v++)
        if (dp[full][v] != LINF && (n == 1 || d[v][0] != LINF))
            best = MIN(best, dp[full][v] + (n == 1 ? 0 : d[v][0]));
    return best;
}

#endif
