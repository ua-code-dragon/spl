/* heap.h - binary min-heap (priority queue) of (key, id) pairs.
 *
 *   heap_push heap_pop heap_top heap_empty heap_clear
 *
 * Max-heap: push -key and negate when popping.
 * Each push/pop is O(log n). Declare heaps static: static Heap pq;
 */
#ifndef XT_HEAP_H
#define XT_HEAP_H
#include "common.h"

#ifndef HEAP_MAX
#define HEAP_MAX (1 << 20)
#endif

typedef struct { ll key; int id; } HeapItem;
typedef struct { HeapItem a[HEAP_MAX]; int n; } Heap;

static inline void heap_clear(Heap *h) { h->n = 0; }
static inline int heap_empty(const Heap *h) { return h->n == 0; }
static inline HeapItem heap_top(const Heap *h) { return h->a[0]; }

static inline void heap_push(Heap *h, ll key, int id) {
    int i = h->n++;
    while (i > 0) { /* sift up: move bigger parents down */
        int p = (i - 1) / 2;
        if (h->a[p].key <= key) break;
        h->a[i] = h->a[p];
        i = p;
    }
    h->a[i].key = key;
    h->a[i].id = id;
}

/* remove and return the item with the smallest key (heap must be non-empty) */
static inline HeapItem heap_pop(Heap *h) {
    HeapItem top = h->a[0], last = h->a[--h->n];
    int i = 0;
    for (;;) { /* sift down: move smaller children up */
        int c = 2 * i + 1;
        if (c >= h->n) break;
        if (c + 1 < h->n && h->a[c + 1].key < h->a[c].key) c++;
        if (h->a[c].key >= last.key) break;
        h->a[i] = h->a[c];
        i = c;
    }
    h->a[i] = last;
    return top;
}

#endif
