/* test_lib.c - checks every header of lib/ against brute force on random data.
 * Build and run:  cc -std=c11 -O2 -Wall -Wextra -pedantic -I../lib test_lib.c -lm && ./a.out
 */
#include "common.h"
#include "io.h"
#include "numtheory.h"
#include "combin.h"
#include "matrix.h"
#include "fft.h"
#include "sort.h"
#include "search.h"
#include "bits.h"
#include "linear.h"
#include "heap.h"
#include "dsu.h"
#include "fenwick.h"
#include "segtree.h"
#include "sparse.h"
#include "hashmap.h"
#include "trie.h"
#include "graph.h"
#include "paths.h"
#include "flow.h"
#include "tree.h"
#include "strutil.h"
#include "geom.h"
#include "dp.h"
#include "game.h"
#include "bignum.h"
#include "grid.h"
#include "util.h"
#include "interactive.h"

static int fails, checks;
#define CHECK(cond) do { checks++; if (!(cond)) { fails++; printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); } } while (0)

static int rnd(int lo, int hi) { return (int)rng_range(lo, hi); }

/* ---------------------------------------------------------------- */
static void test_numtheory(void) {
    CHECK(gcd(12, 18) == 6 && gcd(-4, 6) == 2 && gcd(0, 5) == 5 && lcm(4, 6) == 12);
    for (int it = 0; it < 1000; it++) {
        ll a = rnd(1, 1000000), b = rnd(1, 1000000), x, y;
        ll g = extgcd(a, b, &x, &y);
        CHECK(g == gcd(a, b) && a * x + b * y == g);
    }
    CHECK(powmod(2, 10, 1000) == 24 && powmod(3, 0, 7) == 1 && powmod(5, 3, 1) == 0);
    CHECK(modinv(3, 7) == 5 && modinv(10, 17) * 10 % 17 == 1);
    ll big = 1000000000000000003LL;
    CHECK(mulmod(big - 1, big - 1, big) == 1);
    CHECK(mulmod(-3, 5, 7) == 6);
    ll a, m;
    CHECK(crt2(2, 3, 3, 5, &a, &m) && a == 8 && m == 15);
    CHECK(crt2(2, 4, 4, 6, &a, &m) && a == 10 && m == 12);
    CHECK(!crt2(1, 4, 2, 6, &a, &m));
    sieve(100000);
    CHECK(nprimes == 9592 && primes[0] == 2 && primes[24] == 97);
    for (int n = 0; n < 100000; n++) CHECK(is_prime((ull)n) == (n >= 2 && spf[n] == n));
    CHECK(is_prime(1000000007ULL) && is_prime(2305843009213693951ULL) && !is_prime(561) && !is_prime(1000000007ULL * 998244353ULL));
    int p[20], e[20];
    int k = factor_spf(360, p, e);
    CHECK(k == 3 && p[0] == 2 && e[0] == 3 && p[1] == 3 && e[1] == 2 && p[2] == 5 && e[2] == 1);
    ll pl[20];
    k = factor_trial(600851475143LL, pl, e);
    CHECK(k == 4 && pl[3] == 6857);
    CHECK(euler_phi(36) == 12 && euler_phi(1) == 1 && euler_phi(97) == 96);
    CHECK(isqrt(1000000000000000000LL) == 1000000000LL && isqrt(999999999999999999LL) == 999999999LL && isqrt(0) == 0);
}

static void test_combin(void) {
    comb_init(2000);
    CHECK(nCr(10, 3) == 120 && nCr(5, 7) == 0 && nPr(5, 2) == 20 && catalan(5) == 42);
    static ll C[1001][1001];
    for (int n = 0; n <= 1000; n++)
        for (int r = 0; r <= n; r++) C[n][r] = (r == 0 || r == n) ? 1 : (C[n - 1][r - 1] + C[n - 1][r]) % MOD;
    for (int it = 0; it < 1000; it++) { int n = rnd(0, 1000), r = rnd(0, n); CHECK(nCr(n, r) == C[n][r]); }
    int a[6] = {1, 2, 3, 4, 5, 6}, cnt = 0;
    do cnt++; while (next_perm(a, 6));
    CHECK(cnt == 720 && a[0] == 1 && a[5] == 6);
    int b[4] = {1, 1, 2, 2}; cnt = 0;
    do cnt++; while (next_perm(b, 4));
    CHECK(cnt == 6);
    int out[5];
    nth_perm(4, 0, out); CHECK(out[0] == 1 && out[3] == 4);
    nth_perm(3, 5, out); CHECK(out[0] == 3 && out[1] == 2 && out[2] == 1);
    int q[5] = {1, 0, 3, 4, 2};
    CHECK(perm_cycles(q, 5) == 2);
}

static void test_matrix(void) {
    Mat f = mat_ident(2);
    f.a[0][0] = 1; f.a[0][1] = 1; f.a[1][0] = 1; f.a[1][1] = 0;
    ll x = 0, y = 1;                                    /* F(0), F(1) */
    for (int i = 0; i < 90; i++) { ll t = (x + y) % MOD; x = y; y = t; }
    Mat r = mat_pow(f, 90, MOD);
    CHECK(r.a[0][1] == x);                              /* [[1,1],[1,0]]^n = [[F(n+1),F(n)],[F(n),F(n-1)]] */
    static ll g[MAT_N][MAT_W];
    ll det;
    g[0][0] = 2; g[0][1] = 1; g[0][2] = 5;              /* 2x + y = 5 */
    g[1][0] = 1; g[1][1] = 3; g[1][2] = 10;             /* x + 3y = 10  ->  x = 1, y = 3 */
    CHECK(gauss_mod(g, 2, 3, MOD, NULL) == 2 && g[0][2] == 1 && g[1][2] == 3);
    g[0][0] = 2; g[0][1] = 0; g[1][0] = 0; g[1][1] = 3;
    gauss_mod(g, 2, 2, MOD, &det); CHECK(det == 6);
    g[0][0] = 0; g[0][1] = 1; g[1][0] = 1; g[1][1] = 0;
    gauss_mod(g, 2, 2, MOD, &det); CHECK(det == MOD - 1);
    g[0][0] = 1; g[0][1] = 2; g[1][0] = 2; g[1][1] = 4;
    CHECK(gauss_mod(g, 2, 2, MOD, &det) == 1 && det == 0);
    static double d[MAT_N][MAT_W];
    d[0][0] = 2; d[0][1] = 1; d[0][2] = 5; d[1][0] = 1; d[1][1] = 3; d[1][2] = 10;
    CHECK(gauss_double(d, 2, 3, 1e-9) == 2 && fabs(d[0][2] - 1) < 1e-9 && fabs(d[1][2] - 3) < 1e-9);
}

