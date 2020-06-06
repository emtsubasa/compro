#include <bits/stdc++.h>
using namespace std;

long long l, n, t[3];
vector<long long> dp;
vector<bool> h;

long long solve();

int main() {
  cin >> n >> l;
  dp.assign(l + 1, (long long)1e17);
  h.assign(l + 1, 0);
  for (int i = 0; i < n; ++i) {
    long long x;
    cin >> x;
    h[x] = 1;
  }
  cin >> t[0] >> t[1] >> t[2];
  cout << solve() << endl;
  return 0;
}

long long solve() {
  dp[0] = 0;
  for (int i = 0; i < l; ++i) {
    // 1
    dp[i + 1] = min(dp[i + 1], dp[i] + t[0] + h[i + 1] * t[2]);
    // 2
    if (i + 2 <= l)
      dp[i + 2] = min(dp[i + 2], dp[i] + t[0] + t[1] + h[i + 2] * t[2]);
    else
      dp[i + 1] = min(dp[i + 1], dp[i] + t[0] / 2 + t[1] / 2);
    // 3
    if (i + 4 <= l)
      dp[i + 4] = min(dp[i + 4], dp[i] + t[0] + t[1] * 3 + h[i + 4] * t[2]);
    else {
      long long dist = l - i;
      dp[l] = min(dp[l], dp[i] + t[0] / 2 + t[1] / 2 + t[1] * (dist - 1));
    }
  }
  return dp[l];
}