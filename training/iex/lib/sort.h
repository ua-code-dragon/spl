/* sort.h - sorting helpers around the standard qsort.
 *
 *   cmp_int cmp_ll cmp_dbl cmp_str | sort_int sort_ll unique_int compress
 *   count_inversions | kth_smallest
 *
 * Sorting structures with a custom comparator: see docs/en/handbook.md, section 3.
 * Never return x - y from a comparator: it overflows for large values.
 */
#ifndef XT_SORT_H
#define XT_SORT_H
#include "common.h"

#ifndef SORT_MAX
#define SORT_MAX 1000005
#endif

static inline int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}
static inline int cmp_ll(const void *a, const void *b) {
    ll x = *(const ll *)a, y = *(const ll *)b;
    return (x > y) - (x < y);
}
static inline int cmp_dbl(const void *a, const void *b) {
    double x = *(const double *)a, y = *(const double *)b;
    return (x > y) - (x < y);
}
/* for an array of char* (e.g. char *words[]) */
static inline int cmp_str(const void *a, const void *b) {
    return strcmp(*(char *const *)a, *(char *const *)b);
}

static inline void sort_int(int *a, int n) { qsort(a, (size_t)n, sizeof(int), cmp_int); }
static inline void sort_ll(ll *a, int n) { qsort(a, (size_t)n, sizeof(ll), cmp_ll); }

/* remove adjacent duplicates of a sorted array, returns the new length */
static inline int unique_int(int *a, int n) {
    int m = 0;
    for (int i = 0; i < n; i++)
        if (m == 0 || a[m - 1] != a[i]) a[m++] = a[i];
    return m;
}

/* coordinate compression: replaces a[i] by its rank 0..m-1 among the distinct
 * values; vals[0..m-1] receives the sorted distinct values. Returns m. O(n log n) */
static inline int compress(int *a, int n, int *vals) {
    memcpy(vals, a, sizeof(int) * (size_t)n);
    sort_int(vals, n);
    int m = unique_int(vals, n);
    for (int i = 0; i < n; i++) {
        int lo = 0, hi = m - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (vals[mid] < a[i]) lo = mid + 1; else hi = mid;
        }
        a[i] = lo;
    }
    return m;
}

/* number of pairs i < j with a[i] > a[j], by merge sort; a gets sorted. O(n log n) */
static inline ll count_inversions(int *a, int n) {
    static int tmp[SORT_MAX];
    ll inv = 0;
    for (int w = 1; w < n; w *= 2) { /* bottom-up merge sort */
        for (int lo = 0; lo + w < n; lo += 2 * w) {
            int mid = lo + w, hi = MIN(lo + 2 * w, n);
            int i = lo, j = mid, k = lo;
            while (i < mid && j < hi) {
                if (a[i] <= a[j]) tmp[k++] = a[i++];
                else { tmp[k++] = a[j++]; inv += mid - i; }
            }
            while (i < mid) tmp[k++] = a[i++];
            while (j < hi) tmp[k++] = a[j++];
            memcpy(a + lo, tmp + lo, sizeof(int) * (size_t)(hi - lo));
        }
    }
    return inv;
}

/* k-th smallest (k is 0-based) in average O(n) by quickselect; reorders a */
static inline int kth_smallest(int *a, int n, int k) {
    int lo = 0, hi = n - 1;
    while (lo < hi) {
        int pivot = a[lo + (hi - lo) / 2], i = lo, j = hi;
        while (i <= j) {
            while (a[i] < pivot) i++;
            while (a[j] > pivot) j--;
            if (i <= j) { SWAP(int, a[i], a[j]); i++; j--; }
        }
        if (k <= j) hi = j;
        else if (k >= i) lo = i;
        else break;
    }
    return a[k];
}

#endif
