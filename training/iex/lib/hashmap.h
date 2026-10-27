/* hashmap.h - hash tables with static memory (open addressing, linear probing).
 *
 *   hm_set hm_get hm_add hm_clear       map: long long -> long long
 *   sm_id sm_get sm_str                        dictionary: string -> id 0,1,2,...
 *
 * Expected O(1) per operation. There is no delete: rebuild or hm_clear().
 * Iterate the map: for (i = 0; i < HM_CAP; i++) if (hm_gen[i] == hm_cur) use hm_key[i], hm_val[i].
 */
#ifndef XT_HASHMAP_H
#define XT_HASHMAP_H
#include "common.h"

#ifndef HM_CAP
#define HM_CAP (1 << 21) /* power of two, at least 2x the number of keys */
#endif

static ll hm_key[HM_CAP], hm_val[HM_CAP];
static int hm_gen[HM_CAP]; /* slot is used iff hm_gen[i] == hm_cur */
static int hm_cur = 1, hm_size;

/* splitmix64 scrambler: neighbouring keys land far apart */
static inline ull hm_hash(ull x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

/* slot of key k; inserted with value 0 if absent */
static inline int hm_slot(ll k) {
    ull i = hm_hash((ull)k) & (HM_CAP - 1);
    while (hm_gen[i] == hm_cur && hm_key[i] != k) i = (i + 1) & (HM_CAP - 1);
    if (hm_gen[i] != hm_cur) {
        hm_gen[i] = hm_cur; hm_key[i] = k; hm_val[i] = 0; hm_size++;
    }
    return (int)i;
}

static inline ll hm_get(ll k, ll def) {
    ull i = hm_hash((ull)k) & (HM_CAP - 1);
    while (hm_gen[i] == hm_cur) {
        if (hm_key[i] == k) return hm_val[i];
        i = (i + 1) & (HM_CAP - 1);
    }
    return def;
}

static inline void hm_set(ll k, ll v) { hm_val[hm_slot(k)] = v; }
static inline void hm_add(ll k, ll d) { hm_val[hm_slot(k)] += d; } /* counting */
static inline void hm_clear(void) { hm_cur++; hm_size = 0; } /* O(1) */

/* ---------- string dictionary: assigns ids 0, 1, 2, ... to distinct strings ---------- */
#ifndef SM_CAP
#define SM_CAP (1 << 20) /* power of two, at least 2x the number of strings */
#endif
#ifndef SM_POOL
#define SM_POOL (1 << 24) /* total characters of all distinct strings */
#endif

static int sm_slot_id[SM_CAP]; /* id + 1, 0 = empty */
static int sm_off[SM_CAP / 2]; /* id -> offset of the string in sm_pool */
static char sm_pool[SM_POOL];
static int sm_used, sm_count; /* sm_count = number of distinct strings */

static inline const char *sm_str(int id) { return sm_pool + sm_off[id]; }

static inline int sm_find_(const char *s, int insert) {
    ull h = 1469598103934665603ULL; /* FNV-1a */
    for (const char *p = s; *p; p++) h = (h ^ (unsigned char)*p) * 1099511628211ULL;
    ull i = hm_hash(h) & (SM_CAP - 1);
    while (sm_slot_id[i]) {
        int id = sm_slot_id[i] - 1;
        if (strcmp(sm_str(id), s) == 0) return id;
        i = (i + 1) & (SM_CAP - 1);
    }
    if (!insert) return -1;
    size_t len = strlen(s) + 1;
    memcpy(sm_pool + sm_used, s, len);
    sm_off[sm_count] = sm_used;
    sm_used += (int)len;
    sm_slot_id[i] = sm_count + 1;
    return sm_count++;
}

static inline int sm_id(const char *s) { return sm_find_(s, 1); } /* insert if new */
static inline int sm_get(const char *s) { return sm_find_(s, 0); } /* -1 if absent  */

#endif
