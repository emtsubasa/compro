#include <bits/stdc++.h>
#define inf (long long)(1e17)
using namespace std;

long long n, m;
vector<long long> a, b, r(3, 0);

long long solve();

int main() {
  cin >> n >> m;
  a.resize(n);
  b.resize(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) cin >> b[i];
  for (int i = 0; i < 3; ++i) cin >> r[i];
  cout << solve() << endl;
  return 0;
}

long long solve() {}