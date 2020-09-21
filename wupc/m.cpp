#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> g;
vector<long long> l, sum, dp, res;

void solve();
long long dfs(int now, int par);
void reroot(int now, int par);

int main() {
  cin >> n;
  l.resize(n);
  g.resize(n);
  for (auto& p : l) cin >> p;
  for (int i = 1; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    g[--a].push_back(--b);
    g[b].push_back(a);
  }
  solve();
  for (auto p : res) cout << p << endl;
  return 0;
}

void solve() {
  dp.assign(n, 0);
  sum.assign(n, 0);
  res.assign(n, 0);
  dfs(0, -1);
  reroot(0, -1);
}

long long dfs(int now, int par) {
  for (auto to : g[now])
    if (to != par) {
      sum[now] += dfs(to, now);
      dp[now] += dp[to] + sum[to];
    }
  return (sum[now] += l[now]);
}
void reroot(int now, int par) {
  long long bfdp = dp[now], bfsum = sum[now];
  dp[now] = 0, sum[now] = l[now];
  for (auto to : g[now]) {
    sum[now] += sum[to];
    dp[now] += dp[to] + sum[to];
  }
  res[now] = dp[now];
  for (auto to : g[now])
    if (to != par) {
      sum[now] -= sum[to];
      dp[now] -= sum[to] + dp[to];
      reroot(to, now);
      sum[now] += sum[to];
      dp[now] += sum[to] + dp[to];
    }
  dp[now] = bfdp;
  sum[now] = bfsum;
}