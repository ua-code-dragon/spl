/* interactive.h - talking to an interactive judge.
 *
 * The judge reads your output while you run. Output is buffered, so without
 * fflush the judge never sees the query and both programs wait forever
 * ("Idleness limit exceeded" / TLE). Rules:
 *   - flush after every line you print (ASK does it);
 *   - read the answer with scanf (not io.h, which buffers ahead);
 *   - stop at once if the judge answers -1 (wrong query) or input ends.
 */
#ifndef XT_INTERACTIVE_H
#define XT_INTERACTIVE_H
#include "common.h"

#define ASK(...) do { printf(__VA_ARGS__); fflush(stdout); } while (0)

/* read one integer reply; exits quietly on end of input or a -1 verdict */
static inline int reply_int(void) {
    int x;
    if (scanf("%d", &x) != 1 || x == -1) exit(0);
    return x;
}

#endif
