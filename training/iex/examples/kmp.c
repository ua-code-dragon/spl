/* Pattern search (Knuth-Morris-Pratt) and the period of a string.
 *
 * Input:  a text line and a pattern line (no spaces inside, up to 10^6 chars).
 * Output: number of occurrences, their 1-based positions, and the length of
 *         the shortest period of the pattern (abcabcab -> 3).
 * Idea:   the prefix function lets the scan continue after a mismatch without
 *         moving back in the text. O(|text| + |pattern|)
 */
#include "strutil.h"

static char text[STR_MAX], pat[STR_MAX];
static int pos[STR_MAX], pi[STR_MAX];

int main(void) {
    if (scanf("%s %s", text, pat) != 2) return 0;
    int n = (int)strlen(text), m = (int)strlen(pat);
    int cnt = kmp_search(text, n, pat, m, pos);
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; i++) printf("%d%c", pos[i] + 1, i + 1 < cnt ? ' ' : '\n');
    prefix_function(pat, m, pi);
    printf("%d\n", m - pi[m - 1]);
    return 0;
}
