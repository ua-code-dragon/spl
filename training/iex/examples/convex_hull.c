/* Fence around trees: convex hull, its perimeter and area.
 *
 * Input:  n, then n integer points "x y".
 * Output: number of hull vertices, perimeter (2 decimals), area (1 decimal).
 * Idea:   sort the points, build the lower and upper chains keeping only left
 *         turns (cross product > 0). Area by the shoelace formula. O(n log n)
 */
#include "geom.h"

static Pt p[200005], h[200006];

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) scanf("%lld %lld", &p[i].x, &p[i].y);
    int k = convex_hull(p, n, h);
    double per = 0;
    for (int i = 0; i < k; i++) per += sqrt((double)dist2(h[i], h[(i + 1) % k]));
    printf("%d\n%.2f\n%.1f\n", k, per, polygon_area2(h, k) / 2.0);
    return 0;
}
