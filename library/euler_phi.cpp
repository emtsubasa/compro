long long euler_phi(long long x) {
  long long res = x;
  for (long long i = 2; i * i <= x; ++i)
    if (x % i == 0) {
      res -= res / i;
      while (x % i == 0) x /= i;
    }
  if (x > 1) res -= res / x;
  return res;
}