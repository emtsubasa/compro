#include <bits/stdc++.h>
using namespace std;

long long n;

long long calc(long long x);

int main() {
  cin >> n;
  long long res = 0, now = 1;
  while (now <= n) {
    res = max(res, calc(n / now * now));
    now <<= 1;
  }
  cout << res << endl;
  return 0;
}

long long calc(long long x) {
  long long flg = 1, sum = 0, now = 0;
  while (x) {
    now += x * flg;
    sum += now;
    if (x & 1) break;
    flg *= -1;
    x >>= 1;
  }
  return sum;
}