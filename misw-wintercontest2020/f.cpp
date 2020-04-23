#include <bits/stdc++.h>
using namespace std;

#define MOD (long long)(1e9 + 7)
template <int mod = MOD>
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

// P(x_i) = y_i(i:[0,n])
//  calc c_i : P(x) = c_n x^n + c_(n-1) x^(n-1)...c_0
vector<long long> lagrange_interpolation(long long mod, vector<long long> &y,
                                         vector<long long> &x) {
  assert(y.size() == x.size());
  long long n = y.size();
  vector<long long> ans(n, 0), Q(n), c[2];
  for (int i = 0; i < 2; ++i) c[i] = vector<long long>(n, 0);
  c[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    long long inv = 1;
    for (int j = 0; j < n; ++j)
      if (j != i) {
        inv *= x[i] - x[j];
        if ((inv %= mod) < 0) inv += mod;
      }
    Q[i] = y[i] * calcinv(inv, mod) % mod;
    for (int j = 0; j < n; ++j) {
      c[(i + 1) % 2][j] = (c[i % 2][j] * (-x[i]) % mod + mod) % mod;
      if (j != 0) (c[(i + 1) % 2][j] += c[i % 2][j - 1]) %= mod;
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = n - 1; j >= 0; --j) {
      if (j == n - 1)
        c[(n + 1) % 2][j] = 1;
      else
        c[(n + 1) % 2][j] =
            (c[n % 2][j + 1] + c[(n + 1) % 2][j + 1] * x[i] % mod) % mod;
      (ans[j] += (c[(n + 1) % 2][j] * Q[i]) % mod) %= mod;
    }
  }
  return ans;
}

// calc f(t) x_i = a + i * d, f(y_i) = y_i
template <typename T>
T lagrange_interpolation(const vector<T> &y, const T &t, const T &a = 0,
                         const T &d = 1) {
  long long n = y.size();
  T res = 0, p = 1;
  for (int i = 1; i < n; ++i) {
    p *= t - (a + d * i);
    p /= -d * i;
  }
  for (int i = 0; i < n; ++i) {
    if (t == a + d * i) return y[i];
    res += y[i] * p;
    p *= t - (a + d * i);
    p /= t - d * (i + 1);
    p *= d * (i - (n - 1));
    p /= d * (i + 1);
  }
  return res;
}

long long a, b, k;
vector<ModInt<>> v;

ModInt<> solve(long long x);

int main() {
  cin >> a >> b >> k;
  cout << solve(b + 1) - solve(a) << endl;
  return 0;
}

ModInt<> solve(long long x) {
  vector<ModInt<>> v;
  v.push_back(0);
  ModInt<> sum = 0;
  for (int i = 0; i <= k; ++i) {
    sum += ModInt<>(i + 1).pow(k);
    v.push_back(sum);
  }
  return lagrange_interpolation<ModInt<>>(v, x);
}