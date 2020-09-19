#include <bits/stdc++.h>
#define inf (long long)(1e17)
using namespace std;

long long n, k;
vector<long long> x, w, dp;
vector<vector<long long>> cost;

long long solve();

int main() {
  cin >> n >> k;
  x.resize(n);
  w.resize(n);
  for (int i = 0; i < n; ++i) cin >> x[i] >> w[i];
  cout << solve() << endl;
  return 0;
}

long long solve() {
  {  // calc cost from i to j
    cost.assign(n, vector<long long>(n, inf));
    for (int i = 0; i < n; ++i) {
      long long now = 0;
      // i >= j(left)
      for (int j = i; j < n; ++j) {
        now += w[j] * (x[j] - x[i]);
        cost[j][i] = now + x[j] - x[i];
      }
      // i <= j(right)
      now = 0;
      for (int j = i; j >= 0; --j) {
        now += w[j] * (x[i] - x[j]);
        cost[j][i] = now + x[i] - x[j];
      }
    }
  }
  dp.assign(n + 1, inf);
  dp[0] = 0;
  for (int i = 0; i < n; ++i) {
    long long now = inf;
    for (int j = 0; j <= i; ++j) now = min(now, dp[j] + cost[j][i]);
    for (int j = i; j < n; ++j)
      dp[j + 1] = min(dp[j + 1], now + cost[j][i] + k + 1);
  }
  return dp[n];
}