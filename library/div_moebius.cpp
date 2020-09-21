map<long long, long long> div_moebius(long long n) {
  map<long long, long long> res;
  vector<long long> primes;
  for (long long i = 2; i * i <= n; ++i)
    if (n % i == 0) {
      primes.push_back(i);
      while (n % i == 0) n /= i;
    }
  if (n > 1) primes.push_back(n);
  n = primes.size();
  for (long long i = 0; i < (1 << n); ++i) {
    long long mu = 1, d = 1;
    for (long long j = 0; j < n; ++j)
      if (i >> j & 1) {
        mu *= -1;
        d *= primes[j];
      }
    res[d] = mu;
  }
  return res;
}