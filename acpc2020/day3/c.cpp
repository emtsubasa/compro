#include <bits/stdc++.h>
using namespace std;

long long n, k;
vector<long long> a;
vector<vector<long long>> dp;

long long solve();

int main() {
  cin >> n >> k;
  a.resize(n);
  for (auto &p : a) cin >> p;
  cout << solve() << endl;
  return 0;
}

long long solve() {
  dp.assign(n + 1, vector<long long>(k, -10000000000));
  dp[0][0] = 0;
  long long res = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < k; ++j) {
      long long to = (a[i] + j) % k, tmp = (a[i] + j) / k;
      dp[i + 1][j] = max(dp[i][j], dp[i + 1][j]);
      dp[i + 1][to] = max(dp[i][to], dp[i][j] + tmp);
    }
  for (int i = 0; i < k; ++i) res = max(res, dp[n][i] - i);
  return res;
}