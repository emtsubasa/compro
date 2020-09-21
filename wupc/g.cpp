#include <bits/stdc++.h>
using namespace std;

struct dat {
  long long t, p;
};

int n, k, t;
vector<dat> v;
vector<long long> dp;

long long solve();

int main() {
  cin >> n >> k >> t;
  v.resize(n);
  for (auto& p : v) cin >> p.t >> p.p;
  cout << solve() << endl;
  return 0;
}

long long solve() {
  dp.assign(t + 1, 0);
  for (int i = 0; i < n; ++i)
    for (int j = t; j >= v[i].t; --j)
      dp[j] = max(dp[j], dp[j - v[i].t] + v[i].p);
  v.resize(t + 1);
  for (int i = 0; i <= t; ++i) v[i].t = i + k, v[i].p = dp[i];
  for (int i = 0; i <= t; ++i)
    for (int j = v[i].t; j <= t; ++j)
      dp[j] = max(dp[j], dp[j - v[i].t] + v[i].p);
  long long res = 0;
  for (auto p : dp) res = max(res, p);
  return res;
}