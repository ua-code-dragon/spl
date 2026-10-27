/* Greedy: the largest number of non-overlapping talks in one room.
 *
 * Input:  n, then n lines "start end" (a talk occupies [start, end); a talk may
 *         start exactly when the previous one ends).
 * Output: the maximum number of talks that can be scheduled.
 * Idea:   always take the talk that ends first among those still possible.
 *         Exchange argument: any optimal schedule can swap its first talk for
 *         the earliest-ending one without losing anything. O(n log n)
 */
#include "common.h"

typedef struct { ll start, end; } Talk;

static int by_end(const void *a, const void *b) {
    const Talk *x = a, *y = b;
    if (x->end != y->end) return (x->end > y->end) - (x->end < y->end);
    return (x->start > y->start) - (x->start < y->start);
}

static Talk t[200005];

int main(void) {
    int n, count = 0;
    ll free_from = -LINF;                       /* the room is free from this time on */
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) scanf("%lld %lld", &t[i].start, &t[i].end);
    qsort(t, (size_t)n, sizeof(Talk), by_end);
    for (int i = 0; i < n; i++)
        if (t[i].start >= free_from) { count++; free_from = t[i].end; }
    printf("%d\n", count);
    return 0;
}
