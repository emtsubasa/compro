#include <bits/stdc++.h>
using namespace std;

long long n;
vector<long long> a, b;

long double solve();

int main() {
  cout << fixed << setprecision(5);
  cin >> n;
  a.resize(n);
  b.resize(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) cin >> b[i];
  cout << solve() << endl;
  return 0;
}

long double solve() {
  long double res = 0;
  for (int i = 0; i < n; ++i) {
    long double now = 0;
    for (int j = 0; j <= a[i]; ++j) {
      long long all = 2 * j + 1;
      now = max(
          now,
          (long double)max(a[i] + j - max(a[i] - j, b[i] + 1) + 1, 0LL) / all);
    }
    res += now;
  }
  return res;
}