static void test_fft(void) {
    static ll a[300], b[300], c[600], naive[600];
    for (int it = 0; it < 20; it++) {
        int na = rnd(1, 300), nb = rnd(1, 300);
        for (int i = 0; i < na; i++) a[i] = rnd(0, 1000000);
        for (int i = 0; i < nb; i++) b[i] = rnd(0, 1000000);
        memset(naive, 0, sizeof naive);
        for (int i = 0; i < na; i++)
            for (int j = 0; j < nb; j++) naive[i + j] = (naive[i + j] + a[i] * b[j]) % NTT_MOD;
        int nc = poly_mul(a, na, b, nb, c);
        CHECK(nc == na + nb - 1);
        int ok = 1;
        for (int i = 0; i < nc; i++) ok &= c[i] == naive[i];
        CHECK(ok);
    }
}

static void test_sort_search(void) {
    static int a[2000], b[2000], v[2000];
    for (int it = 0; it < 50; it++) {
        int n = rnd(1, 2000);
        for (int i = 0; i < n; i++) a[i] = b[i] = rnd(-50, 50);
        ll inv = 0;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) inv += b[i] > b[j];
        CHECK(count_inversions(a, n) == inv);
        sort_int(b, n);
        int ok = 1;
        for (int i = 0; i < n; i++) ok &= a[i] == b[i];
        CHECK(ok);
        for (int x = -52; x <= 52; x++) {
            int lb = 0, ub = 0;
            while (lb < n && b[lb] < x) lb++;
            while (ub < n && b[ub] <= x) ub++;
            CHECK(lower_bound_int(b, n, x) == lb && upper_bound_int(b, n, x) == ub);
        }
        for (int i = 0; i < n; i++) a[i] = rnd(-1000, 1000);
        int k = rnd(0, n - 1);
        memcpy(v, a, sizeof(int) * (size_t)n);
        sort_int(v, n);
        int want = v[k];
        CHECK(kth_smallest(a, n, k) == want);
    }
    int c[6] = {50, -3, 50, 7, 7, 1000}, vals[6];
    int m = compress(c, 6, vals);
    CHECK(m == 4 && c[0] == 2 && c[1] == 0 && c[3] == 1 && c[5] == 3 && vals[3] == 1000);
}

static int sq_ge_1000(ll x) { return x * x >= 1000; }
static int real_sq_ge_2(double x) { return x * x >= 2; }
static ll parabola(ll x) { return (x - 37) * (x - 37) + 5; }
static double parabola_d(double x) { return (x - 1.5) * (x - 1.5); }

static void test_search_answer(void) {
    CHECK(bs_first_true(0, 1000, sq_ge_1000) == 32);
    CHECK(bs_first_true(0, 10, sq_ge_1000) == 11);
    CHECK(fabs(bs_real(0, 2, real_sq_ge_2) - 1.41421356237) < 1e-9);
    CHECK(ternary_min_int(-1000, 1000, parabola) == 37);
    CHECK(fabs(ternary_min_real(-10, 10, parabola_d) - 1.5) < 1e-6);
}

static void test_bits(void) {
    CHECK(POPCOUNT(255) == 8 && CTZ(40) == 3 && LOWBIT(40) == 8 && is_pow2(64) && !is_pow2(0) && log2_floor(1000) == 9);
    for (ull i = 0; i < 1000; i++) {
        CHECK(POPCOUNT(gray(i) ^ gray(i + 1)) == 1);
        CHECK(gray_inv(gray(i)) == i);
    }
    int subs = 0;
    FOR_SUBMASKS(s, 0xB) subs++;
    CHECK(subs == 7);
    static ll f[1 << 10], g[1 << 10];
    for (int i = 0; i < 1024; i++) f[i] = g[i] = rnd(0, 100);
    sos_subsets(f, 10);
    int ok = 1;
    for (int m = 0; m < 1024; m++) {
        ll s = g[0];
        FOR_SUBMASKS(t, m) s += g[t];
        ok &= (m == 0 ? g[0] : s) == f[m];
    }
    CHECK(ok);
    for (int it = 0; it < 50; it++) {
        XorBasis xb;
        memset(&xb, 0, sizeof xb);
        int n = rnd(1, 10), val[10];
        for (int i = 0; i < n; i++) { val[i] = rnd(0, 255); xb_insert(&xb, (ull)val[i]); }
        static char reach[256];
        memset(reach, 0, sizeof reach);
        ull best = 0;
        int distinct = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            int x = 0;
            for (int i = 0; i < n; i++) if (mask >> i & 1) x ^= val[i];
            if (!reach[x]) { reach[x] = 1; distinct++; }
            if ((ull)x > best) best = (ull)x;
        }
        CHECK(xb_max(&xb, 0) == best);
        CHECK(distinct == (1 << xb_rank(&xb)));
        int q = rnd(0, 255);
        CHECK(xb_contains(&xb, (ull)q) == reach[q]);
    }
}

