/* Interactive: find a hidden number with yes/no questions.
 *
 * Protocol: the judge prints N. The secret X is in [1, N]. Ask "? y" and the
 *           judge answers 1 if X >= y, otherwise 0. Finish with "! X".
 *           At most 60 questions.
 * Idea:     binary search on the answer; flush after every line, read the
 *           reply with scanf. (Test locally with judge_guess.c, see tests/run_examples.sh.)
 */
#include "interactive.h"

int main(void) {
    ll n, lo = 1, hi;
    if (scanf("%lld", &n) != 1) return 0;
    hi = n;
    while (lo < hi) {                       /* X is in [lo, hi] */
        ll mid = lo + (hi - lo + 1) / 2;
        ASK("? %lld\n", mid);
        if (reply_int()) lo = mid; else hi = mid - 1;
    }
    ASK("! %lld\n", lo);
    return 0;
}
