// calc x s.t. a**x = b(mod p)
long long mod_log(long long a, long long b, long long p) {
  assert(p > 0);
  long long sqp = sqrt(p) + 1;
  map<long long, long long> bs;
  long long now = 1;
  {  // baby-step
    for (long long i = 0; i <= sqp; ++i) {
      bs[now] = i;
      (now *= a) %= p;
    }
  }
  {    // giant-step
    {  // calc a**(-sqp) -> (a**sqp)**-1
      long long mul = now;
      now = 1;
      long long n = p - 2;
      while (n) {
        if (n & 1) (now *= mul) %= p;
        (mul *= mul) %= p;
        n >>= 1;
      }
    }
    for (long long i = 0; i <= sqp; ++i) {
      if (bs.find(b) != bs.end()) return bs[b] + i * sqp;
      (b *= now) %= p;
    }
  }
  return -1;
}