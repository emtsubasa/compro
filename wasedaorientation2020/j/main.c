#include <stdio.h>
#include <stdlib.h>
#define inf (long long)(3e18)

int t;
long long n, m;
long long a[32] = {};
long long dp[2][32768] = {};

int compare_ll(const void *a, const void *b) {
  return *(long long *)a - *(long long *)b;
}
long long solve();

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%lld %lld", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);
    qsort(a, n, sizeof(long long), compare_ll);
    printf("%lld\n", solve());
  }
  return 0;
}

long long solve() {
  long long x = a[0];
  for (int i = 1; i < x; ++i) dp[0][i] = inf;
  dp[0][0] = 0;
  int flg = 1;
  for (int i = 0; i < n; ++i) {
    while (1) {
      for (int j = 0; j < x; ++j) {
        int to = (a[i] + j) % x;
        dp[flg][to] = dp[1 - flg][to];
        if (dp[flg][to] > dp[1 - flg][j] + a[i])
          dp[flg][to] = dp[1 - flg][j] + a[i];
      }
      flg = 1 - flg;
      if ((a[i] <<= 1) > m) break;
    }
  }
  long long res = 0;
  ++m;
  for (int i = 0; i < x; ++i) {
    long long now = m + (x + i - m % x) % x;
    if (now > dp[1 - flg][i]) now = dp[1 - flg][i];
    res += now / x;
  }
  return res;
}