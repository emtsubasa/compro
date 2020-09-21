#include <bits/stdc++.h>
using namespace std;

template <int mod = (int)(1e9 + 7)>
struct ModInt {
  int x;
  constexpr ModInt() : x(0) {}
  constexpr ModInt(int64_t y)
      : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
  constexpr ModInt &operator+=(const ModInt &p) noexcept {
    if ((x += p.x) >= mod) x -= mod;
    return *this;
  }
  constexpr ModInt &operator-=(const ModInt &p) noexcept {
    if ((x += mod - p.x) >= mod) x -= mod;
    return *this;
  }
  constexpr ModInt &operator*=(const ModInt &p) noexcept {
    x = (int)(1LL * x * p.x % mod);
    return *this;
  }
  constexpr ModInt &operator/=(const ModInt &p) noexcept {
    *this *= p.inverse();
    return *this;
  }
  constexpr ModInt operator-() const { return ModInt(-x); }
  constexpr ModInt operator+(const ModInt &p) const noexcept {
    return ModInt(*this) += p;
  }
  constexpr ModInt operator-(const ModInt &p) const noexcept {
    return ModInt(*this) -= p;
  }
  constexpr ModInt operator*(const ModInt &p) const noexcept {
    return ModInt(*this) *= p;
  }
  constexpr ModInt operator/(const ModInt &p) const noexcept {
    return ModInt(*this) /= p;
  }
  constexpr bool operator==(const ModInt &p) const noexcept { return x == p.x; }
  constexpr bool operator!=(const ModInt &p) const noexcept { return x != p.x; }
  constexpr ModInt inverse() const noexcept {
    int a = x, b = mod, u = 1, v = 0, t = 0;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return ModInt(u);
  }
  constexpr ModInt pow(int64_t n) const {
    ModInt res(1), mul(x);
    while (n) {
      if (n & 1) res *= mul;
      mul *= mul;
      n >>= 1;
    }
    return res;
  }
  friend constexpr ostream &operator<<(ostream &os, const ModInt &p) noexcept {
    return os << p.x;
  }
  friend constexpr istream &operator>>(istream &is, ModInt &a) noexcept {
    int64_t t = 0;
    is >> t;
    a = ModInt<mod>(t);
    return (is);
  }
  constexpr int get_mod() { return mod; }
};

struct Combination {
  vector<ModInt<>> _fact, _rfact, _inv;
  Combination(long long nsize = 5000000)
      : _fact(nsize + 1), _rfact(nsize + 1), _inv(nsize + 1) {
    _fact[0] = _rfact[nsize] = _inv[0] = 1;
    for (int i = 1; i <= nsize; i++) _fact[i] = _fact[i - 1] * i;
    _rfact[nsize] /= _fact[nsize];
    for (int i = nsize - 1; i >= 0; i--) _rfact[i] = _rfact[i + 1] * (i + 1);
    for (int i = 1; i <= nsize; i++) _inv[i] = _rfact[i] * _fact[i - 1];
  }
  inline ModInt<> fact(int k) const { return _fact[k]; }

  inline ModInt<> rfact(int k) const { return _rfact[k]; }

  inline ModInt<> inv(int k) const { return _inv[k]; }

  ModInt<> P(int n, int r) const {
    if (r < 0 || n < r) return 0;
    return fact(n) * rfact(n - r);
  }

  ModInt<> C(int p, int q) const {
    if (q < 0 || p < q) return 0;
    return fact(p) * rfact(q) * rfact(p - q);
  }
  // n types,choose r
  ModInt<> H(int n, int r) const {
    if (n < 0 || r < 0) return (0);
    return r == 0 ? 1 : C(n + r - 1, r);
  }
};

map<long long, long long> div_moebius(long long n, vector<long long> &primes) {
  map<long long, long long> res;
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

long long n;
Combination com;
vector<ModInt<>> rsum;

ModInt<> solve();

int main() {
  {
    int len = com._rfact.size();
    rsum.assign(len, 1);
    for (int i = 1; i < len; ++i) rsum[i] = rsum[i - 1] + com.rfact(i);
  }
  cin >> n;
  cout << solve() << endl;
  return 0;
}

ModInt<> solve() {
  ModInt<> res = 0;
  vector<long long> primes, divisors;
  map<long long, long long> mb = div_moebius(n, primes), cnt;
  for (long long i = 1; i * i <= n; ++i)
    if (n % i == 0) {
      divisors.push_back(i);
      if (i * i != n) divisors.push_back(n / i);
    }
  sort(divisors.begin(), divisors.end());
  cnt[1] = 1;
  for (auto d : divisors)
    for (auto p : primes)
      if (d % p == 0) {
        long long now = 1, tmp = d;
        while (tmp % p == 0) ++now, tmp /= p;
        cnt[d] = cnt[d / p] * now / (now - 1);
        break;
      }
  for (auto p : mb) {
    long long d = n / p.first, u = p.second, c = 0;
    c = cnt[d];
    res += com.fact(c) * rsum[c - 1] * u;
  }
  return res;
}