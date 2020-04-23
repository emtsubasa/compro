#include <bits/stdc++.h>
#define MOD (long long)(1e9 + 7)
using namespace std;

#define MAX 5000000

template <int mod>
struct ModInt {
  int x;
  ModInt() : x(0) {}
  ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
  ModInt &operator+=(const ModInt &p) {
    if ((x += p.x) >= mod) x -= mod;
    return *this;
  }
  ModInt &operator-=(const ModInt &p) {
    if ((x += mod - p.x) >= mod) x -= mod;
    return *this;
  }
  ModInt &operator*=(const ModInt &p) {
    x = (int)(1LL * x * p.x % mod);
    return *this;
  }
  ModInt &operator/=(const ModInt &p) {
    *this *= p.inverse();
    return *this;
  }
  ModInt operator-() const { return ModInt(-x); }
  ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
  ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
  ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
  ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
  bool operator==(const ModInt &p) const { return x == p.x; }
  bool operator!=(const ModInt &p) const { return x != p.x; }
  ModInt inverse() const {
    int a = x, b = mod, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return ModInt(u);
  }
  ModInt pow(int64_t n) const {
    ModInt ans(1), mul(x);
    while (n) {
      if (n & 1) ans *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ans;
  }
  friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; }
  friend istream &operator>>(istream &is, ModInt &a) {
    int64_t t;
    is >> t;
    a = ModInt<mod>(t);
    return (is);
  }
  static int get_mod() { return mod; }
};

struct Combination {
  vector<ModInt<MOD>> _fact, _rfact, _inv;
  Combination(long long nsize = MAX)
      : _fact(nsize + 1), _rfact(nsize + 1), _inv(nsize + 1) {
    _fact[0] = _rfact[nsize] = _inv[0] = 1;
    for (int i = 1; i <= nsize; i++) _fact[i] = _fact[i - 1] * i;
    _rfact[nsize] /= _fact[nsize];
    for (int i = nsize - 1; i >= 0; i--) _rfact[i] = _rfact[i + 1] * (i + 1);
    for (int i = 1; i <= nsize; i++) _inv[i] = _rfact[i] * _fact[i - 1];
  }
  inline ModInt<MOD> fact(int k) const { return _fact[k]; }

  inline ModInt<MOD> rfact(int k) const { return _rfact[k]; }

  inline ModInt<MOD> inv(int k) const { return _inv[k]; }

  ModInt<MOD> P(int n, int r) const {
    if (r < 0 || n < r) return 0;
    return fact(n) * rfact(n - r);
  }

  ModInt<MOD> C(int p, int q) const {
    if (q < 0 || p < q) return 0;
    return fact(p) * rfact(q) * rfact(p - q);
  }
  ModInt<MOD> H(int n, int r) const {
    if (n < 0 || r < 0) return (0);
    return n == 0 ? 1 : C(n + r - 1, r - 1);
  }
};

long long n;
map<long long, long long> mp;
Combination com;

ModInt<MOD> solve();

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    long long x;
    cin >> x;
    ++mp[x];
  }
  cout << solve() << endl;
  return 0;
}

ModInt<MOD> solve() {
  vector<ModInt<MOD>> memo(n + 1, 0);
  memo[0] = 0;
  memo[1] = 1;
  for (int i = 2; i <= n; ++i) {
    ModInt<MOD> now = i;
    memo[i] = now.pow(i - 2);
  }
  vector<long long> v;
  ModInt<MOD> res = 1;
  for (auto p : mp) v.push_back(p.second);
  for (int i = 0; i < v.size(); ++i) {
    if (v.size() != 1) res *= v[i];
    if (i != 0 && i != (int)v.size() - 1) res *= v[i];
    res *= memo[v[i]];
  }
  return res;
}