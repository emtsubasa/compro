#include <bits/stdc++.h>
using namespace std;

long long h, w;
vector<vector<long long>> a, dp[2];

long long solve();

int main() {
  cin >> h >> w;
  a.assign(h, vector<long long>(w, -1));
  dp[0].assign(h + 1, vector<long long>(w + 1, -1));
  dp[1].assign(h + 1, vector<long long>(w + 1, -1));
  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j) cin >> a[i][j];
  cout << solve() << endl;
  return 0;
}

long long solve() {
  dp[0][0][0] = dp[1][0][0] = a[0][0];
  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j) {
      if (dp[0][i][j] != -1) {
        long long x = i, y = j, now = dp[0][i][j];
        for (int k = 0; k < 2; ++k) {
          if (++x >= h) break;
          now += a[x][y];
          dp[1][x][y] = max(dp[1][x][y], now);
        }
      }
      if (dp[1][i][j] != -1) {
        long long x = i, y = j, now = dp[1][i][j];
        for (int k = 0; k < 2; ++k) {
          if (++y >= w) break;
          now += a[x][y];
          dp[0][x][y] = max(dp[0][x][y], now);
        }
      }
    }
  return max(dp[0][h - 1][w - 1], dp[1][h - 1][w - 1]);
}