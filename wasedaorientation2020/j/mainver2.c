#include <stdio.h>
#include <stdlib.h>
#define inf (long long)(3e18)

int t;
long long n, m;
long long a[32] = {};
long long dp[32768] = {};
int cnt[32768] = {};

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
  for (int i = 1; i < x; ++i) dp[i] = inf;
  dp[0] = 0;
  for (int i = 0; i < n; ++i) {
    int now = 0;
    for (int j = 0; j < x; ++j) cnt[j] = 0;
    for (int j = 0; j < x; ++j)
      if (cnt[j] < 2) {
        int now = j;
        while (cnt[now] < 2) {
          int to = (a[i] + now) % x;
          if (dp[to] > dp[now] + a[i]) dp[to] = dp[now] + a[i];
          ++cnt[now];
          now = to;
        }
      }
  }
  long long res = 0;
  ++m;
  for (int i = 0; i < x; ++i) {
    long long now = m + (x + i - m % x) % x;
    if (now > dp[i]) now = dp[i];
    res += now / x;
  }
  return res;
}