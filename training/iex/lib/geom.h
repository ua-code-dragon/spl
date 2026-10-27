/* geom.h - 2D computational geometry.
 *
 * Integer points (exact):   cross3 dot3 dist2 on_segment seg_intersect
 *                           polygon_area2 convex_hull in_polygon
 *                           lattice_boundary lattice_interior (Pick)
 * Real points:              dist_pt_seg line_intersect
 *
 * Prefer integers: coordinates up to 1e9 keep cross products inside long long.
 * With doubles compare using an epsilon: fabs(a - b) < 1e-9.
 */
#ifndef XT_GEOM_H
#define XT_GEOM_H
#include "common.h"
#include <math.h>

typedef struct { ll x, y; } Pt;

/* (a - o) x (b - o): > 0 if o -> a -> b turns left (counter-clockwise),
 * < 0 if it turns right, 0 if collinear. Twice the signed triangle area. */
static inline ll cross3(Pt o, Pt a, Pt b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

static inline ll dot3(Pt o, Pt a, Pt b) {
    return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}

static inline ll dist2(Pt a, Pt b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }

static inline int sgn(ll x) { return (x > 0) - (x < 0); }

/* is p on the closed segment ab? */
static inline int on_segment(Pt a, Pt b, Pt p) {
    return cross3(a, b, p) == 0 && MIN(a.x, b.x) <= p.x && p.x <= MAX(a.x, b.x)
        && MIN(a.y, b.y) <= p.y && p.y <= MAX(a.y, b.y);
}

/* do closed segments ab and cd have a common point? */
static inline int seg_intersect(Pt a, Pt b, Pt c, Pt d) {
    int d1 = sgn(cross3(a, b, c)), d2 = sgn(cross3(a, b, d));
    int d3 = sgn(cross3(c, d, a)), d4 = sgn(cross3(c, d, b));
    if (d1 * d2 < 0 && d3 * d4 < 0) return 1; /* proper crossing */
    return on_segment(a, b, c) || on_segment(a, b, d) || on_segment(c, d, a) || on_segment(c, d, b);
}

/* twice the signed area (shoelace formula): > 0 for counter-clockwise order */
static inline ll polygon_area2(const Pt *p, int n) {
    ll s = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        s += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return s;
}

static inline int pt_cmp_(const void *a, const void *b) {
    const Pt *p = a, *q = b;
    if (p->x != q->x) return (p->x > q->x) - (p->x < q->x);
    return (p->y > q->y) - (p->y < q->y);
}

/* convex hull (Andrew's monotone chain): sorts p[], writes the hull to h[]
 * counter-clockwise without collinear points, returns its size. h needs n+1 slots. O(n log n) */
static inline int convex_hull(Pt *p, int n, Pt *h) {
    if (n == 1) { h[0] = p[0]; return 1; }
    qsort(p, (size_t)n, sizeof(Pt), pt_cmp_);
    int k = 0;
    for (int i = 0; i < n; i++) { /* lower hull */
        while (k >= 2 && cross3(h[k - 2], h[k - 1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) { /* upper hull */
        while (k >= t && cross3(h[k - 2], h[k - 1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    return k - 1; /* last point repeats the first */
}

/* point in (any simple) polygon: 2 = on the boundary, 1 = inside, 0 = outside. O(n) */
static inline int in_polygon(const Pt *poly, int n, Pt q) {
    int inside = 0;
    for (int i = 0; i < n; i++) {
        Pt a = poly[i], b = poly[(i + 1) % n];
        if (on_segment(a, b, q)) return 2;
        if ((a.y > q.y) != (b.y > q.y)) { /* edge crosses the line y = q.y */
            ll c = cross3(a, b, q);
            if ((c > 0) == (b.y > a.y)) inside ^= 1; /* ... to the right of q */
        }
    }
    return inside;
}

static inline ll geom_gcd_(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) { ll t = a % b; a = b; b = t; }
    return a;
}

/* lattice points on the boundary of a polygon with integer vertices */
static inline ll lattice_boundary(const Pt *p, int n) {
    ll b = 0;
    for (int i = 0; i < n; i++) b += geom_gcd_(p[(i + 1) % n].x - p[i].x, p[(i + 1) % n].y - p[i].y);
    return b;
}

/* lattice points strictly inside, by Pick's theorem: A = I + B/2 - 1 */
static inline ll lattice_interior(const Pt *p, int n) {
    ll a2 = polygon_area2(p, n);
    if (a2 < 0) a2 = -a2;
    return (a2 - lattice_boundary(p, n) + 2) / 2;
}

/* ---------- real-valued helpers ---------- */
typedef struct { double x, y; } Pd;

/* distance from p to the segment ab */
static inline double dist_pt_seg(Pd p, Pd a, Pd b) {
    double dx = b.x - a.x, dy = b.y - a.y, len2 = dx * dx + dy * dy;
    double t = len2 > 0 ? ((p.x - a.x) * dx + (p.y - a.y) * dy) / len2 : 0;
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    return hypot(p.x - (a.x + t * dx), p.y - (a.y + t * dy));
}

/* intersection of the infinite lines ab and cd; returns 0 if parallel */
static inline int line_intersect(Pd a, Pd b, Pd c, Pd d, Pd *out) {
    double d1x = b.x - a.x, d1y = b.y - a.y, d2x = d.x - c.x, d2y = d.y - c.y;
    double den = d1x * d2y - d1y * d2x;
    if (fabs(den) < 1e-12) return 0;
    double t = ((c.x - a.x) * d2y - (c.y - a.y) * d2x) / den;
    out->x = a.x + t * d1x;
    out->y = a.y + t * d1y;
    return 1;
}

#endif
