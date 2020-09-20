#include <bits/stdc++.h>
using namespace std;

using P = pair<int, int>;

int n, p, k;
vector<P> v;
vector<vector<int>> dp;

int solve();

int main() {
  cin >> n >> p >> k;
  dp.assign(n + 1, vector<int>(p + 1, -1000000000));
  dp[0][0] = 0;
  v.resize(n);
  for (auto &p : v) cin >> p.first >> p.second;
  for (int i = 0; i < n; ++i) {
    auto [w, b] = v[i];
    for (int j = 0; j <= p; ++j) {
      dp[i + 1][j] = max(dp[i][j], dp[i + 1][j]);
      // w
      if (j + w <= p) dp[i + 1][j + w] = max(dp[i + 1][j + w], dp[i][j]);
      // b
      dp[i + 1][j] = max(dp[i + 1][j], min(dp[i][j] + b, k));
    }
  }
  int res = 0;
  for (int i = 0; i <= p; ++i) res = max(res, dp[n][i] + i);
  cout << res << endl;
  return 0;
}