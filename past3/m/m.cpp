#include <bits/stdc++.h>
#define inf 1e7
using namespace std;

long long n, m, s, k;
vector<vector<int>> g, memo;
vector<vector<long long>> dp;
vector<int> dist, t;

long long solve();

int main() {
  cin >> n >> m;
  g.resize(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    g[--u].push_back(--v);
    g[v].push_back(u);
  }
  cin >> s >> k;
  t.resize(k + 1);
  t[0] = s - 1;
  for (int i = 1; i <= k; ++i) {
    cin >> t[i];
    --t[i];
  }
  cout << solve() << endl;
  return 0;
}

long long solve() {
  ++k;
  memo.assign(k, vector<int>(k, 0));
  for (int i = 0; i < k; ++i) {
    dist.assign(n, inf);
    dist[t[i]] = 0;
    queue<int> qu;
    qu.push(t[i]);
    while (qu.size()) {
      int now = qu.front();
      qu.pop();
      for (auto to : g[now])
        if (dist[to] == inf) {
          dist[to] = dist[now] + 1;
          qu.push(to);
        }
    }
    for (int j = 0; j < k; ++j) memo[i][j] = dist[t[j]];
  }
  dp.assign(1 << k, vector<long long>(k, (long long)(1e16)));
  dp[1][0] = 0;
  for (int i = 2; i < (1 << k); ++i)
    for (int j = 0; j < k; ++j)
      if (i >> j & 1) {
        long long bit = i - (1 << j);
        for (int l = 0; l < k; ++l)
          if (bit >> l & 1) dp[i][j] = min(dp[i][j], dp[bit][l] + memo[j][l]);
      }

  long long res = 1e16;
  for (int i = 0; i < k; ++i) res = min(res, dp[(1 << k) - 1][i]);
  return res;
}