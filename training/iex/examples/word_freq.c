/* Text processing: the most frequent words.
 *
 * Input:  any text until end of file. A word is a maximal run of letters,
 *         compared case-insensitively.
 * Output: the 5 most frequent words as "word count", by count (descending),
 *         ties alphabetically.
 * Idea:   read character by character, give each distinct word an id with a
 *         hash table (sm_id), count per id, sort ids with a comparator.
 */
#include <ctype.h>
#include "hashmap.h"

static int cnt[SM_CAP / 2], order[SM_CAP / 2];

static int by_count(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    if (cnt[x] != cnt[y]) return cnt[y] - cnt[x];     /* bigger count first */
    return strcmp(sm_str(x), sm_str(y));              /* then alphabetically */
}

int main(void) {
    char word[1000];
    int len = 0, c;
    do {
        c = getchar();
        if (c != EOF && isalpha(c)) {
            if (len < 999) word[len++] = (char)tolower(c);
        } else if (len > 0) {
            word[len] = 0;
            cnt[sm_id(word)]++;
            len = 0;
        }
    } while (c != EOF);
    for (int i = 0; i < sm_count; i++) order[i] = i;
    qsort(order, (size_t)sm_count, sizeof(int), by_count);
    for (int i = 0; i < sm_count && i < 5; i++) printf("%s %d\n", sm_str(order[i]), cnt[order[i]]);
    return 0;
}
