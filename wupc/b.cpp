#include <bits/stdc++.h>
using namespace std;

int n, sum = 0;
vector<long long> a, b;

int main() {
  cin >> n;
  a.resize(n);
  b.resize(n);
  for (auto &p : a) cin >> p;
  for (int i = 0; i < n - 1; ++i) {
    sum += a[i];
    b[i] = a[n - 1];
  }
  b[n - 1] = -sum;
  sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += a[i] * b[i];
    assert(abs(b[i]) <= (long long)(1e9));
  }
  assert(sum == 0);
  for (int i = 0; i < n; ++i) cout << b[i] << " \n"[i == n - 1];
  return 0;
}