#include <stdbool.h>
#include <stdio.h>
#define inf 1000000

int d[4] = {0, 1, 0, -1};
int n, m;
int x[512] = {}, y[512] = {}, dist[32][32] = {};
char c[4] = "RDLU";
char g[32][32];

bool isvalid(int nx, int ny) {
  return nx >= 0 && nx < n && ny >= 0 && ny < m && g[nx][ny] != '#';
}
int solve();

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%s", &g[i]);
    int res = solve();
    if (res == inf)
      printf("kusoge-\n");
    else
      printf("%d\n", res);
  }
  return 0;
}

int solve() {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) dist[i][j] = inf;
  dist[0][0] = 0;
  for (int id = 0, len = 1; id < len; ++id) {
    int nx = x[id], ny = y[id];
    int cos = dist[nx][ny];
    for (int j = 0; j < 4; ++j)
      if (g[nx][ny] == '.' || g[nx][ny] == c[j]) {
        int tx = nx + d[j], ty = ny + d[1 ^ j];
        if (!isvalid(tx, ty) || dist[tx][ty] <= cos + 1) continue;
        dist[tx][ty] = cos + 1;
        x[len] = tx;
        y[len++] = ty;
      }
  }
  return dist[n - 1][m - 1];
}