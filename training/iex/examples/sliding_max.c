/* Maximum of every window of k consecutive values (monotonic deque).
 *
 * Input:  n k, then n integers.
 * Output: the n-k+1 window maxima.
 * Idea:   keep indices whose values decrease from front to back; a new value
 *         removes smaller ones from the back (they can never be a maximum
 *         again), the front leaves when it slides out of the window. O(n)
 */
#include "io.h"
#include "linear.h"

static int a[LIN_MAX], out[LIN_MAX];

int main(void) {
    int n = read_int(), k = read_int();
    for (int i = 0; i < n; i++) a[i] = read_int();
    sliding_max(a, n, k, out);
    for (int i = 0; i + k <= n; i++) printf("%d%c", out[i], i + k < n ? ' ' : '\n');
    return 0;
}
