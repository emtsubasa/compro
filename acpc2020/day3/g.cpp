#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> memo, table;
vector<int> a, dp;

long long solve();

int main() {
  cin >> n >> m;
  a.resize(n);
  for (auto &p : a) {
    cin >> p;
    --p;
  }
  {  // make memo
    memo.assign(m, vector<int>(m, 0));
    for (int i = 1; i < n; ++i) ++memo[a[i - 1]][a[i]];
    ++memo[a[n - 1]][a[n - 1]];
  }
  cout << solve() << endl;
  return 0;
}
long long solve() {
  dp.assign((1 << m), n + 1);
  dp[0] = 0;
  // iが右にいて左のビットがjのときに何回行くか
  table.assign(m, vector<int>(1 << m, 0));
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < (1 << m); ++j)
      for (int k = 0; k < m; ++k)
        if (j >> k & 1) {
          table[i][j] += memo[i][k] + memo[k][i];
        }
  for (int i = 0; i < (1 << m); ++i)
    for (int j = 0; j < m; ++j)
      if (i >> j & 1) {
        int bf = i ^ (1 << j), now = dp[bf], cnt = 0;
        for (int k = 0; k < m; ++k) cnt += memo[j][k];
        for (int k = 0; k < m; ++k)
          if (!(i >> k & 1)) cnt += table[k][bf];
        now = max(cnt, now);
        dp[i] = min(dp[i], now);
      }
  return dp[(1 << m) - 1];
}