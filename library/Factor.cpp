struct Factor {
  inline long long mul(long long x, long long y, long long z) {
    return (__int128_t)x * y % z;
  }
  inline long long f(long long x, long long n) {
    return ((__int128_t)x * x + 1) % n;
  }
  long long mpow(long long b, long long p, long long mod) {
    long long res = 1;
    while (p) {
      if (p & 1) res = mul(res, b, mod);
      b = mul(b, b, mod);
      p >>= 1;
    }
    return res;
  }
  bool millar(long long n) {
    if ((~n & 1) && n != 2) return 0;
    long long d = n - 1, x = n - 1;
    int s = __builtin_ctzll(d);
    d >>= s;
    vector<long long> a = {2, 7, 61};
    if (n >= 4759123141LL)
      a = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (auto p : a) {
      if (p >= n) break;
      long long now = mpow(p, d, n);
      if (now == 1) continue;
      int i = s;
      while (now != x && i--) now = mul(now, now, n);
      if (now != x) return 0;
    }
    return 1;
  }
  long long rho(long long n) {
    long long x = 0, y = 0;
    int i = 1;
    while (1) {
      long long g = gcd(abs(x - y), n);
      if (g == n)
        y = f(x = ++i, n);
      else if (g == 1) {
        x = f(x, n);
        y = f(f(y, n), n);
      } else
        return g;
    }
    return -1;
  }
  map<long long, int> factor(long long n) {
    map<long long, int> res;
    if (n % 2 == 0) {
      res[2] = __builtin_ctzll(n);
      n >>= __builtin_ctzll(n);
    }
    queue<long long> qu;
    qu.push(n);
    while (qu.size()) {
      long long now = qu.front();
      qu.pop();
      if (now == 1) continue;
      if (millar(now)) {
        ++res[now];
        continue;
      }
      long long p = rho(now);
      qu.push(p);
      qu.push(now / p);
    }
    return res;
  }
};