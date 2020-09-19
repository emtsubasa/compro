#include <bits/stdc++.h>
using namespace std;

template <int mod = (int)(998244353)>
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

struct dat {
  long long t, l, r;
  dat(long long x = 0, long long y = 0, long long z = 0) : t(x), l(y), r(z) {}
  bool operator==(const dat &d) const {
    return t == d.t && l == d.l && r == d.r;
  }
  bool operator<(const dat &d) const {
    if (t != d.t) return t < d.t;
    if (l != d.l) return l < d.l;
    return r < d.r;
  }
  dat operator*(const dat &d) const {
    dat res(d.t, max(d.l, l - (d.t - t)), min(d.r, r + (d.t - t)));
    if (res.l > res.r) res = dat(-1, 0, 0);
    return res;
  }
};

int n;
vector<dat> v;
map<dat, ModInt<>> dp;

ModInt<> solve();

int main() {
  cin >> n;
  v.resize(n);
  for (auto &p : v) cin >> p.t >> p.l >> p.r;
  cout << solve() << endl;
  return 0;
}

ModInt<> solve() {
  dp[dat()] = 1;
  for (int i = 0; i < n; ++i) {
    vector<dat> memod;
    vector<ModInt<>> memoc;
    for (auto [d, c] : dp) {
      dat now = d * v[i];
      if (now.t >= 0) {
        memod.push_back(now);
        memoc.push_back(c);
      }
    }
    int len = memod.size();
    for (int j = 0; j < len; ++j) dp[memod[j]] += memoc[j];
  }
  ModInt<> res = -1;
  for (auto [d, c] : dp) res += c;

  return res;
}