static void test_linear_heap(void) {
    static int a[3000], res[3000], out[3000];
    for (int it = 0; it < 30; it++) {
        int n = rnd(1, 3000), k = rnd(1, n);
        for (int i = 0; i < n; i++) a[i] = rnd(0, 20);
        next_greater(a, n, res);
        int ok = 1;
        for (int i = 0; i < n; i++) { int j = i + 1; while (j < n && a[j] <= a[i]) j++; ok &= res[i] == j; }
        CHECK(ok);
        prev_smaller(a, n, res); ok = 1;
        for (int i = 0; i < n; i++) { int j = i - 1; while (j >= 0 && a[j] >= a[i]) j--; ok &= res[i] == j; }
        CHECK(ok);
        sliding_max(a, n, k, out); ok = 1;
        for (int i = 0; i + k <= n; i++) { int mx = a[i]; for (int j = i; j < i + k; j++) mx = MAX(mx, a[j]); ok &= out[i] == mx; }
        CHECK(ok);
        if (n <= 400) {
            ll best = 0;
            for (int l = 0; l < n; l++) { int mn = INT_MAX; for (int r = l; r < n; r++) { mn = MIN(mn, a[r]); best = MAX(best, (ll)mn * (r - l + 1)); } }
            CHECK(max_histogram(a, n) == best);
        }
    }
    static Deque dq;
    dq_clear(&dq);
    dq_push_back(&dq, 1); dq_push_back(&dq, 2); dq_push_front(&dq, 0);
    CHECK(dq_front(&dq) == 0 && dq_back(&dq) == 2 && dq.size == 3);
    CHECK(dq_pop_back(&dq) == 2 && dq_pop_front(&dq) == 0 && dq_pop_front(&dq) == 1 && dq_empty(&dq));
    static Heap h;
    static ll keys[5000];
    heap_clear(&h);
    for (int i = 0; i < 5000; i++) { keys[i] = rnd(-100000, 100000); heap_push(&h, keys[i], i); }
    sort_ll(keys, 5000);
    int ok = 1;
    for (int i = 0; i < 5000; i++) { HeapItem t = heap_pop(&h); ok &= t.key == keys[i]; }
    CHECK(ok && heap_empty(&h));
}

static void test_dsu(void) {
    for (int it = 0; it < 20; it++) {
        int n = rnd(1, 200), lab[200];
        dsu_init(n);
        for (int i = 0; i < n; i++) lab[i] = i;
        for (int q = 0; q < 300; q++) {
            int a = rnd(0, n - 1), b = rnd(0, n - 1);
            int merged = dsu_union(a, b), la = lab[a], lb = lab[b];
            CHECK(merged == (la != lb));
            for (int i = 0; i < n; i++) if (lab[i] == lb) lab[i] = la;
            int c = rnd(0, n - 1), d = rnd(0, n - 1), sz = 0;
            CHECK(dsu_same(c, d) == (lab[c] == lab[d]));
            for (int i = 0; i < n; i++) sz += lab[i] == lab[c];
            CHECK(dsu_size(c) == sz);
        }
        int sets = 0;
        for (int i = 0; i < n; i++) { int first = 1; for (int j = 0; j < i; j++) if (lab[j] == lab[i]) first = 0; sets += first; }
        CHECK(dsu_sets == sets);
    }
    pdsu_init(4);                                       /* triangle 0-1-2 is an odd cycle */
    CHECK(pdsu_union(0, 1, 1) && pdsu_union(1, 2, 1) && !pdsu_union(0, 2, 1) && pdsu_union(2, 3, 1) && pdsu_union(0, 3, 1));
}

static void test_fenwick_segtree(void) {
    static ll a[600], b[600];
    int n = 500;
    fen_init(n);
    fenr_init(n);
    for (int i = 1; i <= n; i++) a[i] = 0;
    for (int q = 0; q < 3000; q++) {
        int l = rnd(1, n), r = rnd(l, n);
        ll v = rnd(0, 100);
        fen_add(l, v); a[l] += v;
        fenr_add(l, r, v); for (int i = l; i <= r; i++) b[i] += v;
        int x = rnd(1, n), y = rnd(x, n);
        ll s1 = 0, s2 = 0;
        for (int i = x; i <= y; i++) { s1 += a[i]; s2 += b[i]; }
        CHECK(fen_range(x, y) == s1);
        CHECK(fenr_sum(x, y) == s2);
        ll k = rnd(1, (int)MIN(fen_sum(n) + 5, 2000000000LL)), pre = 0;
        int want = n + 1;
        for (int i = 1; i <= n; i++) { pre += a[i]; if (pre >= k) { want = i; break; } }
        CHECK(fen_lower_bound(k) == want);
    }
    static ll c[777];
    int m = 777;
    for (int i = 0; i < m; i++) c[i] = rnd(-1000, 1000);
    seg_init(m, c);
    lz_init(m, c);
    for (int q = 0; q < 3000; q++) {
        int i = rnd(0, m - 1), l = rnd(0, m - 1), r = rnd(l, m - 1), type = rnd(0, 2);
        ll v = rnd(-1000, 1000);
        if (type == 0) { c[i] = v; seg_set(i, v); lz_assign(i, i, v); }
        else if (type == 1) { for (int j = l; j <= r; j++) c[j] += v; lz_add(l, r, v); for (int j = l; j <= r; j++) seg_set(j, c[j]); }
        else { for (int j = l; j <= r; j++) c[j] = v; lz_assign(l, r, v); for (int j = l; j <= r; j++) seg_set(j, c[j]); }
        int x = rnd(0, m - 1), y = rnd(x, m - 1);
        ll s = 0, mx = -LINF;
        for (int j = x; j <= y; j++) { s += c[j]; mx = MAX(mx, c[j]); }
        CHECK(seg_query(x, y) == s && lz_sum(x, y) == s && lz_max(x, y) == mx && seg_get(x) == c[x]);
    }
    sp_build(c, m);
    for (int q = 0; q < 1000; q++) {
        int x = rnd(0, m - 1), y = rnd(x, m - 1);
        ll mn = LINF;
        for (int j = x; j <= y; j++) mn = MIN(mn, c[j]);
        CHECK(sp_query(x, y) == mn);
    }
}

