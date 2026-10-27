/* linear.h - deque (also a queue) and monotonic stack / queue applications.
 *
 *   dq_clear dq_push_back dq_push_front dq_pop_front dq_pop_back dq_front dq_back dq_empty
 *   next_greater prev_smaller sliding_max max_histogram
 *
 * A stack needs no structure in C: int st[N], top = 0; push st[top++] = x;
 * pop x = st[--top]; peek st[top - 1]; empty top == 0.
 * Mirror tricks: prev_greater = next_greater on the reversed array,
 * sliding minimum = sliding_max of the negated values.
 * Deque is big: declare it static or global, never as a local variable.
 */
#ifndef XT_LINEAR_H
#define XT_LINEAR_H
#include "common.h"

#ifndef LIN_MAX
#define LIN_MAX 1000005
#endif

/* ---------- circular deque; a queue = push_back + pop_front ---------- */
typedef struct { int a[LIN_MAX]; int head, size; } Deque;

static inline void dq_clear(Deque *d) { d->head = d->size = 0; }
static inline int dq_empty(const Deque *d) { return d->size == 0; }
static inline void dq_push_back(Deque *d, int x) { d->a[(d->head + d->size++) % LIN_MAX] = x; }
static inline void dq_push_front(Deque *d, int x) {
    d->head = (d->head + LIN_MAX - 1) % LIN_MAX;
    d->a[d->head] = x;
    d->size++;
}
static inline int dq_pop_front(Deque *d) {
    int x = d->a[d->head];
    d->head = (d->head + 1) % LIN_MAX;
    d->size--;
    return x;
}
static inline int dq_pop_back(Deque *d) { d->size--; return d->a[(d->head + d->size) % LIN_MAX]; }
static inline int dq_front(const Deque *d) { return d->a[d->head]; }
static inline int dq_back(const Deque *d) { return d->a[(d->head + d->size - 1) % LIN_MAX]; }

/* ---------- monotonic stack. O(n) ---------- */
static int lin_st[LIN_MAX];

/* res[i] = smallest j > i with a[j] > a[i], or n */
static inline void next_greater(const int *a, int n, int *res) {
    int top = 0;
    for (int i = n - 1; i >= 0; i--) {
        while (top && a[lin_st[top - 1]] <= a[i]) top--; /* they are hidden by a[i] */
        res[i] = top ? lin_st[top - 1] : n;
        lin_st[top++] = i;
    }
}

/* res[i] = largest j < i with a[j] < a[i], or -1 */
static inline void prev_smaller(const int *a, int n, int *res) {
    int top = 0;
    for (int i = 0; i < n; i++) {
        while (top && a[lin_st[top - 1]] >= a[i]) top--;
        res[i] = top ? lin_st[top - 1] : -1;
        lin_st[top++] = i;
    }
}

/* ---------- monotonic deque: out[i] = max of a[i .. i+k-1], i = 0..n-k. O(n) ---------- */
static inline void sliding_max(const int *a, int n, int k, int *out) {
    int h = 0, t = 0; /* lin_st[h..t-1]: indices with decreasing values */
    for (int i = 0; i < n; i++) {
        while (t > h && a[lin_st[t - 1]] <= a[i]) t--;
        lin_st[t++] = i;
        if (lin_st[h] <= i - k) h++; /* front left the window */
        if (i >= k - 1) out[i - k + 1] = a[lin_st[h]];
    }
}

/* largest rectangle under a histogram of non-negative heights h[0..n-1]. O(n) */
static inline ll max_histogram(const int *h, int n) {
    int top = 0;
    ll best = 0;
    for (int i = 0; i <= n; i++) {
        int cur = (i == n) ? 0 : h[i];
        while (top && h[lin_st[top - 1]] >= cur) {
            ll height = h[lin_st[--top]];
            int left = top ? lin_st[top - 1] + 1 : 0; /* bar extends over [left, i) */
            if (height * (i - left) > best) best = height * (i - left);
        }
        lin_st[top++] = i;
    }
    return best;
}

#endif
