#include <bits/stdc++.h>
using namespace std;

struct dat {
  long long a, b;
  bool operator<(const dat &r) {
    if (b != r.b) return b > r.b;
    return a > r.a;
  }
};

long long n, m;
vector<dat> v;
vector<vector<long long>> dp;

long long solve();

int main() {
  cin >> n >> m;
  v.resize(n);
  for (int i = 0; i < n; ++i) cin >> v[i].a;
  for (int i = 0; i < n; ++i) cin >> v[i].b;
  sort(v.begin(), v.end());
  cout << solve() << endl;
  return 0;
}

long long solve() {
  long long res = -1e17;
  dp.assign(n + 1, vector<long long>(m + 1, -1e17));
  dp[0][0] = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= m; ++j) {
      dp[i + 1][j] = dp[i][j];
      if (j != 0)
        dp[i + 1][j] =
            max(dp[i + 1][j], dp[i][j - 1] + v[i].a - (j - 1) * v[i].b);
    }
  }
  return dp[n][m];
}