static void test_hash_trie(void) {
    static ll cnt[2001];
    hm_clear();
    for (int i = 0; i < 20000; i++) { int k = rnd(-1000, 1000); hm_add((ll)k * 1000000007LL, 1); cnt[k + 1000]++; }
    int ok = 1;
    for (int k = -1000; k <= 1000; k++) ok &= hm_get((ll)k * 1000000007LL, 0) == cnt[k + 1000];
    CHECK(ok && hm_get(5, -1) == -1);
    hm_set(42, 7); CHECK(hm_get(42, 0) == 7);
    hm_clear(); CHECK(hm_get(42, -1) == -1 && hm_size == 0);
    CHECK(sm_id("apple") == 0 && sm_id("pear") == 1 && sm_id("apple") == 0 && sm_get("plum") == -1 && sm_count == 2);
    CHECK(strcmp(sm_str(1), "pear") == 0);

    const char *words[] = {"he", "she", "his", "hers", "he"};
    for (int i = 0; i < 5; i++) trie_insert(words[i]);
    CHECK(trie_count_prefix("h") == 4 && trie_count_prefix("he") == 3 && trie_count_word("he") == 2 && trie_count_word("her") == 0 && trie_count_prefix("x") == 0);
    ac_build();
    const char *text = "ahishershe";                    /* brute force count below */
    ll brute = 0;
    for (int i = 0; i < 5; i++) {
        int len = (int)strlen(words[i]);
        for (int j = 0; j + len <= (int)strlen(text); j++) brute += strncmp(text + j, words[i], (size_t)len) == 0;
    }
    CHECK(ac_count(text) == brute);

    static int vals[3000];
    int n = 0;
    for (int it = 0; it < 3000; it++) {
        int op = rnd(0, 3);
        if (op < 2 || n == 0) { vals[n] = rnd(0, (1 << 20)); bt_insert(vals[n], 1); n++; }
        else if (op == 2) { int i = rnd(0, n - 1); bt_insert(vals[i], -1); vals[i] = vals[--n]; }
        if (n == 0) continue;
        int x = rnd(0, (1 << 20)), k = rnd(0, (1 << 21)), best = 0, less = 0;
        for (int i = 0; i < n; i++) { best = MAX(best, x ^ vals[i]); less += (x ^ vals[i]) < k; }
        CHECK(bt_max_xor(x) == best);
        CHECK(bt_count_less(x, k) == less);
    }
}

/* random graph helpers */
static int adj[60][60];

