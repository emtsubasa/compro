#include <bits/stdc++.h>
using namespace std;

// calculate |gcd|.
// if  ether num is 0, return 0
long long GCD(long long left, long long right) {
  if (left == 0 || right == 0) return 0;
  if (left < 0) left *= -1;
  if (right < 0) right *= -1;
  if (left < right) swap(left, right);
  long long nextnum, ansgcd = -1;
  while (ansgcd == -1) {
    nextnum = left % right;
    if (nextnum == 0) ansgcd = right;
    left = right;
    right = nextnum;
  }
  return ansgcd;
}

long long n, k, l;

bool solve(long long p) {
  return (k == n && p == 0) || ((p + k <= n) && GCD(p, n - p) == k);
}

int main() {
  cin >> k >> n >> l;
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
