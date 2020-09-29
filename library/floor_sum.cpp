// sum_{i = 0}^{n-1}floor((a * i + b)/m)
long long floor_sum(long long n, long long m, long long a, long long b) {
  long long res = b / m * n + n * (n - 1) / 2 * (a / m);
  b %= m;
  a %= m;
  if (a == 0 || n == 0) return res;
  long long p = (a * (n - 1) + b) / m;
  return res + floor_sum(p, a, m, a * (n - 1) - m * p + b + a);
}