static void test_graph(void) {
    static int dist[100], comp[100], color[100], order[100];
    static ll dd[100];
    for (int it = 0; it < 200; it++) {
        int n = rnd(1, 40), m = rnd(0, 80);
        g_init(n);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) adj[i][j] = (i == j) ? 0 : INF;
        Edge e[200];
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1), w = rnd(0, 20);
            g_add2(u, v, w);
            e[i].u = u; e[i].v = v; e[i].w = w;
            if (u != v) { adj[u][v] = MIN(adj[u][v], w); adj[v][u] = MIN(adj[v][u], w); }
        }
        /* reachability and weighted distances by Floyd */
        static int reach[60][60], wd[60][60];
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) { wd[i][j] = adj[i][j]; reach[i][j] = (i == j) || adj[i][j] < INF; }
        for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            reach[i][j] |= reach[i][k] && reach[k][j];
            if (wd[i][k] + wd[k][j] < wd[i][j]) wd[i][j] = wd[i][k] + wd[k][j];
        }
        int src = rnd(0, n - 1);
        dijkstra(src, dd, NULL);
        int ok = 1;
        for (int v = 0; v < n; v++) ok &= (wd[src][v] >= INF) ? dd[v] == LINF : dd[v] == wd[src][v];
        CHECK(ok);
        int k = components(comp); ok = 1;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) ok &= (comp[i] == comp[j]) == reach[i][j];
        CHECK(ok);
        ll mst = kruskal(n, e, m);
        CHECK((dsu_sets == k));
        /* Prim on the multigraph for comparison (per component) */
        ll prim = 0;
        static int in[60]; static ll key[60];
        for (int i = 0; i < n; i++) { in[i] = 0; key[i] = LINF; }
        for (int s = 0; s < n; s++) {
            if (in[s]) continue;
            key[s] = 0;
            for (;;) {
                int u = -1;
                for (int i = 0; i < n; i++) if (!in[i] && key[i] < LINF && (u < 0 || key[i] < key[u])) u = i;
                if (u < 0) break;
                in[u] = 1; prim += key[u];
                for (int v = 0; v < n; v++) if (!in[v] && adj[u][v] < INF && adj[u][v] < key[v]) key[v] = adj[u][v];
            }
        }
        CHECK(mst == prim);
        /* bridges: removing edge i disconnects its endpoints? (brute force with DSU) */
        int nb = bridges(), brute = 0;
        g_init(n);
        for (int i = 0; i < m; i++) g_add2(e[i].u, e[i].v, e[i].w);
        nb = bridges();
        ok = 1;
        for (int i = 0; i < m; i++) {
            dsu_init(n);
            for (int j = 0; j < m; j++) if (j != i) dsu_union(e[j].u, e[j].v);
            int isb = !dsu_same(e[i].u, e[i].v);
            brute += isb;
            ok &= g_bridge[2 * i] == isb && g_bridge[2 * i + 1] == isb;
        }
        CHECK(ok && nb == brute);
        /* articulation points */
        ok = 1;
        dsu_init(n);
        for (int j = 0; j < m; j++) dsu_union(e[j].u, e[j].v);
        int base = dsu_sets;
        for (int v = 0; v < n; v++) {
            dsu_init(n);
            for (int j = 0; j < m; j++) if (e[j].u != v && e[j].v != v) dsu_union(e[j].u, e[j].v);
            int cut = dsu_sets - 1 > base;               /* without v (an isolated singleton now) */
            ok &= g_cut[v] == cut;
        }
        CHECK(ok);
        /* bipartite vs brute force over colorings for tiny n */
        if (n <= 12) {
            int any = 0;
            for (int mask = 0; mask < (1 << n) && !any; mask++) {
                int good = 1;
                for (int i = 0; i < m; i++) if ((mask >> e[i].u & 1) == (mask >> e[i].v & 1)) good = 0;
                any |= good;
            }
            CHECK(bipartite(color) == any);
        }
        bfs(src, dist);
        bfs01(src, dd);                                 /* weights are 0..20 here: only compare with 0/1 below */
        (void)dd;
    }
    /* directed: toposort, scc, bfs, bfs01, bellman-ford */
    for (int it = 0; it < 200; it++) {
        int n = rnd(1, 30), m = rnd(0, 60);
        g_init(n);
        static int reach[60][60], w01[60][60];
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) { reach[i][j] = i == j; w01[i][j] = i == j ? 0 : INF; }
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1), w = rnd(0, 1);
            g_add(u, v, w);
            reach[u][v] = 1;
            w01[u][v] = MIN(w01[u][v], w);
        }
        for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            reach[i][j] |= reach[i][k] && reach[k][j];
            if (w01[i][k] + w01[k][j] < w01[i][j]) w01[i][j] = w01[i][k] + w01[k][j];
        }
        int cyc = 0;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (i != j && reach[i][j] && reach[j][i]) cyc = 1;
        for (int u = 0; u < n; u++) G_EACH(e, u) if (g_to[e] == u) cyc = 1;
        int placed = toposort(order);
        CHECK((placed < n) == cyc);
        if (!cyc) {
            static int posn[60];
            for (int i = 0; i < n; i++) posn[order[i]] = i;
            int ok = 1;
            for (int u = 0; u < n; u++) G_EACH(e, u) ok &= posn[u] < posn[g_to[e]];
            CHECK(ok);
        }
        scc();
        int ok = 1;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            ok &= (scc_id[i] == scc_id[j]) == (reach[i][j] && reach[j][i]);
            if (reach[i][j] && scc_id[i] != scc_id[j]) ok &= scc_id[i] > scc_id[j];
        }
        CHECK(ok);
        int src = rnd(0, n - 1);
        bfs01(src, dd);
        ok = 1;
        for (int v = 0; v < n; v++) ok &= (w01[src][v] >= INF) ? dd[v] == LINF : dd[v] == w01[src][v];
        CHECK(ok);
        bfs(src, dist);
        ok = 1;
        for (int v = 0; v < n; v++) ok &= (dist[v] >= 0) == (reach[src][v] != 0);
        CHECK(ok);
    }
    /* Bellman-Ford and Floyd with negative edges on a DAG (i -> j only for i < j) */
    for (int it = 0; it < 100; it++) {
        int n = rnd(2, 30);
        g_init(n);
        fw_init(n);
        for (int i = 0; i < 60; i++) {
            int u = rnd(0, n - 2), v = rnd(u + 1, n - 1), w = rnd(-20, 20);
            g_add(u, v, w);
            fw[u][v] = MIN(fw[u][v], (ll)w);
        }
        floyd(n);
        CHECK(bellman_ford(0, dd));
        int ok = 1;
        for (int v = 0; v < n; v++) ok &= dd[v] == fw[0][v];
        CHECK(ok);
    }
    g_init(3);
    g_add(0, 1, 1); g_add(1, 2, -3); g_add(2, 1, 1);
    CHECK(!bellman_ford(0, dd));
    /* dijkstra path reconstruction */
    g_init(4);
    g_add2(0, 1, 1); g_add2(1, 2, 1); g_add2(0, 2, 5); g_add2(2, 3, 1);
    static int prev[4], path[4];
    dijkstra(0, dd, prev);
    int k = build_path(prev, 3, path);
    CHECK(dd[3] == 3 && k == 4 && path[0] == 0 && path[1] == 1 && path[2] == 2 && path[3] == 3);
}

static void test_flow(void) {
    /* classic CLRS network, max flow 23 */
    flow_init(6);
    flow_add(0, 1, 16); flow_add(0, 2, 13); flow_add(1, 3, 12); flow_add(2, 1, 4);
    flow_add(2, 4, 14); flow_add(3, 2, 9); flow_add(3, 5, 20); flow_add(4, 3, 7); flow_add(4, 5, 4);
    CHECK(max_flow(0, 5) == 23);
    /* bipartite matching vs flow and brute force; assignment via mcmf vs permutations */
    for (int it = 0; it < 100; it++) {
        int nl = rnd(1, 7), nr = rnd(1, 7);
        static int ok_edge[8][8];
        g_init(nl);
        flow_init(nl + nr + 2);
        for (int i = 0; i < nl; i++) flow_add(nl + nr, i, 1);
        for (int j = 0; j < nr; j++) flow_add(nl + j, nl + nr + 1, 1);
        for (int i = 0; i < nl; i++) for (int j = 0; j < nr; j++) {
            ok_edge[i][j] = rnd(0, 2) == 0;
            if (ok_edge[i][j]) { g_add(i, j, 0); flow_add(i, nl + j, 1); }
        }
        int mt = bipartite_matching(nl, nr);
        CHECK(mt == max_flow(nl + nr, nl + nr + 1));
        int valid = 1;
        for (int i = 0; i < nl; i++) if (mt_left[i] >= 0) valid &= ok_edge[i][mt_left[i]] && mt_right[mt_left[i]] == i;
        CHECK(valid);
        int n = rnd(1, 6), cost[6][6], p[6];
        mcmf_init(2 * n + 2);
        for (int i = 0; i < n; i++) { mcmf_add(2 * n, i, 1, 0); mcmf_add(n + i, 2 * n + 1, 1, 0); }
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) { cost[i][j] = rnd(-10, 50); mcmf_add(i, n + j, 1, cost[i][j]); }
        ll c;
        CHECK(mcmf(2 * n, 2 * n + 1, LINF, &c) == n);
        for (int i = 0; i < n; i++) p[i] = i;
        ll best = LINF;
        do { ll s = 0; for (int i = 0; i < n; i++) s += cost[i][p[i]]; best = MIN(best, s); } while (next_perm(p, n));
        CHECK(c == best);
    }
}

