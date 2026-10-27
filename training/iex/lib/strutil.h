/* strutil.h - string algorithms.
 *
 *   prefix_function kmp_search z_function     pattern matching, periods
 *   hash_build hash_sub                        O(1) substring comparison
 *   manacher longest_palindrome                palindromes
 *   suffix_array lcp_array                     sorted suffixes
 *   str_reverse
 *
 * Strings are char arrays of length n (no need for '\0' unless stated).
 */
#ifndef XT_STRUTIL_H
#define XT_STRUTIL_H
#include "common.h"

#ifndef STR_MAX
#define STR_MAX 1000005
#endif

static inline void str_reverse(char *s, int n) {
    for (int i = 0, j = n - 1; i < j; i++, j--) SWAP(char, s[i], s[j]);
}

/* ---------- KMP ----------
 * pi[i] = length of the longest proper prefix of s[0..i] that is also its suffix.
 * Smallest period of s = n - pi[n-1]. O(n) */
static inline void prefix_function(const char *s, int n, int *pi) {
    pi[0] = 0;
    for (int i = 1; i < n; i++) {
        int k = pi[i - 1];
        while (k > 0 && s[i] != s[k]) k = pi[k - 1];
        if (s[i] == s[k]) k++;
        pi[i] = k;
    }
}

/* start positions of all occurrences of pat (length m) in text (length n)
 * are written to pos (may be NULL); returns their count. O(n + m) */
static inline int kmp_search(const char *text, int n, const char *pat, int m, int *pos) {
    static int pi[STR_MAX];
    int cnt = 0, k = 0;
    if (m == 0) return 0;
    prefix_function(pat, m, pi);
    for (int i = 0; i < n; i++) {
        while (k > 0 && text[i] != pat[k]) k = pi[k - 1];
        if (text[i] == pat[k]) k++;
        if (k == m) {
            if (pos) pos[cnt] = i - m + 1;
            cnt++;
            k = pi[k - 1];
        }
    }
    return cnt;
}

/* z[i] = length of the longest common prefix of s and s[i..]; z[0] = n. O(n)
 * Matching: z-function of pat + '#' + text, occurrences where z == m. */
static inline void z_function(const char *s, int n, int *z) {
    int l = 0, r = 0;
    z[0] = n;
    for (int i = 1; i < n; i++) {
        z[i] = (i < r) ? MIN(r - i, z[i - l]) : 0;
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
}

/* ---------- polynomial rolling hash modulo 2^61 - 1 ----------
 * hash_build(s, n) once, then hash_sub(l, len) is the hash of s[l .. l+len-1].
 * Equal substrings -> equal hashes; different -> equal with probability ~1e-18.
 * To compare two different strings hash their concatenation. */
#define HS_MOD ((1ULL << 61) - 1)
#define HS_BASE 1000003ULL
static ull hs_pre[STR_MAX], hs_pow[STR_MAX];

static inline ull hs_mul(ull a, ull b) {
    unsigned __int128 c = (unsigned __int128)a * b;
    ull x = (ull)(c & HS_MOD) + (ull)(c >> 61);
    while (x >= HS_MOD) x -= HS_MOD;
    return x;
}

static inline void hash_build(const char *s, int n) {
    hs_pre[0] = 0; hs_pow[0] = 1;
    for (int i = 0; i < n; i++) {
        hs_pre[i + 1] = (hs_mul(hs_pre[i], HS_BASE) + (unsigned char)s[i]) % HS_MOD;
        hs_pow[i + 1] = hs_mul(hs_pow[i], HS_BASE);
    }
}

static inline ull hash_sub(int l, int len) {
    return (hs_pre[l + len] + HS_MOD - hs_mul(hs_pre[l], hs_pow[len])) % HS_MOD;
}

/* ---------- Manacher ----------
 * d1[i]: odd palindromes centred at i; the longest is s[i-d1[i]+1 .. i+d1[i]-1].
 * d2[i]: even palindromes centred between i-1 and i; the longest is s[i-d2[i] .. i+d2[i]-1].
 * Number of palindromic substrings = sum d1 + sum d2. O(n) */
static inline void manacher(const char *s, int n, int *d1, int *d2) {
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : MIN(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) { l = i - k; r = i + k; }
    }
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : MIN(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) { l = i - k - 1; r = i + k; }
    }
}

/* length of the longest palindromic substring, its start in *start */
static inline int longest_palindrome(const char *s, int n, int *start) {
    static int d1[STR_MAX], d2[STR_MAX];
    int best = 0;
    *start = 0;
    manacher(s, n, d1, d2);
    for (int i = 0; i < n; i++) {
        if (2 * d1[i] - 1 > best) { best = 2 * d1[i] - 1; *start = i - d1[i] + 1; }
        if (2 * d2[i] > best) { best = 2 * d2[i]; *start = i - d2[i]; }
    }
    return best;
}

/* ---------- suffix array (prefix doubling + qsort, O(n log^2 n)) ----------
 * sa[i] = start of the i-th smallest suffix. Fine for n up to ~2e5. */
static int sa_rank[STR_MAX], sa_tmp[STR_MAX], sa_k, sa_n;

static inline int sa_cmp_(const void *a, const void *b) {
    int i = *(const int *)a, j = *(const int *)b;
    if (sa_rank[i] != sa_rank[j]) return sa_rank[i] - sa_rank[j];
    int ri = i + sa_k < sa_n ? sa_rank[i + sa_k] : -1;
    int rj = j + sa_k < sa_n ? sa_rank[j + sa_k] : -1;
    return ri - rj;
}

static inline void suffix_array(const char *s, int n, int *sa) {
    sa_n = n;
    for (int i = 0; i < n; i++) { sa[i] = i; sa_rank[i] = (unsigned char)s[i]; }
    for (sa_k = 1;; sa_k *= 2) {
        qsort(sa, (size_t)n, sizeof(int), sa_cmp_); /* sort by (rank[i], rank[i+k]) */
        sa_tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            sa_tmp[sa[i]] = sa_tmp[sa[i - 1]] + (sa_cmp_(&sa[i - 1], &sa[i]) < 0);
        memcpy(sa_rank, sa_tmp, sizeof(int) * (size_t)n);
        if (sa_rank[sa[n - 1]] == n - 1 || sa_k > n) break;
    }
}

/* lcp[i] = common prefix length of suffixes sa[i] and sa[i+1] (Kasai, O(n)).
 * Distinct substrings = n(n+1)/2 - sum of lcp. */
static inline void lcp_array(const char *s, int n, const int *sa, int *lcp) {
    int k = 0;
    for (int i = 0; i < n; i++) sa_rank[sa[i]] = i;
    for (int i = 0; i < n; i++) {
        if (sa_rank[i] == n - 1) { k = 0; continue; }
        int j = sa[sa_rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[sa_rank[i]] = k;
        if (k) k--;
    }
}

#endif
