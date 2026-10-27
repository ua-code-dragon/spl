/* Data processing in the style of the IEEE Xplore tasks: one JSON object per line.
 *
 * Input:  lines like {"title": "Some paper", "year": 2019, "citations": 12}
 *         (fields in any order, other fields may appear).
 * Output: for every year (ascending): "year papers total_citations".
 * Idea:   no JSON library in C, but a small field extractor is enough:
 *         find "key", skip to ':', read a number or a quoted string.
 */
#include "sort.h"

/* copy the value of "key" in line into out (without quotes); 0 if missing */
static int json_get(const char *line, const char *key, char *out, int cap) {
    char pattern[100];
    snprintf(pattern, sizeof pattern, "\"%s\"", key);
    const char *p = strstr(line, pattern);
    if (!p) return 0;
    p = strchr(p + strlen(pattern), ':');
    if (!p) return 0;
    p++;
    while (*p == ' ') p++;
    int n = 0;
    if (*p == '"') {                                   /* string value */
        for (p++; *p && *p != '"' && n < cap - 1; p++) {
            if (*p == '\\' && p[1]) p++;               /* keep escaped character */
            out[n++] = *p;
        }
    } else {                                           /* number / true / false / null */
        while (*p && *p != ',' && *p != '}' && *p != ' ' && n < cap - 1) out[n++] = *p++;
    }
    out[n] = 0;
    return 1;
}

static int years[3000];
static ll papers[3000], cites[3000];

int main(void) {
    static char line[1 << 16];
    char val[256];
    while (fgets(line, sizeof line, stdin)) {
        if (!json_get(line, "year", val, sizeof val)) continue;
        int y = atoi(val);
        if (y < 0 || y >= 3000) continue;
        papers[y]++;
        if (json_get(line, "citations", val, sizeof val)) cites[y] += atoll(val);
    }
    int k = 0;
    for (int y = 0; y < 3000; y++) if (papers[y]) years[k++] = y;
    sort_int(years, k);                                /* already sorted, shown for the idiom */
    for (int i = 0; i < k; i++) printf("%d %lld %lld\n", years[i], papers[years[i]], cites[years[i]]);
    return 0;
}