static int hpos_val[200];
static ll hsum;
static void hld_sum_cb(int l, int r) { for (int i = l; i <= r; i++) hsum += hpos_val[i]; }

static void test_tree(void) {
    static int par[200], val[200];
    for (int it = 0; it < 100; it++) {
        int n = rnd(1, 150), root = rnd(0, n - 1);
        g_init(n);
        for (int i = 0; i < n; i++) par[i] = -1;
        static int perm[200];
        for (int i = 0; i < n; i++) perm[i] = i;
        shuffle_int(perm, n);
        for (int i = 1; i < n; i++) { int p = perm[rnd(0, i - 1)]; g_add2(perm[i], p, rnd(0, 9)); }
        lca_init(root);
        /* naive parent pointers from tree_root */
        for (int i = 0; i < n; i++) par[i] = t_par[i];
        int ok = 1;
        for (int q = 0; q < 200; q++) {
            int a = rnd(0, n - 1), b = rnd(0, n - 1), x = a, y = b;
            while (t_dep[x] > t_dep[y]) x = par[x];
            while (t_dep[y] > t_dep[x]) y = par[y];
            while (x != y) { x = par[x]; y = par[y]; }
            ok &= lca(a, b) == x;
        }
        CHECK(ok);
        /* subtree ranges: v in subtree(u) iff tin[u] <= tin[v] <= tout[u] */
        ok = 1;
        for (int q = 0; q < 200; q++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1), x = v, inside = 0;
            while (x != -1) { if (x == u) inside = 1; x = par[x]; }
            ok &= inside == (t_tin[u] <= t_tin[v] && t_tin[v] <= t_tout[u]);
        }
        CHECK(ok);
        /* diameter by brute force (all pairs tree_dist) */
        ll best = 0;
        for (int a = 0; a < n; a++) for (int b = 0; b < n; b++) best = MAX(best, tree_dist(a, b));
        int da, db;
        CHECK(tree_diameter(root, &da, &db) == best);
        /* HLD path sums vs naive walk */
        hld_build(root);
        for (int i = 0; i < n; i++) { val[i] = rnd(0, 100); hpos_val[t_pos[i]] = val[i]; }
        lca_init(root);
        ok = 1;
        for (int q = 0; q < 200; q++) {
            int a = rnd(0, n - 1), b = rnd(0, n - 1), l = lca(a, b);
            ll s = 0, s_edges;
            for (int x = a; x != l; x = t_par[x]) s += val[x];
            for (int x = b; x != l; x = t_par[x]) s += val[x];
            s_edges = s;
            s += val[l];
            hsum = 0; hld_path(a, b, 0, hld_sum_cb); ok &= hsum == s;
            hsum = 0; hld_path(a, b, 1, hld_sum_cb); ok &= hsum == s_edges;
            ok &= hld_lca(a, b) == l;
            ok &= kth_ancestor(a, t_dep[a] - t_dep[l]) == l;
        }
        CHECK(ok);
        ok = 1;
        for (int v = 0; v < n; v++) for (int u = 0; u < n; u++) {
            int x = u, inside = 0;
            while (x != -1) { if (x == v) inside = 1; x = t_par[x]; }
            ok &= inside == (t_pos[v] <= t_pos[u] && t_pos[u] < t_pos[v] + t_sz[v]);
        }
        CHECK(ok);
    }
}

static void test_strings(void) {
    static char s[2100], t[20];
    static int pos[2100], z[2100], d1[2100], d2[2100], sa[2100], lcp[2100], pi[2100];
    for (int it = 0; it < 100; it++) {
        int n = rnd(1, 2000), m = rnd(1, 5), alpha = rnd(1, 3);
        for (int i = 0; i < n; i++) s[i] = (char)('a' + rnd(0, alpha - 1));
        s[n] = 0;
        for (int i = 0; i < m; i++) t[i] = (char)('a' + rnd(0, alpha - 1));
        t[m] = 0;
        int cnt = kmp_search(s, n, t, m, pos), brute = 0, ok = 1;
        for (int i = 0; i + m <= n; i++) if (strncmp(s + i, t, (size_t)m) == 0) { ok &= brute < cnt && pos[brute] == i; brute++; }
        CHECK(ok && cnt == brute);
        if (n <= 300) {
            z_function(s, n, z);
            prefix_function(s, n, pi);
            ok = 1;
            for (int i = 0; i < n; i++) {
                int k = 0;
                while (i + k < n && s[k] == s[i + k]) k++;
                ok &= z[i] == k;
                int best = 0;
                for (int len = 1; len <= i; len++) if (strncmp(s, s + i + 1 - len, (size_t)len) == 0) best = len;
                ok &= pi[i] == best;
            }
            CHECK(ok);
            manacher(s, n, d1, d2);
            ll pals = 0, brute_p = 0;
            for (int i = 0; i < n; i++) pals += d1[i] + d2[i];
            int longest = 0;
            for (int l = 0; l < n; l++) for (int r = l; r < n; r++) {
                int p = 1;
                for (int a = l, b = r; a < b; a++, b--) if (s[a] != s[b]) { p = 0; break; }
                brute_p += p;
                if (p) longest = MAX(longest, r - l + 1);
            }
            int st;
            CHECK(pals == brute_p);
            CHECK(longest_palindrome(s, n, &st) == longest);
            suffix_array(s, n, sa);
            ok = 1;
            for (int i = 0; i + 1 < n; i++) ok &= strcmp(s + sa[i], s + sa[i + 1]) < 0;
            CHECK(ok);
            lcp_array(s, n, sa, lcp);
            ok = 1;
            for (int i = 0; i + 1 < n; i++) { int k = 0; while (s[sa[i] + k] && s[sa[i] + k] == s[sa[i + 1] + k]) k++; ok &= lcp[i] == k; }
            CHECK(ok);
        }
        hash_build(s, n);
        ok = 1;
        for (int q = 0; q < 200; q++) {
            int len = rnd(1, MIN(n, 6)), a = rnd(0, n - len), b = rnd(0, n - len);
            ok &= (hash_sub(a, len) == hash_sub(b, len)) == (strncmp(s + a, s + b, (size_t)len) == 0);
        }
        CHECK(ok);
    }
    char r[] = "abcde";
    str_reverse(r, 5);
    CHECK(strcmp(r, "edcba") == 0);
}

