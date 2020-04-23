#include <bits/stdc++.h>
using namespace std;

long long n, k, l;

bool solve(long long p);

int main() {
  cin >> k >> n >> l;
  assert(n % k == 0);
  if (solve(l))
    cout << "Yes" << endl;
  else {
    cout << "No" << endl;
    for (int i = l - 1; i >= 0; --i)
      if (solve(i)) {
        cout << i << endl;
        return 0;
      }
  }
  return 0;
}

bool solve(long long p) {
  if (p % k != 0 || p + k > n) return 0;
  long long q = n / k;
  p /= k;
  q -= p;
  while (1) {
    if (p > q) swap(p, q);
    if (p == 0) break;
    q %= p;
  }
  return q == 1;
}