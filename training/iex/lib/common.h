/* common.h - shared typedefs, macros and constants. Every other header includes it.
 *
 * Conventions used by the whole library:
 *  - plain C11, no dynamic allocation: arrays are static, their size is a
 *    macro you can override BEFORE the #include (e.g. #define GV_MAX 1000005);
 *  - functions are "static inline" so a header can be included without
 *    linking anything and unused ones do not trigger warnings;
 *  - arrays are 0-indexed unless a comment says otherwise;
 *  - macros evaluate their arguments more than once: MIN(i++, j) is a bug.
 */
#ifndef XT_COMMON_H
#define XT_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef long long ll;
typedef unsigned long long ull;

#define MIN(a, b)     ((a) < (b) ? (a) : (b))
#define MAX(a, b)     ((a) > (b) ? (a) : (b))
#define ABS(a)        ((a) < 0 ? -(a) : (a))
#define SWAP(T, a, b) do { T _t = (a); (a) = (b); (b) = _t; } while (0)
#define REP(i, n)     for (int i = 0; i < (n); i++)
#define FOR(i, a, b)  for (int i = (a); i < (b); i++)
#define LEN(a)        ((int)(sizeof(a) / sizeof((a)[0])))

#define INF   1000000000 /* "infinity" for int values  */
#define LINF  4000000000000000000LL /* "infinity" for ll values   */
#define MOD   1000000007LL /* the usual prime modulus    */
#define MOD2  998244353LL /* NTT-friendly prime modulus */

#endif