static void test_geom(void) {
    Pt sq[4] = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    CHECK(polygon_area2(sq, 4) == 8 && lattice_boundary(sq, 4) == 8 && lattice_interior(sq, 4) == 1);
    CHECK(in_polygon(sq, 4, (Pt){1, 1}) == 1 && in_polygon(sq, 4, (Pt){2, 1}) == 2 && in_polygon(sq, 4, (Pt){3, 1}) == 0);
    Pt conc[6] = {{0, 0}, {4, 0}, {4, 4}, {2, 1}, {0, 4}, {0, 0}};   /* concave, last point duplicates first */
    CHECK(in_polygon(conc, 5, (Pt){2, 3}) == 0 && in_polygon(conc, 5, (Pt){1, 1}) == 1 && in_polygon(conc, 5, (Pt){3, 2}) == 1);
    CHECK(seg_intersect((Pt){0, 0}, (Pt){2, 2}, (Pt){0, 2}, (Pt){2, 0}));
    CHECK(seg_intersect((Pt){0, 0}, (Pt){2, 0}, (Pt){2, 0}, (Pt){3, 5}));
    CHECK(!seg_intersect((Pt){0, 0}, (Pt){1, 1}, (Pt){2, 2}, (Pt){3, 3}));
    CHECK(seg_intersect((Pt){0, 0}, (Pt){2, 2}, (Pt){1, 1}, (Pt){3, 3}));
    for (int it = 0; it < 100; it++) {
        int n = rnd(1, 60);
        Pt p[61], h[62], copy[61];
        for (int i = 0; i < n; i++) p[i] = copy[i] = (Pt){rnd(-10, 10), rnd(-10, 10)};
        int k = convex_hull(p, n, h);
        int ok = 1;
        if (k >= 3) {
            for (int i = 0; i < k; i++) ok &= cross3(h[i], h[(i + 1) % k], h[(i + 2) % k]) > 0;   /* strictly convex, ccw */
            for (int i = 0; i < n; i++) ok &= in_polygon(h, k, copy[i]) > 0;                   /* contains all points */
        }
        CHECK(ok);
    }
    Pd o;
    CHECK(line_intersect((Pd){0, 0}, (Pd){2, 2}, (Pd){0, 2}, (Pd){2, 0}, &o) && fabs(o.x - 1) < 1e-9 && fabs(o.y - 1) < 1e-9);
    CHECK(!line_intersect((Pd){0, 0}, (Pd){1, 1}, (Pd){0, 1}, (Pd){1, 2}, &o));
    CHECK(fabs(dist_pt_seg((Pd){0, 1}, (Pd){-1, 0}, (Pd){1, 0}) - 1) < 1e-9 && fabs(dist_pt_seg((Pd){3, 4}, (Pd){0, 0}, (Pd){-1, 0}) - 5) < 1e-9);
    CHECK(dist2((Pt){0, 0}, (Pt){3, 4}) == 25 && dot3((Pt){0, 0}, (Pt){1, 0}, (Pt){0, 1}) == 0);
}

static void test_dp(void) {
    ll arr[5] = {-2, 3, -1, 4, -10};
    CHECK(max_subarray(arr, 5) == 6);
    ll neg[3] = {-5, -2, -7};
    CHECK(max_subarray(neg, 3) == -2);
    for (int it = 0; it < 100; it++) {
        int n = rnd(1, 200), a[200], f[200], best = 0, bestw = 0;
        for (int i = 0; i < n; i++) a[i] = rnd(0, 20);
        for (int strict = 0; strict < 2; strict++) {
            best = 0;
            for (int i = 0; i < n; i++) {
                f[i] = 1;
                for (int j = 0; j < i; j++) if (strict ? a[j] < a[i] : a[j] <= a[i]) f[i] = MAX(f[i], f[j] + 1);
                best = MAX(best, f[i]);
            }
            CHECK(lis_length(a, n, strict) == best);
        }
        int k = rnd(1, 12), w[12], cap = rnd(0, 60);
        ll v[12];
        for (int i = 0; i < k; i++) { w[i] = rnd(1, 20); v[i] = rnd(0, 100); }
        ll bv = 0;
        for (int mask = 0; mask < (1 << k); mask++) {
            int ws = 0; ll vs = 0;
            for (int i = 0; i < k; i++) if (mask >> i & 1) { ws += w[i]; vs += v[i]; }
            if (ws <= cap) bv = MAX(bv, vs);
        }
        CHECK(knapsack01(w, v, k, cap) == bv);
        (void)bestw;
    }
    CHECK(lcs_length("ABCBDAB", "BDCABA") == 4 && lcs_length("", "abc") == 0);
    CHECK(edit_distance("kitten", "sitting") == 3 && edit_distance("", "abc") == 3 && edit_distance("same", "same") == 0);
    int coins[3] = {1, 3, 4}, c2[2] = {4, 6};
    CHECK(coin_min(coins, 3, 6) == 2 && coin_min(c2, 2, 7) == -1 && coin_min(c2, 2, 0) == 0);
    int c3[3] = {1, 2, 5};
    CHECK(coin_ways(c3, 3, 5, MOD) == 4 && coin_ways(c3, 3, 0, MOD) == 1);
    static ll d[TSP_N][TSP_N];
    for (int it = 0; it < 30; it++) {
        int n = rnd(1, 7), p[8];
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) d[i][j] = (i == j) ? 0 : (rnd(0, 4) == 0 ? LINF : rnd(1, 50));
        ll best = LINF;
        for (int i = 0; i < n; i++) p[i] = i;
        do {
            if (p[0] != 0) break;
            ll s = 0;
            for (int i = 0; i < n && s < LINF; i++) { ll c = d[p[i]][p[(i + 1) % n]]; s = (c == LINF) ? LINF : s + c; }
            best = MIN(best, s);
        } while (next_perm(p, n));
        CHECK(tsp(n, d) == best);
    }
}

