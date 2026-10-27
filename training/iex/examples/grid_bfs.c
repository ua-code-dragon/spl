/* Maze: shortest path on a grid (BFS).
 *
 * Input:  R C, then R rows of C characters: '#' wall, '.' free, 'S' start, 'E' exit.
 * Output: minimum number of 4-directional steps from S to E, or -1.
 * Idea:   every step costs 1, so BFS visits cells in order of distance.  O(R*C)
 */
#include "grid.h"

static char g[GRID_MAX][GRID_MAX];

int main(void) {
    int R, C, sr = 0, sc = 0, er = 0, ec = 0;
    if (scanf("%d %d", &R, &C) != 2) return 0;
    for (int r = 0; r < R; r++) {
        scanf("%s", g[r]);
        for (int c = 0; c < C; c++) {
            if (g[r][c] == 'S') { sr = r; sc = c; }
            if (g[r][c] == 'E') { er = r; ec = c; }
        }
    }
    grid_bfs(g, R, C, sr, sc, '#');
    printf("%d\n", grid_dist[er][ec]);
    return 0;
}
