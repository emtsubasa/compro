// as + bt = GCD(a,b) a,b:const s,t:var(any)
// return GCD(a,b)
long long extGCD(long long a, long long b, long long &s, long long &t) {
  s = 1, t = 0;
  long long u = 0, v = 1;
  while (b) {
    long long tmp = a / b;
    a -= b * tmp;
    s -= u * tmp;
    t -= v * tmp;
    swap(s, u);
    swap(t, v);
    swap(a, b);
  }
  return a;
}
// (mod)x+ay=1, calculate y -> a^-1 (mod m) (a,m : coprime)
long long calcinv(long long a, long long m) {
  long long s, t;
  extGCD(a, m, s, t);
  return (s + m) % m;
}

// calc x s.t. a**x = b(mod p)
long long mod_log(long long a, long long b, long long p) {
  assert(p > 0);
  long long sqp = sqrt(p) + 2;
  unordered_map<long long, long long> bs;
  long long base = 1;                      // a if deny 0
  {                                        // baby-step
    for (long long i = 0; i < sqp; ++i) {  // i = 1 if deny 0
      if (!bs.count(base)) bs[base] = i;
      (base *= a) %= p;
    }
  }
  {  // giant-step
    long long rev = calcinv(base, p);
    for (long long i = 0; i <= sqp; ++i) {
      if (bs.count(b)) return bs[b] + i * sqp;
      (b *= rev) %= p;
    }
  }
  return -1;
}