static void test_game(void) {
    int moves[2] = {1, 2}, g[50];
    grundy_subtraction(49, moves, 2, g);
    int ok = 1;
    for (int x = 0; x <= 49; x++) ok &= g[x] == x % 3;
    CHECK(ok);
    int v[4] = {0, 1, 3, 1};
    CHECK(mex(v, 4) == 2 && mex(v, 0) == 0);
    ll piles[3] = {3, 4, 5};
    CHECK(nim_xor(piles, 3) == 2);
    g_init(4);                                          /* 0->1->2, 0->2, 3 isolated */
    g_add(0, 1, 0); g_add(1, 2, 0); g_add(0, 2, 0);
    int gd[4];
    CHECK(grundy_dag(gd) && gd[2] == 0 && gd[1] == 1 && gd[0] == 2 && gd[3] == 0);
}

static void test_bignum(void) {
    static Big a, b, c, d;
    bn_from_ll(&a, 1);
    for (int i = 2; i <= 30; i++) bn_mul_small(&a, &a, i);
    bn_from_str(&b, "265252859812191058636308480000000");
    CHECK(bn_cmp(&a, &b) == 0);
    bn_from_str(&c, "123456789012345678901234567890");
    bn_from_str(&d, "987654321098765432109876543210");
    Big e;
    bn_mul(&e, &c, &d);
    bn_from_str(&a, "121932631137021795226185032733622923332237463801111263526900");
    CHECK(bn_cmp(&e, &a) == 0);
    bn_add(&e, &c, &d);
    bn_from_str(&a, "1111111110111111111011111111100");
    CHECK(bn_cmp(&e, &a) == 0);
    bn_sub(&e, &d, &c);
    bn_from_str(&a, "864197532086419753208641975320");
    CHECK(bn_cmp(&e, &a) == 0);
    int rem = bn_div_small(&e, &d, 7);
    int r = 0;                                          /* the remainder digit by digit */
    for (const char *p = "987654321098765432109876543210"; *p; p++) r = (r * 10 + (*p - '0')) % 7;
    CHECK(rem == r);
    bn_mul_small(&e, &e, 7);
    bn_from_ll(&a, r);
    bn_add(&e, &e, &a);
    CHECK(bn_cmp(&e, &d) == 0);
    bn_from_str(&a, "000");
    bn_from_ll(&b, 0);
    CHECK(bn_cmp(&a, &b) == 0 && a.n == 1);
}

static char grid_g[GRID_MAX][GRID_MAX], grid_r[GRID_MAX][GRID_MAX];
static ll cell_hash(int r, int c) { return grid_g[r][c] == '#'; }

static void test_grid_util(void) {
    const char *maze[4] = {"S..#", ".#.#", ".#..", "...#"};
    for (int r = 0; r < 4; r++) strcpy(grid_g[r], maze[r]);
    grid_bfs(grid_g, 4, 4, 0, 0, '#');
    CHECK(grid_dist[2][3] == 5 && grid_dist[0][3] == -1 && grid_dist[3][0] == 3);
    int sizes[20];
    int k = grid_regions(grid_g, 4, 4, '.', sizes);   /* '#' regions: (0,3)-(1,3), (1,1)-(2,1), (3,3) */
    CHECK(k == 4 && sizes[0] == 1);                    /* 'S' counts as its own region */
    prefix2d_build(4, 4, cell_hash);
    CHECK(rect_sum(0, 0, 3, 3) == 5 && rect_sum(0, 3, 1, 3) == 2 && rect_sum(1, 1, 2, 1) == 2);
    rotate90(grid_g, 4, 4, grid_r);
    CHECK(grid_r[0][3] == 'S' && grid_r[3][3] == '#');
    CHECK(floor_div(-7, 2) == -4 && floor_div(7, 2) == 3 && ceil_div(-7, 2) == -3 && ceil_div(7, 2) == 4 && floor_div(7, -2) == -4 && ceil_div(6, 3) == 2);
    CHECK(ipow(3, 5) == 243 && ipow(2, 62) == 4611686018427387904LL && ipow(7, 0) == 1);
    int a[100], seen[100] = {0};
    for (int i = 0; i < 100; i++) a[i] = i;
    shuffle_int(a, 100);
    int ok = 1;
    for (int i = 0; i < 100; i++) { ok &= !seen[a[i]]; seen[a[i]] = 1; }
    CHECK(ok && elapsed_sec() >= 0);
}

int main(void) {
    test_numtheory();
    test_combin();
    test_matrix();
    test_fft();
    test_sort_search();
    test_search_answer();
    test_bits();
    test_linear_heap();
    test_dsu();
    test_fenwick_segtree();
    test_hash_trie();
    test_graph();
    test_flow();
    test_tree();
    test_strings();
    test_geom();
    test_dp();
    test_game();
    test_bignum();
    test_grid_util();
    printf("%d checks, %d failed\n", checks, fails);
    return fails != 0;
}
