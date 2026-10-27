/* Local judge for guess.c:  ./judge_guess N X  (talks to the solution via pipes).
 * Prints OK / WRONG on stderr. Not a solution, a testing tool. */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 3) return 2;
    long long n = atoll(argv[1]), x = atoll(argv[2]), y;
    char c;
    int asked = 0;
    printf("%lld\n", n);
    fflush(stdout);
    while (scanf(" %c %lld", &c, &y) == 2) {
        if (c == '!') {
            int ok = (y == x && asked <= 60);
            fprintf(stderr, "%s after %d questions\n", ok ? "OK" : "WRONG", asked);
            return !ok;
        }
        asked++;
        printf("%d\n", x >= y);
        fflush(stdout);
    }
    fprintf(stderr, "WRONG: no answer\n");
    return 1;
}
