/* grid.h - helpers for problems on 2D boards (mazes, images, maps).
 *
 *   DR4 DC4 DR8 DC8 IN_GRID | grid_bfs grid_regions
 *   prefix2d_build rect_sum | rotate90
 *
 * Boards are char g[GRID_MAX][GRID_MAX] (declare them static), rows 0..R-1,
 * columns 0..C-1. A cell (r, c) is encoded in queues as r * GRID_MAX + c.
 */
#ifndef XT_GRID_H
#define XT_GRID_H
#include "common.h"

#ifndef GRID_MAX
#define GRID_MAX 1005
#endif

static const int DR4[4] = {-1, 0, 1, 0}, DC4[4] = {0, 1, 0, -1}; /* up right down left */
static const int DR8[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, DC8[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
#define IN_GRID(r, c, R, C) ((r) >= 0 && (r) < (R) && (c) >= 0 && (c) < (C))

static int grid_dist[GRID_MAX][GRID_MAX]; /* result of grid_bfs   */
static int grid_comp[GRID_MAX][GRID_MAX]; /* result of grid_regions */
static int grid_q[GRID_MAX * GRID_MAX];

/* 4-direction BFS from (sr, sc); cells equal to wall are blocked.
 * grid_dist[r][c] = number of steps, -1 if unreachable. O(R C) */
static inline void grid_bfs(char g[][GRID_MAX], int R, int C, int sr, int sc, char wall) {
    int h = 0, t = 0;
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) grid_dist[r][c] = -1;
    grid_dist[sr][sc] = 0;
    grid_q[t++] = sr * GRID_MAX + sc;
    while (h < t) {
        int r = grid_q[h] / GRID_MAX, c = grid_q[h] % GRID_MAX;
        h++;
        for (int d = 0; d < 4; d++) {
            int nr = r + DR4[d], nc = c + DC4[d];
            if (!IN_GRID(nr, nc, R, C) || g[nr][nc] == wall || grid_dist[nr][nc] >= 0) continue;
            grid_dist[nr][nc] = grid_dist[r][c] + 1;
            grid_q[t++] = nr * GRID_MAX + nc;
        }
    }
}

/* flood fill: 4-connected regions of equal characters, cells equal to skip
 * are ignored (grid_comp = -1). grid_comp[r][c] = region id, size[id] (if
 * size != NULL) = number of cells. Returns the number of regions. O(R C) */
static inline int grid_regions(char g[][GRID_MAX], int R, int C, char skip, int *size) {
    int k = 0;
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) grid_comp[r][c] = -1;
    for (int r0 = 0; r0 < R; r0++)
        for (int c0 = 0; c0 < C; c0++) {
            if (g[r0][c0] == skip || grid_comp[r0][c0] >= 0) continue;
            int h = 0, t = 0;
            grid_comp[r0][c0] = k;
            grid_q[t++] = r0 * GRID_MAX + c0;
            while (h < t) {
                int r = grid_q[h] / GRID_MAX, c = grid_q[h] % GRID_MAX;
                h++;
                for (int d = 0; d < 4; d++) {
                    int nr = r + DR4[d], nc = c + DC4[d];
                    if (!IN_GRID(nr, nc, R, C) || grid_comp[nr][nc] >= 0 || g[nr][nc] != g[r][c]) continue;
                    grid_comp[nr][nc] = k;
                    grid_q[t++] = nr * GRID_MAX + nc;
                }
            }
            if (size) size[k] = t;
            k++;
        }
    return k;
}

/* ---------- 2D prefix sums: O(1) sum of any rectangle ---------- */
static ll grid_ps[GRID_MAX + 1][GRID_MAX + 1]; /* grid_ps[r][c] = sum of rows < r, cols < c */

/* value(r, c) supplies the cell values, e.g. return g[r][c] == '#'; */
static inline void prefix2d_build(int R, int C, ll (*value)(int r, int c)) {
    for (int c = 0; c <= C; c++) grid_ps[0][c] = 0;
    for (int r = 1; r <= R; r++) {
        grid_ps[r][0] = 0;
        for (int c = 1; c <= C; c++)
            grid_ps[r][c] = value(r - 1, c - 1) + grid_ps[r - 1][c] + grid_ps[r][c - 1] - grid_ps[r - 1][c - 1];
    }
}

/* sum over rows r1..r2 and columns c1..c2 (inclusive, 0-based) */
static inline ll rect_sum(int r1, int c1, int r2, int c2) {
    return grid_ps[r2 + 1][c2 + 1] - grid_ps[r1][c2 + 1] - grid_ps[r2 + 1][c1] + grid_ps[r1][c1];
}

/* rotate an R x C board 90 degrees clockwise into dst (C x R) */
static inline void rotate90(char src[][GRID_MAX], int R, int C, char dst[][GRID_MAX]) {
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) dst[c][R - 1 - r] = src[r][c];
}

#endif
