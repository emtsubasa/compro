#include <bits/stdc++.h>
using namespace std;

long long n, lim;
vector<long long> a;

long long solve();
bool ch(long long x, bool flg);

int main() {
  cin >> n;
  a.resize(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  cout << solve() << endl;
  return 0;
}

long long solve() {
  long long l = -1, r = 1e16, tmp = 0;
  lim = n * (n + 1) / 2;
  while (r - l > 1) {
    long long mid = (l + r) / 2;
    if (ch(mid, 1))
      r = mid;
    else
      l = mid;
  }
  tmp = r;
  if (lim & 1) return tmp;
  l = -1, r = 1e16;
  while (r - l > 1) {
    long long mid = (l + r) / 2;
    if (ch(mid, 0))
      r = mid;
    else
      l = mid;
  }
  tmp += r;
  return tmp / 2;
}

bool ch(long long x, bool flg) {
  long long cnt = 0;
  for (long long l = 0, r = 0, sum = 0; l < n; r = max(r, ++l)) {
    while (r < n && sum + a[r] <= x) sum += a[r++];
    cnt += r - l;
    if (l != r) sum -= a[l];
  }
  return cnt >= lim / 2 + flg;
}